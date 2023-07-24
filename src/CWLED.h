#ifndef XIIIMCWLED_h
#define XIIIMCWLED_h

#pragma once
#include <Arduino.h>

#define writeLed(x,i) analogWrite(x,255-i)

class XIIIMCWLED {
public:

uint8_t Led_Pin_[2];
uint8_t Relay_PIN;
boolean pc_2mode = 0;                           // Если включаем дежурный режим с ПК
XIIIMCWLED(uint8_t Cold_PIN, uint8_t Warm_PIN);

boolean switchLED;
void SwitchLED();
void deltaCalc();
void loop();

private:

void SetLED();
void StandByLight();

boolean mode=0;                                 // Normal / Night light mode
uint8_t Led_Value_[2];                          // Cold | Warm
uint8_t Led_Value_Fade_[2];
uint8_t Led_Value_Fade_Start_[2];
uint8_t Led_Value_Old_[2];
int16_t delta[2];
int16_t fadeCount = 0;
int16_t steps = 0;
boolean changeColorProcess = 0;                 // нужно изменить цвет

};

XIIIMCWLED::XIIIMCWLED(uint8_t Cold_PIN, uint8_t Warm_PIN) {Led_Pin_[0] = Cold_PIN; Led_Pin_[1] = Warm_PIN;
for_i(0,2) {pinMode(Led_Pin_[i], OUTPUT); writeLed(Led_Pin_[i], 0); Led_Value_[i] = 0; Led_Value_Fade_[i] = 0; Led_Value_Fade_Start_[i] = 0; Led_Value_Old_[i] = 0;}}

void XIIIMCWLED::deltaCalc() {int16_t coltemp = 0; double Cl[2], Wl[2];
if (RELAY_Value_[Relay_PIN]) {switch(mode) {
case 0: Cl[0]=((2.55*save.currentLight)/100)*save.ColdWarm; Cl[1]=((2.55*save.currentLight)/100)*(100-save.ColdWarm); Led_Value_[0]=Cl[0]; Led_Value_[1]=Cl[1]; break;
case 1: Wl[0]=((2.55*save.nightLight)/100)*save.ColdWarm; Wl[1]=((2.55*save.nightLight)/100)*(100-save.ColdWarm); Led_Value_[0]=Wl[0]; Led_Value_[1]=Wl[1]; break;}
} else {Led_Value_[0]=0; Led_Value_[1]=0;}
COMPort(" Cold Old: "); COMPort(Led_Value_Old_[0]); COMPort(" -> New: "); COMPortln(Led_Value_[0]);
for_i(0,2) {Led_Value_Fade_Start_[i] = Led_Value_Old_[i]; coltemp = abs(Led_Value_[i] - Led_Value_Fade_Start_[i]); 
if (steps < coltemp) steps = coltemp;} fadeCount = 0; COMPort("Шагов = "); COMPort(steps); COMPort(" Delta: ");
if (!steps) {COMPortln("Нечего менять, выходим"); return;}
for_i(0,2) {delta[i] = (abs(Led_Value_[i] - Led_Value_Old_[i]))*1000 / steps; COMPort(delta[i]); COMPort(" "); Led_Value_Old_[i] = Led_Value_[i];}
COMPortln(); changeColorProcess = 1;}

void XIIIMCWLED::SetLED() {if (!changeColorProcess) return; static uint32_t fadeTimer; static uint16_t summValue;
if (millis() - fadeTimer < save.fadeDelay+summValue) return; fadeTimer = millis();
changeColorProcess = 0; for_i(0,2) {if (Led_Value_Fade_[i] != Led_Value_[i]) changeColorProcess = 1;}
COMPort("LED: "); for_i(0,2) {COMPort(Led_Value_[i]); COMPort(" ");} COMPort(" <- ");
for_i(0,2) {if (Led_Value_Fade_[i] < Led_Value_[i]) Led_Value_Fade_[i] = Led_Value_Fade_Start_[i] + round(delta[i]*fadeCount/1000); 
else if (Led_Value_Fade_[i] > Led_Value_[i]) Led_Value_Fade_[i] = Led_Value_Fade_Start_[i] - round(delta[i]*fadeCount/1000);
if (Led_Value_Fade_[i] > 255) Led_Value_Fade_[i] = 255; if (Led_Value_Fade_[i] < 0) Led_Value_Fade_[i] = 0;
Led_Value_Old_[i] = Led_Value_Fade_[i];
COMPort(Led_Value_Fade_[i]); COMPort(" "); 
writeLed(Led_Pin_[i],Led_Value_Fade_[i]);} summValue=(Led_Value_Fade_[0]+Led_Value_Fade_[1]);
summValue = map(summValue, 0, 255, 10, 0); ;fadeCount++;
COMPortln();
if (fadeCount > steps) {changeColorProcess = 0; steps = 0; for_i(0,2) {Led_Value_Old_[i] = Led_Value_[i]; writeLed(Led_Pin_[i],Led_Value_[i]);}}
}

void XIIIMCWLED::SwitchLED() {static uint32_t timeSw; if(!switchLED) return; COMPort("Светильник "); 
if(millis()-timeSw < 500) return; timeSw=millis();
switch (RELAY_Value_[Relay_PIN]) {
case 0: COMPortln("выключаем"); break;
case 1: mode=0; COMPortln("включаем"); break;
case 2: mode=1; COMPortln("в дежурный режим"); break;}
deltaCalc(); saveRelay=1; switchLED=0;}

void XIIIMCWLED::StandByLight() {static uint8_t munualStandByQuick;
if(!RELAY_Value_[Relay_PIN] && standByShot && !standBy && !standByQuick && save.autoMode) {RELAY_Value_[Relay_PIN]=2; switchLED=1;}
if(!munualStandByQuick && standByQuick) {RELAY_Value_[Relay_PIN]=2; switchLED=1; munualStandByQuick=1;}
if(munualStandByQuick && !RELAY_Value_[Relay_PIN]) munualStandByQuick=0;
if(pc_2mode && RELAY_Value_[Relay_PIN]!=2) pc_2mode=0;
return1sec;
if(RELAY_Value_[Relay_PIN] && !standByQuick && munualStandByQuick) {munualStandByQuick=0; RELAY_Value_[Relay_PIN]=0; switchLED=1;}
if(pc_2mode) return;
if(RELAY_Value_[Relay_PIN]==2 && !standByShot && !standBy && !standByQuick && save.autoMode) {RELAY_Value_[Relay_PIN]=0; switchLED=1;}
}

void XIIIMCWLED::loop() {
SwitchLED();
SetLED();
StandByLight();
}

#endif // XIIIMCWLED_h