#ifndef XIIIMLed_h
#define XIIIMLed_h

#pragma once
#include <Arduino.h>

#if defined InverseOutIndikator
#define dBlueLED(x) digblueLED(!x)
#define aBlueLED(x) anblueLED(255-x)
#else
#define dBlueLED(x) digblueLED(x)
#define aBlueLED(x) anblueLED(x)
#endif

#if not defined MonoIndikator
#define dRedLED(x) digredLED(x)
#define aRedLED(x) anredLED(x)
#else
#define aRedLED(x)
#endif

class XIIIMLED {
public:

XIIIMLED();
XIIIMLED(uint8_t PinBlue);
XIIIMLED(uint8_t PinBlue, uint8_t PinRed);
boolean ProgramInd=0;
boolean ventStandByInd=0;
boolean SaveInd=0;
boolean NoWifiInd=1;
boolean StandByInd=0;
boolean StandByShotInd=0;
boolean StandByQuickInd=0;
boolean NoAutoModeInd=0;
boolean SyncInd=0;

uint8_t blueLED=LED_BUILTIN;
uint8_t redLED=99;

void status();
void loop();

private:

void Program();
void ventStandBy();
void Save();
void NoWifi();
void StandBy();
void StandByShot();
void StandByQuick();
void Sync();
void NoAutoMode();

void State();
void digblueLED(boolean x);
void anblueLED(uint8_t x);
#if not defined MonoIndikator
void digredLED(boolean x);
void anredLED(uint8_t x);
#endif
};

XIIIMLED::XIIIMLED() {pinMode(blueLED, OUTPUT); dBlueLED(1);}
XIIIMLED::XIIIMLED(uint8_t PinBlue) {blueLED=PinBlue; pinMode(blueLED, OUTPUT); dBlueLED(1);}
XIIIMLED::XIIIMLED(uint8_t PinBlue, uint8_t PinRed) {blueLED=PinBlue; pinMode(blueLED, OUTPUT); dBlueLED(1); redLED=PinRed; 
#if not defined MonoIndikator
pinMode(redLED, OUTPUT); dRedLED(0);
#endif
}

void XIIIMLED::status() {CM("LED Blue PIN: "); CMn(blueLED);
#if not defined MonoIndikator
CM("LED Red PIN: "); CMn(redLED);
#endif
}

void XIIIMLED::digblueLED(boolean in) {digitalWrite(blueLED,in);}
void XIIIMLED::anblueLED(uint8_t in) {analogWrite(blueLED,in);}
#if not defined MonoIndikator
void XIIIMLED::digredLED(boolean in) {digitalWrite(redLED,in);}
void XIIIMLED::anredLED(uint8_t in) {analogWrite(redLED,in);}
#endif

void XIIIMLED::StandBy() {
if(!StandByInd || StandByQuickInd || SyncInd || ProgramInd || NoWifiInd || ventStandByInd || SaveInd) return;
static int16_t stateBlue, result; static uint32_t timeLag, timeHold;
if(millis()-timeLag<4) return; timeLag=millis();
#if not defined MonoIndikator
static int16_t stateRed;
#endif
result=millis()-timeHold; if(millis()-timeHold>2400) timeHold=millis();
if (result<1200 && stateBlue<255) {stateBlue+=1; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if (result>710 && result<1810 && stateRed<255) {stateRed+=1; aRedLED(stateRed);}
#endif
if (result>1300 && stateBlue>0) {stateBlue-=1; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if ((result>1910 || result<710) && stateRed>0) {stateRed-=1; if (stateRed<0) stateRed=0; aRedLED(stateRed);}
#endif
}

void XIIIMLED::StandByShot() {
if(!StandByShotInd || StandByInd || StandByQuickInd || SyncInd || ProgramInd || NoWifiInd || ventStandByInd || SaveInd) return;
static int16_t stateBlue, result; static uint32_t timeLag, timeHold;
#if not defined MonoIndikator
if(millis()-timeLag<2) return; 
#else
if(millis()-timeLag<4) return; 
#endif
timeLag=millis();
#if not defined MonoIndikator
static int16_t stateRed;
#endif
result=millis()-timeHold; if(millis()-timeHold>3200) timeHold=millis();
if (result<1200 && stateBlue<255) {stateBlue+=1; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if (result>710 && result<1810 && stateRed<255) {stateRed+=1; aRedLED(stateRed);}
#endif
if (result>1300 && stateBlue>0) {stateBlue-=1; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if ((result>1910 || result<710) && stateRed>0) {stateRed-=1; aRedLED(stateRed);}
if (result>2670 && result<2760) {dBlueLED(1); aRedLED(127);}
if (result>2760 && result<2765) {dBlueLED(0); dRedLED(0);}
#else
if (result>2670 && result<2760) {dBlueLED(1);}
if (result>2760 && result<2765) {dBlueLED(0);}
#endif
}

void XIIIMLED::StandByQuick() {if(!StandByQuickInd || SyncInd || ProgramInd || NoWifiInd || ventStandByInd || SaveInd) return;
static uint32_t timeLag; static uint8_t mode;
if(mode==5 && millis()-timeLag < 400) return;
if(millis()-timeLag < 50) return; timeLag=millis(); 
#if not defined MonoIndikator
switch (mode) {
case 1: case 3: case 5: dRedLED(0); dBlueLED(0); break;
case 0: aRedLED(127); aBlueLED(127); break;
case 2: aRedLED(70); aBlueLED(140); break;
//case 4: redLED(0); blueLED(1); break;
} mode++;
if(mode>5) mode=0;
#else
static boolean state;
state=!state; mode++; if(mode>5) {mode=0; state=0;} dBlueLED(!state);
#endif
}

void XIIIMLED::Sync() {if(!SyncInd) return; static uint32_t timeLag; static uint8_t mode;
if(millis()-timeLag < 50) return; timeLag=millis(); 
#if not defined MonoIndikator
switch (mode) {
case 1: case 3: case 5: dRedLED(0); dBlueLED(0); break;
case 0: aRedLED(127); aBlueLED(127); break;
case 2: aRedLED(70); aBlueLED(140); break;
case 4: dRedLED(0); dBlueLED(1); break;} mode++;
if(mode>6) {mode=0; SyncInd=0; dBlueLED(1); dRedLED(0);}
#else
static boolean state;
state=!state; dBlueLED(state); mode++; if(mode>6) {mode=0; state=0; SyncInd=0; dBlueLED(1);}
#endif
}

void XIIIMLED::NoWifi() {
//CM("Условия: "); CM(" "); CM(NoWifiInd); CM(" "); CM(MQTTOk); CM(" "); CM(masterSyncOk); CM(" "); CM(ProgramInd); CM(" "); CM(ventStandByInd); CM(" "); CMn(SaveInd);
if(!NoWifiInd || SyncInd || ProgramInd || ventStandByInd || SaveInd) return;
static uint8_t mode; static uint32_t timeLag;
switch (mode) {
case 0: if(millis()-timeLag < 1200) return; break;
case 1: if(millis()-timeLag < 150) return; break;
default : if(millis()-timeLag < 40) return; break;}
timeLag = millis(); if(mode==0 || mode==2) {
#if not defined MonoIndikator
dRedLED(1);
#else
dBlueLED(1);
#endif
} else {
#if not defined MonoIndikator
dRedLED(0);
#endif
dBlueLED(0);}
mode++; if(mode>3) mode=0;}

void XIIIMLED::NoAutoMode() {if(!NoAutoModeInd || StandByQuickInd || NoWifiInd || SyncInd || StandByInd || StandByShotInd || ventStandByInd || ProgramInd || SaveInd) return;
static uint8_t mode; static uint32_t timeLag;
if(mode==1 && millis()-timeLag < 3000) return;
if((mode==0 || mode==2 || mode==4) && millis()-timeLag < 50) return;
if(millis()-timeLag < 10) return; timeLag = millis();
if(mode==1 || mode==3 || mode==5) {
#if not defined MonoIndikator
aRedLED(10); aBlueLED(30);
#else
aBlueLED(50); 
#endif
} else {
#if not defined MonoIndikator
dRedLED(0);
#endif
dBlueLED(1);
} mode++; if(mode>5) mode=0;}

void XIIIMLED::Save() {if(!SaveInd || SyncInd) return;
static uint8_t mode, blueOut, redOut;  static uint32_t time; uint16_t timeLag; static boolean start;
if(mode==0) timeLag=4; else timeLag=60;
if(millis()-time < timeLag) return; time=millis(); 
if(!start) {start=1; timeLag = millis(); blueOut=255;
#if not defined MonoIndikator
redOut=0;
#endif
}
switch (mode) {
case 0: if(blueOut>0) blueOut--; aBlueLED(blueOut); if(blueOut==0) mode++;
#if not defined MonoIndikator
if(redOut<255) redOut++; aRedLED(redOut); 
#endif
break;
case 1: dBlueLED(1); break;
case 2: dBlueLED(0); break;
case 3: 
#if not defined MonoIndikator
aRedLED(192); aBlueLED(64);
#else
dBlueLED(1);
#endif
break;
case 4: dBlueLED(0);
#if not defined MonoIndikator
dRedLED(0);
#endif
break;
case 5: 
#if not defined MonoIndikator
dRedLED(1);
#else
dBlueLED(1); 
#endif
break;
case 6: dBlueLED(0);
#if not defined MonoIndikator
dRedLED(0);
#endif
break;
case 7: dBlueLED(1); break;
case 8: dBlueLED(0);
#if not defined MonoIndikator
dRedLED(0);
#endif
break;
}
if(mode>0) mode++; if(mode==9) {SaveInd=0; start=0; mode=0; dBlueLED(1);}
}

void XIIIMLED::ventStandBy() {if(!ventStandByInd || StandByQuickInd || ProgramInd || SyncInd || SaveInd) return; // вытяжка на кухне
static int16_t stateBlue, result; static uint32_t timeLag;
#if not defined MonoIndikator
static int16_t stateRed;
#endif
result=millis()-timeLag; if(millis()-timeLag>1200) timeLag=millis();
if (result<150 && stateBlue<255) {stateBlue+=3; if(stateBlue>255) stateBlue=255; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if (result>100 && result<150+55 && stateRed<255) {stateRed+=3; aRedLED(stateRed);}
#endif
if (result>150 && stateBlue>0) {stateBlue-=2; aBlueLED(stateBlue);}
#if not defined MonoIndikator
if (result>150+85 && stateRed>0) {stateRed-=2; if (stateRed<0) stateRed=0; aRedLED(stateRed);}
#endif
}

void XIIIMLED::Program() {if(!ProgramInd || SyncInd || SaveInd) return;
static uint8_t mode; static uint32_t timeLag;
switch (mode) {
case 0: if(millis()-timeLag < 1200) return; break;
case 2: if(millis()-timeLag < 150) return; break;
case 3: if(millis()-timeLag < 70) return; break;}
timeLag = millis(); switch (mode) {
case 0:
aBlueLED(127); break;
case 2:
#if not defined MonoIndikator
aRedLED(127);
#else
aBlueLED(127);
#endif
break;
case 3:
#if not defined MonoIndikator
dRedLED(0);
#endif
dBlueLED(0); break;}
mode++; if(mode>3) mode=0;}

void XIIIMLED::State() {static boolean state, stateSave; returnSec(1);   // если нет индикации, то должен гореть                                                                           // только синий
//CM("Индикаторы: "); CM("ProgramInd "); CM(ProgramInd); CM(" ventStandByInd "); CM(ventStandByInd); CM(" SaveInd "); CM(SaveInd); CM(" NoWifiInd "); CM(NoWifiInd); CM(" StandByInd "); CM(StandByInd); CM(" StandByShotInd "); CM(StandByShotInd); CM(" StandByQuickInd "); CM(StandByQuickInd); CM(" NoAutoModeInd "); CM(NoAutoModeInd); CM(" SyncInd "); CMn(SyncInd);
if(!ProgramInd && !ventStandByInd && !SaveInd && !NoWifiInd && !StandByInd && !StandByShotInd && !StandByQuickInd && !NoAutoModeInd && !SyncInd) state=1; else state=0;
if(stateSave!=state) {stateSave=state; if(state) {dBlueLED(1);
#if not defined MonoIndikator
dRedLED(0);
#endif
}}}

void XIIIMLED::loop() {
State();                                   // Состояние индикатора
Sync();                                    // Синхронизация
NoWifi();                                  // Нет сети, не синхронизации
StandBy();                                 // Ожидание
StandByShot();                             // Отсчет подсветки при движении
StandByQuick();                            // Отсчет дежурной подсветки на 15 сек.
NoAutoMode();                              // Авто режим отключен
Program();                                 // Программирование
ventStandBy();                               // Обратный отсчет
Save();                                    // Сохранили данные
}
#endif // XIIIMLed_h