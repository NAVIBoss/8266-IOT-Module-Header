#ifndef XIIIMRGB_h
#define XIIIMRGB_h

#pragma once
#include <Arduino.h>
#include <GammaCorrectionLib.h>

#define aLED(x,y) analogWrite(x,y)

#if defined MQTT_SendEnable
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTStat(x,y,z) Comm.status(x,y,z)
#else
#define MQTTStatus(x,y)
#define MQTTStat(x,y,z)
#endif

class XIIIMRGB {
public:
uint8_t Red_PIN;
uint8_t Green_PIN;
uint8_t Blue_PIN;
uint8_t Relay_PIN;

int32_t timeSave;                              // таймер задержки записи изменений в EEPROM
int32_t saveDelay=1000;                        // задержка проверки необходимости записи изменений в EEPROM каждую секунду
int32_t BrightTimeStart;                       // начало отсчета включения яркой подсветки

XIIIMRGB(uint8_t Red_PIN, uint8_t Green_PIN, uint8_t Blue_PIN);

void HEXtoRGB(char *hex);
void powerON();
void powerOFF();
void Status();
void loop();

private:

boolean powerBeforeBright = 0;                 // сохранить состояние включения до включения яркой подсветки

uint8_t Led_Pin_[3];                           // GPOI ESP для управления RGB
uint8_t Led_Value_[3];
uint8_t Led_Value_Fade_[3];
uint8_t Led_Value_Fade_Start_[3];
uint8_t Led_Value_Old_[3];
int16_t delta[3];
int16_t fadeCount = 0;
int16_t steps = 0;
boolean changeColorProcess = 0;                 // нужно изменить цвет

struct Esave {                                  // структура для сверки параметров текущих и записанных в EEPROM
uint8_t Led_Value_Save_[3];
int16_t FadeDelay;
char hexColor[8];
char favoriteColor[8];
boolean Power;
boolean GammaCorrection;
uint8_t StartMode;
char brightColor[8];
} esave;

void deltaCalc();
void SetRGBLed();
void SetBrightMode();
void init();
void ChangeColor();

#if defined EEPROM_Enable
void SaveData(boolean in);
#endif
};

void XIIIMRGB::init() {if(!InitializationOk) return; static boolean init; if(init) return; init=1;
for_i(0,3) {pinMode(Led_Pin_[i], OUTPUT);}

CMn("");
if(save.StartMode==0) {CMn("Восстанавливаем состояние RGB"); if(save.Power) HEXtoRGB(save.hexColor);}
if(save.StartMode==1) {powerOFF(); CMn("Выключаем RGB");} 
if(save.StartMode==2) {CMn("Установливыем любимый цвет"); HEXtoRGB(save.favoriteColor); strcpy(save.hexColor,save.favoriteColor);}

for_i(0, sizeof(RELAY_Pin_)) {if(RELAY_Pin_[i]==RGBPIN) RELAY_Value_[i]=save.Power; CM("RGB Relay"); CM(i); CM(" : "); CMn(RELAY_Value_[i]);}

#if defined EEPROM_Enable
for_i(0,3) esave.Led_Value_Save_[i] = save.Led_Value_Save_[i];
esave.FadeDelay = save.FadeDelay;
strcpy(esave.hexColor, save.hexColor);
strcpy(esave.favoriteColor, save.favoriteColor);
esave.Power = save.Power;
esave.GammaCorrection = save.GammaCorrection;
esave.StartMode = save.StartMode;
strcpy(esave.brightColor,save.brightColor);
#endif
CMn("Инициализация RGB завершена\n");}

XIIIMRGB::XIIIMRGB(uint8_t _Red_PIN, uint8_t _Green_PIN, uint8_t _Blue_PIN) {Red_PIN=_Red_PIN; Green_PIN=_Green_PIN; Blue_PIN=_Blue_PIN;
Led_Pin_[0] = Red_PIN; Led_Pin_[1] = Green_PIN; Led_Pin_[2] = Blue_PIN;
for_i(0,3) {Led_Value_[i] = 0; Led_Value_Fade_[i] = 0; Led_Value_Fade_Start_[i] = 0; Led_Value_Old_[i] = 0;
esave.Led_Value_Save_[i] = Led_Value_[i]; }
esave.FadeDelay=10; strcpy(esave.hexColor,"#62006C"); strcpy(esave.favoriteColor,"#62006C"); esave.Power = 0; esave.GammaCorrection = 1; esave.StartMode = 0; strcpy(esave.brightColor,"#E700FF");}

void XIIIMRGB::Status() {CM("LED RGB PINs: "); CM("Red - "); CM(Red_PIN); CM(", "); CM("Green - "); CM(Green_PIN); CM(", "); CM("Blue - "); CMn(Blue_PIN);
CM("Текущий цвет RGB: "); CMn(save.hexColor);
CM("Любимый цвет RGB: "); CMn(save.favoriteColor);
CM("Яркий цвет RGB: "); CMn(save.brightColor);
CM("Гамма коррекция: "); if (save.GammaCorrection) CMn("Включена"); else CMn("Выключена");
CM("Режим запуска: "); if (save.StartMode == 0) CMn("Восстановить цвет"); if (save.StartMode == 1) CMn("Выключить"); if (save.StartMode == 2) CMn("Любимый цвет");
CM("Задержка перехода: "); CM(save.FadeDelay); CMn(" мс");}

void XIIIMRGB::deltaCalc() {int16_t coltemp = 0;
for_i(0,3) {Led_Value_Fade_Start_[i] = Led_Value_Old_[i]; coltemp = abs(Led_Value_[i] - Led_Value_Fade_Start_[i]); 
if (steps < coltemp) steps = coltemp;} fadeCount = 0;
CM("Шагов = "); CM(steps); CM(" Delta: ");
if (!steps) {CMn("Нечего менять, выходим"); return;}
for_i(0,3) {delta[i] = (abs(Led_Value_[i] - Led_Value_Old_[i]))*1000 / steps; CM(delta[i]); CM(" "); Led_Value_Old_[i] = Led_Value_[i];}
CMn(); changeColorProcess = 1;}

int16_t hex2dec(uint8_t c) { // converts one HEX character into a number
if (c >= '0' && c <= '9') {return c - '0';} 
else if (c >= 'A' && c <= 'F') {return c - 'A' + 10;}
else if (c >= 'a' && c <= 'f') {return c - 32 - 'A' + 10;}
return '0';}

void XIIIMRGB::HEXtoRGB(char *hex) {CM("Цвет HEX: "); CM(hex); CM(" -> RGB: ");
Led_Value_[0] = (hex2dec(hex[2]) + hex2dec(hex[1]) * 16);
Led_Value_[1] = (hex2dec(hex[4]) + hex2dec(hex[3]) * 16);
Led_Value_[2] = (hex2dec(hex[6]) + hex2dec(hex[5]) * 16);
//Led_Value_[0] = 255- (hex2dec(hex[1]) + hex2dec(hex[0]) * 16);
//Led_Value_[1] = 255- (hex2dec(hex[3]) + hex2dec(hex[2]) * 16);
//Led_Value_[2] = 255- (hex2dec(hex[5]) + hex2dec(hex[4]) * 16);
CM(Led_Value_[0]); CM(" "); CM(Led_Value_[1]); CM(" "); CMn(Led_Value_[2]);
if(MQTTOk) MQTTStatus("Color",hex);
if (Led_Value_[0] == 0 && Led_Value_[1] == 0 && Led_Value_[2] == 0 && save.Power) {
save.Power = 0; powerBeforeBright=save.Power; RELAY_Value_[Relay_PIN]=0; MQTTStatus4("Relay",Relay_PIN,false,"Relay");} 
else if ((Led_Value_[0] != 0 || Led_Value_[1] != 0 || Led_Value_[2] != 0) && !save.Power) {
save.Power = 1; powerBeforeBright=save.Power; RELAY_Value_[Relay_PIN]=0; MQTTStatus4("Relay",Relay_PIN,true,"Relay");}
deltaCalc();}

void XIIIMRGB::SetBrightMode() {
static boolean brightLight; if(brightMode==brightLight) return; CM("Переключаем Bright Mode в "); CMn(brightMode); brightLight=brightMode;
if(!brightLight && !standByShot) {CMn("Возвращаем цвет"); brightMode=0;
if(!powerBeforeBright) {save.Power=0; for_i(0,3) Led_Value_[i]=0; deltaCalc(); MQTTStatus("Color",save.hexColor);} else {
HEXtoRGB(save.hexColor);}} else {BrightTimeStart=millis(); powerBeforeBright=save.Power; CM("save.Power = "); CMn(save.Power); if(!save.Power) {save.Power=1;} HEXtoRGB(save.brightColor); 
CMn("Включаем яркую подсветку"); brightMode=1; timeSave = millis();}}

void XIIIMRGB::powerOFF() {if(!save.Power) return; save.Power = 0; powerBeforeBright=save.Power; for_i(0,3) Led_Value_[i]=0; CMn("Power: OFF"); deltaCalc(); brightMode=0;}

void XIIIMRGB::powerON() {if(!save.Power) {CMn("Power: ON"); save.Power = 1; powerBeforeBright=save.Power;}
if (!strcmp(save.hexColor,"#000000")) {HEXtoRGB(save.favoriteColor); strcpy(save.hexColor,save.favoriteColor); return;} HEXtoRGB(save.hexColor);}

void XIIIMRGB::SetRGBLed() { if (!changeColorProcess) return; static long fadeTimer; if (millis() - fadeTimer < save.FadeDelay) return; fadeTimer = millis();
changeColorProcess = 0; for_i(0,3) {if (Led_Value_Fade_[i] != Led_Value_[i]) changeColorProcess = 1;}
//CM("RGB: "); for_i(0,3) {CM(Led_Value_[i]); CM(" ");} CM(" <- ");
for_i(0,3) {if (Led_Value_Fade_[i] < Led_Value_[i]) Led_Value_Fade_[i] = Led_Value_Fade_Start_[i] + round(delta[i]*fadeCount/1000); 
else if (Led_Value_Fade_[i] > Led_Value_[i]) Led_Value_Fade_[i] = Led_Value_Fade_Start_[i] - round(delta[i]*fadeCount/1000);
if (Led_Value_Fade_[i] > 255) Led_Value_Fade_[i] = 255; if (Led_Value_Fade_[i] < 0) Led_Value_Fade_[i] = 0;
Led_Value_Old_[i] = Led_Value_Fade_[i];
//CM(Led_Value_Fade_[i]); CM(" "); 
save.GammaCorrection ? aLED(Led_Pin_[i],GammaCorrection::CorrectTable8(Led_Value_Fade_[i])) : aLED(Led_Pin_[i],Led_Value_Fade_[i]);}
//CMn();
fadeCount++;
if (fadeCount > steps) {changeColorProcess = 0; steps = 0; for_i(0,3) {Led_Value_Old_[i] = Led_Value_[i]; 
save.GammaCorrection ? aLED(Led_Pin_[i],GammaCorrection::CorrectTable8(Led_Value_[i])) : aLED(Led_Pin_[i],Led_Value_[i]);}}}

void XIIIMRGB::SaveData(boolean in) {if(standBy || standByShot || standByQuick) return;
if (!in && millis() - timeSave < saveDelay) return; timeSave = millis(); //CMn("Проверка изменения данных для EEPROM");
saveDelay = 1000; boolean needSave=0; if (in) goto goSave;
for_i(0,3) if (save.Led_Value_Save_[i] != esave.Led_Value_Save_[i]) {esave.Led_Value_Save_[i] = save.Led_Value_Save_[i]; needSave=1;}
if (save.FadeDelay != esave.FadeDelay) {esave.FadeDelay = save.FadeDelay; needSave=1;}
if (strcmp(save.hexColor,esave.hexColor)) {strcpy(esave.hexColor, save.hexColor); needSave=1;}
if (strcmp(save.favoriteColor,esave.favoriteColor)) {strcpy(esave.favoriteColor, save.favoriteColor); needSave=1;}
if (save.Power != esave.Power) {esave.Power = save.Power; needSave=1;}
if (save.GammaCorrection != esave.GammaCorrection) {esave.GammaCorrection = save.GammaCorrection; needSave=1;}
if (save.StartMode != esave.StartMode) {esave.StartMode = save.StartMode; needSave=1;}
if (strcmp(save.brightColor, esave.brightColor)) {strcpy(esave.brightColor,save.brightColor); needSave=1;}
if(!needSave) return; // {CMn("Ничего не изменилось. Нечего сохранять."); return;
goSave:
#if defined EEPROM_Enable
CMn("Есть изменения данных. Сохраняем данные");
#if defined ledIndikator_Enable
Led.SaveInd=1;
#endif
saveChange=1;
#endif
}

void XIIIMRGB::ChangeColor() {return1sec; uint8_t Value[3];
for_i(0,3) Value[i]=random(5,180); CM("Red: "); CM(Value[0]); CM(" Green: "); CM(Value[1]); CM(" Blue: "); CM(Value[2]);
char hex[8] = {0}, hexColor[8]={"#"}; sprintf(hex,"%02X%02X%02X",Value[0],Value[1],Value[2]); CM(" HEX: "); CMn(hex);
strcat(hexColor,hex); HEXtoRGB(hexColor);}

void XIIIMRGB::loop(){
init();
SetRGBLed();
SetBrightMode();
SaveData(0);
//ChangeColor();
}

#endif // XIIIMRGB_h