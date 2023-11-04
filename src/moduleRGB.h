#ifndef XIIIMmoduleRGB_h
#define XIIIMmoduleRGB_h

#pragma once
#include <Arduino.h>
#include <GammaCorrectionLib.h>

#if defined MQTT_SendEnable
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTStat(x,y,z) Comm.status(x,y,z)
#else
#define MQTTStatus(x,y)
#define MQTTStat(x,y,z)
#endif

class XIIIMmoduleRGB {
public:
int32_t timeSave;                              // таймер задержки записи изменений в EEPROM
int32_t saveDelay=1000;                        // задержка проверки необходимости записи изменений в EEPROM каждую секунду
int32_t BrightTimeStart;                       // начало отсчета включения яркой подсветки

XIIIMmoduleRGB();

void HEXtoRGB(char *hex, uint8_t modules);
void SetBrightMode(uint8_t in);
void powerON(uint8_t Module);
void powerOFF(uint8_t Module);
void Status();
void loop();

private:

boolean initOk=0;
uint8_t Relay_NUM[5];
boolean powerBeforeBright[5];                  // сохранить состояние включения до включения яркой подсветки

struct moduleRGBVal {
uint8_t Led_Value[3];
uint8_t Led_Value_Fade[3];
uint8_t Led_Value_Fade_Start[3];
uint8_t Led_Value_Old[3];
int16_t delta[3];
int16_t fadeCount=0;
int16_t steps = 0;
uint8_t Led_Pin_[3];
} lVal[5];

boolean changeColorProcess[5] = {0,0,0,0,0};   // нужно изменить цвет

struct {                                       // структура для сверки параметров текущих и записанных в EEPROM
uint8_t Led_Value_Save[3];
char hexColor[8];
char favoriteColor[8];
boolean Power;
uint8_t StartMode;
char brightColor[8];
} esave[5];

struct {                                       // структура для сверки параметров текущих и записанных в EEPROM
int16_t FadeDelay;
boolean GammaCorrection;
} esaveAll;

void deltaCalc(uint8_t module);
void SetRGBLed();
void init();
void ChangeColor();
void SaveData(boolean in);
};

void XIIIMmoduleRGB::init() {if(!InitializationOk) return; if(initOk) return;
FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN , RGB>(leds, NUM_LEDS);
for_t(0,NUM_LEDS) {leds[t] = CRGB::Black;} FastLED.show();
CMn("");

//CM("Init Relay: "); for_i(0,5) {CM(RELAY_Value_[i]); CM(" ");} CM(" SavePower: "); for_i(0,5) {CM(save.Power[i]); CM(" ");} CMn();

for_i(0, sizeof(RELAY_Pin_)) {
if(RELAY_Pin_[i]==RGBPIN0) {RELAY_Value_[i]=save.Power[0]; CM("RGB0 Relay"); Relay_NUM[0]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
if(RELAY_Pin_[i]==RGBPIN1) {RELAY_Value_[i]=save.Power[1]; CM("RGB1 Relay"); Relay_NUM[1]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
if(RELAY_Pin_[i]==RGBPIN2) {RELAY_Value_[i]=save.Power[2]; CM("RGB2 Relay"); Relay_NUM[2]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
if(RELAY_Pin_[i]==RGBPIN3) {RELAY_Value_[i]=save.Power[3]; CM("RGB3 Relay"); Relay_NUM[3]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
if(RELAY_Pin_[i]==RGBPIN4) {RELAY_Value_[i]=save.Power[4]; CM("RGB4 Relay"); Relay_NUM[4]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
if(RELAY_Pin_[i]==RGBPIN5) {RELAY_Value_[i]=save.Power[4]; CM("RGB5 Relay"); Relay_NUM[5]=i; CM(i); CM(" : "); CMn(RELAY_Value_[i]);}
}

for_t(0,NUM_LEDS) {
if(save.StartMode[t]==0) {CM("Восстанавление модуля RGB"); CM(t); CMn("."); if(save.Power[t]) {CM("Включаем модуль RGB"); CMn(t); HEXtoRGB(save.SaveModRGB[t].hexColor,t);}}
if(save.StartMode[t]==1) {powerOFF(t); CM("Выключаем модуль RGB"); CMn(t);} 
if(save.StartMode[t]==2) {CM("Установливыем любимый цвет модуля RGB"); CMn(t); HEXtoRGB(save.SaveModRGB[t].favoriteColor,t); strcpy(save.SaveModRGB[t].hexColor,save.SaveModRGB[t].favoriteColor);}
saveRelay=1;}

for_i(0,NUM_LEDS) {CM("Модуль RGB"); CM(i); CM(" управляется реле Relay"); CMn(Relay_NUM[i]);}

#if defined EEPROM_Enable
for_t(0,NUM_LEDS) {
for_i(0,3) {esave[t].Led_Value_Save[i] = save.SaveModRGB[t].Led_Value_Save[i];}
strcpy(esave[t].hexColor, save.SaveModRGB[t].hexColor);
strcpy(esave[t].favoriteColor, save.SaveModRGB[t].favoriteColor);
esave[t].Power = save.Power[t];
esave[t].StartMode = save.StartMode[t];
strcpy(esave[t].brightColor,save.SaveModRGB[t].brightColor);}
esaveAll.FadeDelay = save.FadeDelay;
esaveAll.GammaCorrection = save.GammaCorrection;
#endif
CMn("Инициализация модулей RGB завершена"); initOk=1;}

XIIIMmoduleRGB::XIIIMmoduleRGB() {
for_t(0,NUM_LEDS) {for_i(0,3) {lVal[t].Led_Value[i] = 0; lVal[t].Led_Value_Fade[i] = 0; lVal[t].Led_Value_Fade_Start[i] = 0; lVal[t].Led_Value_Old[i] = 0;
}
esaveAll.FadeDelay=4; strcpy(esave[t].hexColor,"#62006C"); strcpy(esave[t].favoriteColor,"#62006C"); esave[t].Power = 0; esaveAll.GammaCorrection = 1; esave[t].StartMode = 0; strcpy(esave[t].brightColor,"#E700FF");}}

void XIIIMmoduleRGB::Status() {CM("RGB Data Clock PINs: "); CM("Data PIN - "); CM(DATA_PIN); CM(", "); CM("Clock PIN - "); CMn(CLOCK_PIN);
for_t(0,NUM_LEDS) {CM("Текущий цвет RGB модуля"); CM(t); CM(": "); CMn(save.SaveModRGB[t].hexColor);
CM("Любимый цвет RGB модуля"); CM(t); CM(": "); CMn(save.SaveModRGB[t].favoriteColor);
CM("Яркий цвет RGB модуля"); CM(t); CM(": "); CMn(save.SaveModRGB[t].brightColor);
CM("Режим запуска модуля"); CM(t); CM(": "); if (save.StartMode[t] == 0) CMn("Восстановить цвет");
else if (save.StartMode[t] == 1) CMn("Выключить"); else if (save.StartMode[t] == 2) CMn("Любимый цвет");}
CM("Задержка перехода: "); CM(save.FadeDelay); CMn(" мс");
CM("Гамма коррекция: "); if (save.GammaCorrection) CMn("Включена"); else CMn("Выключена");
}

void XIIIMmoduleRGB::deltaCalc(uint8_t module) {int16_t coltemp = 0;
for_i(0,3) {lVal[module].Led_Value_Fade_Start[i] = lVal[module].Led_Value_Old[i]; coltemp = abs(lVal[module].Led_Value[i] - lVal[module].Led_Value_Fade_Start[i]); 
if (lVal[module].steps < coltemp) lVal[module].steps = coltemp;} lVal[module].fadeCount = 0;
CM("Модуль"); CM(module); CM(" Old: "); for_i(0,3) {CM(lVal[module].Led_Value_Old[i]); CM(" ");} 
CM(" New: "); for_i(0,3) {CM(lVal[module].Led_Value[i]); CM(" ");} CM("Шагов = "); CM(lVal[module].steps); CM(" Delta: ");
if (!lVal[module].steps) {CMn("Нечего менять, выходим"); return;}
for_i(0,3) {lVal[module].delta[i] = (abs(lVal[module].Led_Value[i] - lVal[module].Led_Value_Old[i]))*1000 / lVal[module].steps; 
CM(lVal[module].delta[i]); CM(" "); lVal[module].Led_Value_Old[i] = lVal[module].Led_Value[i];}
CMn(); changeColorProcess[module] = 1;}

int16_t hex2dec(uint8_t c) { // converts one HEX character into a number
if (c >= '0' && c <= '9') {return c - '0';} 
else if (c >= 'A' && c <= 'F') {return c - 'A' + 10;}
else if (c >= 'a' && c <= 'f') {return c - 32 - 'A' + 10;}
return '0';}

void XIIIMmoduleRGB::HEXtoRGB(char *hex, uint8_t module) {static boolean notSaveRelay; CM("Цвет HEX: "); CM(hex); CM(" -> RGB ");
lVal[module].Led_Value[0] = (hex2dec(hex[2]) + hex2dec(hex[1]) * 16);
lVal[module].Led_Value[1] = (hex2dec(hex[4]) + hex2dec(hex[3]) * 16);
lVal[module].Led_Value[2] = (hex2dec(hex[6]) + hex2dec(hex[5]) * 16);
CM("Модуль"); CM(module); CM(" реле Relay"); CM(Relay_NUM[module]); CM(": "); CM(lVal[module].Led_Value[0]); CM(" "); CM(lVal[module].Led_Value[1]); 
CM(" "); CMn(lVal[module].Led_Value[2]); 
#if defined MQTT_SendEnable
if(MQTTOk) MQTTStatus4("Color module",module,hex,"Module");
#endif
if(brightMode) notSaveRelay=1; if(notSaveRelay) {deltaCalc(module); CM("Не сохраняем состояние реле"); CM(module); CM(" = "); CMn(RELAY_Value_[Relay_NUM[module]]); if(!brightMode) notSaveRelay=0; return;}
if (!lVal[module].Led_Value[0] && !lVal[module].Led_Value[1] && !lVal[module].Led_Value[2] && RELAY_Value_[Relay_NUM[module]]  ) {
CM("Relay"); CM(Relay_NUM[module]); CM(" было "); CM(RELAY_Value_[Relay_NUM[module]]);
save.Power[module] = 0; powerBeforeBright[module]=save.Power[module]; RELAY_Value_[Relay_NUM[module]]=0;
CM(" сохранили "); CMn(RELAY_Value_[Relay_NUM[module]]);
saveRelay=1; //CM("Сохраняем Relay"); CM(Relay_NUM[module]); CM(" = "); CMn(RELAY_Value_[Relay_NUM[module]]);
// MQTTStatus4("Relay",module,false,"Relay");
} 
else if ((lVal[module].Led_Value[0] || lVal[module].Led_Value[1] || lVal[module].Led_Value[2]) && !RELAY_Value_[Relay_NUM[module]]  ) {
CM("Relay"); CM(Relay_NUM[module]); CM(" было "); CM(RELAY_Value_[Relay_NUM[module]]);
save.Power[module] = 1; powerBeforeBright[module]=save.Power[module]; RELAY_Value_[Relay_NUM[module]]=1;
CM(" сохранили "); CMn(RELAY_Value_[Relay_NUM[module]]);
saveRelay=1;
//MQTTStatus4("Relay",module,true,"Relay");
}
deltaCalc(module);}

void XIIIMmoduleRGB::SetBrightMode(uint8_t in) {static boolean brightLight; if(brightLight==brightMode) return; MQTTStatus("BrightMode",brightMode);
// если нужно исключить возврат цвета, то in - номер модуля, которому не возвращаем цвет
if (in<5) {powerBeforeBright[in]=RELAY_Value_[Relay_NUM[in]]; CM("Не возвращаем цвет модуля "); CM(in); CM(" (реле "); CM(Relay_NUM[in]); CMn(")");}
CM("Переключаем Bright Mode в "); CMn(brightMode); brightLight=brightMode;
if(!brightLight && !standByShot) {for_t(0,NUM_LEDS) {if (in!=t) {CM("Возвращаем цвет модуля "); CMn(t);
if(!powerBeforeBright[t]) {save.Power[t]=0; for_i(0,3) lVal[t].Led_Value[i]=0; deltaCalc(t); MQTTStatus4("Color module",t,save.SaveModRGB[t].hexColor,"Module");} else {
HEXtoRGB(save.SaveModRGB[t].hexColor,t);}}}} else {CMn("Включаем яркую подсветку"); BrightTimeStart=millis(); 
for_t(0,NUM_LEDS) {powerBeforeBright[t]=save.Power[t]; CM("save.Power module"); CM(t); CM(" = "); CMn(save.Power[t]); 
if(!save.Power[t]) {save.Power[t]=1;} HEXtoRGB(save.SaveModRGB[t].brightColor,t);} timeSave = millis();}}

void XIIIMmoduleRGB::powerOFF(uint8_t Module) {if(!save.Power[Module]) return; save.Power[Module] = 0; powerBeforeBright[Module]=save.Power[Module];
if(!brightMode) {for_i(0,3) lVal[Module].Led_Value[i]=0; CM("Power: OFF module"); CMn(Module); deltaCalc(Module);}}

void XIIIMmoduleRGB::powerON(uint8_t Module) {if(!save.Power[Module]) {CM("Power: ON module"); CMn(Module); save.Power[Module] = 1; powerBeforeBright[Module]=save.Power[Module];}
if (!strcmp(save.SaveModRGB[Module].hexColor,"#000000")) {HEXtoRGB(save.SaveModRGB[Module].favoriteColor,Module); 
strcpy(save.SaveModRGB[Module].hexColor,save.SaveModRGB[Module].favoriteColor); return;} HEXtoRGB(save.SaveModRGB[Module].hexColor,Module);}

void XIIIMmoduleRGB::SetRGBLed() {static long fadeTimer; if (millis() - fadeTimer < save.FadeDelay) return; fadeTimer = millis();
for_t(0,NUM_LEDS) {if (changeColorProcess[t]) { //CM("RGB"); CM(t); CM(": "); for_i(0,3) {CM(lVal[t].Led_Value[i]); CM(" ");} CM(" <- ");
for_i(0,3) {if (lVal[t].Led_Value_Fade[i] < lVal[t].Led_Value[i]) lVal[t].Led_Value_Fade[i] = lVal[t].Led_Value_Fade_Start[i] + round(lVal[t].delta[i]*lVal[t].fadeCount/1000); 
else if (lVal[t].Led_Value_Fade[i] > lVal[t].Led_Value[i]) lVal[t].Led_Value_Fade[i] = lVal[t].Led_Value_Fade_Start[i] - round(lVal[t].delta[i]*lVal[t].fadeCount/1000);
if (lVal[t].Led_Value_Fade[i] > 255) lVal[t].Led_Value_Fade[i] = 255; if (lVal[t].Led_Value_Fade[i] < 0) lVal[t].Led_Value_Fade[i] = 0;
lVal[t].Led_Value_Old[i] = lVal[t].Led_Value_Fade[i]; //CM(lVal[t].Led_Value_Fade[i]); CM(" ");
}
if(save.GammaCorrection) {leds[t].r=GammaCorrection::CorrectTable8(lVal[t].Led_Value_Fade[0]); leds[t].g=GammaCorrection::CorrectTable8(lVal[t].Led_Value_Fade[1]);
leds[t].b=GammaCorrection::CorrectTable8(lVal[t].Led_Value_Fade[2]);} else {leds[t].r=lVal[t].Led_Value_Fade[0]; leds[t].g=lVal[t].Led_Value_Fade[1];
leds[t].b=lVal[t].Led_Value_Fade[2];} FastLED.show(); //CMn();
lVal[t].fadeCount++;
if (lVal[t].fadeCount > lVal[t].steps) {changeColorProcess[t] = 0; lVal[t].steps = 0; for_i(0,3) {lVal[t].Led_Value_Old[i] = lVal[t].Led_Value[i]; 
save.GammaCorrection ? lVal[t].Led_Value[i]=GammaCorrection::CorrectTable8(lVal[t].Led_Value_Fade[i]) : lVal[t].Led_Value[i]=lVal[t].Led_Value[i];
leds[t].r=lVal[t].Led_Value[0]; leds[t].g=lVal[t].Led_Value[1]; leds[t].b=lVal[t].Led_Value[2]; FastLED.show();}}}}}

void XIIIMmoduleRGB::SaveData(boolean in) {if(standBy || standByShot || standByQuick) {timeSave = millis(); saveDelay = 5000; return;}
if (!in && millis() - timeSave < saveDelay) return; timeSave = millis(); //CMn("Проверка изменения данных для EEPROM");
saveDelay = 1000; boolean needSave=0; if (in) goto goSave;
for_t(0,NUM_LEDS) {
for_i(0,3) if(save.SaveModRGB[t].Led_Value_Save[i] != esave[t].Led_Value_Save[i]) {esave[t].Led_Value_Save[i] = save.SaveModRGB[t].Led_Value_Save[i]; needSave=1;}
if (strcmp(save.SaveModRGB[t].hexColor,esave[t].hexColor)) {strcpy(esave[t].hexColor, save.SaveModRGB[t].hexColor); needSave=1;}
if (strcmp(save.SaveModRGB[t].favoriteColor,esave[t].favoriteColor)) {strcpy(esave[t].favoriteColor, save.SaveModRGB[t].favoriteColor); needSave=1;}
if (save.Power[t] != esave[t].Power) {esave[t].Power = save.Power[t]; needSave=1;}
if (save.StartMode[t] != esave[t].StartMode) {esave[t].StartMode = save.StartMode[t]; needSave=1;}
if (strcmp(save.SaveModRGB[t].brightColor, esave[t].brightColor)) {strcpy(esave[t].brightColor,save.SaveModRGB[t].brightColor); needSave=1;}}
if (save.FadeDelay != esaveAll.FadeDelay) {esaveAll.FadeDelay = save.FadeDelay; needSave=1;}
if (save.GammaCorrection != esaveAll.GammaCorrection) {esaveAll.GammaCorrection = save.GammaCorrection; needSave=1;}
if(!needSave) return; // {CMn("Ничего не изменилось. Нечего сохранять."); return;
goSave:;
#if defined EEPROM_Enable
CMn("Есть изменения данных. Сохраняем данные");
#if defined ledIndikator_Enable
Led.SaveInd=1;
#endif
saveChange=1;
#endif
}

void XIIIMmoduleRGB::ChangeColor() {returnSec(1); 
//CM("Relay: "); for_i(0,5) {CM(RELAY_Value_[i]); CM(" ");} CM(" SavePower: "); for_i(0,5) {CM(save.Power[i]); CM(" ");} CMn(); return;
uint8_t Value[3];
for_i(0,3) Value[i]=random(5,180); CM("Red: "); CM(Value[0]); CM(" Green: "); CM(Value[1]); CM(" Blue: "); CM(Value[2]);
char hex[8] = {0}, hexColor[8]={"#"}; sprintf(hex,"%02X%02X%02X",Value[0],Value[1],Value[2]); CM(" HEX: "); CMn(hex);
strcat(hexColor,hex); HEXtoRGB(hexColor,0);}

void XIIIMmoduleRGB::loop(){ //static uint32_t loops; loops++; returnSec(1); CM("Loops in sec: "); CMn(loops); loops=0;
init(); if(!initOk) return;
SetRGBLed();
SetBrightMode(9);
SaveData(0);
//ChangeColor();
}

#endif // XIIIMmoduleRGB_h