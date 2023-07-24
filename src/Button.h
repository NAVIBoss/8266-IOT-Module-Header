// управление c кнопок (0+1 & 0(3сек) - изменение задержки кнопок(0-, 1+); 1+0 & 1(3сек) - обучаемая задержка); 1+0(3сек) вых из пр-я
#ifndef XIIIMButton_h
#define XIIIMButton_h

#define _BTN_DEB_STEPS 10                       // количество подсчетов фиксированного состояния кнопки для определения нажатия
#define _BTN_HOLD 400                           // время фиксации одиночного клика, если не было последующих нажатий
#define _BTN_COEFFICIETNT 0.80                  // коэффициент на который умножается 500ms для установки вермени BTN_HOLD
#define _BTN_LONG 150                           // время фиксации длинного нажатия, если кнопка не была отпущена

#pragma once
#include <Arduino.h>

#ifndef BTN_DEB_STEPS
#define BTN_DEB_STEPS _BTN_DEB_STEPS
#endif

#ifndef BTN_HOLD
#define BTN_HOLD _BTN_HOLD
#endif

#ifndef BTN_COEFFICIETNT
#define BTN_COEFFICIETNT _BTN_COEFFICIETNT
#endif

#ifndef BTN_LONG
#define BTN_LONG _BTN_LONG
#endif

#define for_i(from, to) for(uint8_t i=(from); i < (to); i++)
#define for_x(from, to) for(uint8_t x=(from); x < (to); x++)

#define readPIN(x) if(sizeof(btn) > x+1 && !digitalRead(btn[x])) bitSet(mScene0, x)

class XIIIMButton {
public:
XIIIMButton();
XIIIMButton(boolean m);
XIIIMButton(boolean m, const int b0);
XIIIMButton(boolean m, const int b0, const int b1);
XIIIMButton(boolean m, const int b0, const int b1, const int b2);
XIIIMButton(boolean m, const int b0, const int b1, const int b2, const int b3);
uint8_t mumOfPINs=1;
boolean programInd=0;
uint8_t btn[4];
uint8_t scan();
void status();

//--------------------------------------------- переопределяемые параметры ---------------------------------------------
int16_t BtnDbSt=BTN_DEB_STEPS;
int16_t BtnHOLD=BTN_HOLD;
int16_t BtnLONG=BTN_LONG;
double Btnkf=BTN_COEFFICIETNT; // BTN_HOLD=500*BTN_COEFFICIETNT
//--------------------------------------------- переопределяемые параметры ---------------------------------------------

void setSteps(int set) {if(set>255) BtnDbSt=255; else if(set<4) BtnDbSt=4; else BtnDbSt=set;}
void setHold(int set) {if(set>2000) BtnHOLD=2000; else if(set<400) BtnHOLD=400; else BtnHOLD=set;}
void setKoef(double set) {if(set>4.00) Btnkf=4.00; else if(set<0.80) Btnkf=0.80; else Btnkf=set; BtnHOLD=500*Btnkf;}
void setLong(int set) {if(set>1000) BtnLONG=1000; else if(set<150) BtnLONG=150; else BtnLONG=set;}

private:
void statusScene(uint8_t SCENE) {CM("SCENE: "); CM(SCENE); if(shotPress==1) CM(" Shot"); if(doublePress) CM(" Double"); if(longPress) CM(" Long"); CMn();}
};

void XIIIMButton::status() {CM("Назначен"); if(mumOfPINs>1) CM("ы"); CM(" пин"); if(mumOfPINs>1) CM("ы"); CM(" на кнопк");
if(mumOfPINs>1) CM("и"); else CM("у"); CM(": ");
for_i(0,mumOfPINs) {CM(btn[i]); if (i<mumOfPINs-1) CM(","); CM(" ");} CMn("");}

XIIIMButton::XIIIMButton() {btn[0]=0; pinMode(btn[0], INPUT_PULLUP);}

XIIIMButton::XIIIMButton(boolean m) {btn[0]=0;
switch (m) {
case 0: pinMode(btn[0], INPUT_PULLUP);
case 1: pinMode(btn[0], INPUT);}}

XIIIMButton::XIIIMButton(boolean m, const int b0) {
btn[0]=0; switch (m) {
case 0: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT_PULLUP);} break;
case 1: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT);} break;}}

XIIIMButton::XIIIMButton(boolean m, const int b0, const int b1) {
btn[0]=b0; btn[1]=b1; mumOfPINs=2; switch (m) {
case 0: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT_PULLUP);} break;
case 1: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT);} break;}}

XIIIMButton::XIIIMButton(boolean m, const int b0, const int b1, const int b2) {
btn[0]=b0; btn[1]=b1; btn[2]=b2; mumOfPINs=3; switch (m) {
case 0: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT_PULLUP);} break;
case 1: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT);} break;}}

XIIIMButton::XIIIMButton(boolean m, const int b0, const int b1, const int b2, const int b3) {
btn[0]=b0; btn[1]=b1; btn[2]=b2; btn[3]=b3; mumOfPINs=4; switch (m) {
case 0: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT_PULLUP);} break;
case 1: for_x(0,mumOfPINs) {pinMode(btn[x], INPUT);} break;}}

uint8_t XIIIMButton::scan() {static uint8_t SCENE;
static int16_t press; static boolean pressEvent, EventEND, firstPressUp, secondPressUP, secondPress, differentKey; boolean registr=0;
static uint32_t pressStartTime, Press_StopTime, btTime; static uint8_t mScene0, mScene1;
// ----------------------------------------------------------------------------------------------------- Программирование
#if defined EEPROM_Enable
BtnHOLD=500*Btnkf;
#else
BtnHOLD=BTN_HOLD;
#endif
static boolean prgMode[4], progMode; // режимы программирования
if(progMode) {
#if defined EEPROM_Enable
static int32_t progModeTime; static uint32_t pressDelay; // измеренное время двойного нажатия
if(prgMode[3]) BtnHOLD=2000; if(progMode) {
static boolean count20, startProg; static int16_t countLearn; char value[8];
if (!startProg) {progModeTime=millis(); startProg=1; pressDelay=400;}

if (SCENE == 3 && longPress) {programInd=0; CMn("Программирование завершено");
if (prgMode[3]) {CM("Задержка кнопки: "); dtostrf(Btnkf,1,2,value); CM(value); CM(" : "); dtostrf(500*Btnkf,1,0,value); CM(value); CMn(" мсек.");}
dtostrf(Btnkf,1,2,value); for_i(0,4) prgMode[i]=0; progMode=0; countLearn=0; startProg=0; BtnHOLD=500*Btnkf; statusScene(34); return 34;}

if (millis() - progModeTime > 30000) {for_i(0,4) prgMode[i]=0; progMode=0; startProg=0; countLearn=0; CMn("Превышено время ожидания"); programInd=0; return 0;}

if (prgMode[3] && pressEvent) {static uint32_t startTime; static boolean startPress; if(!startPress && !secondPress) {startPress=1; startTime=millis();}
if (startPress && secondPress) {int32_t roundDelay; SCENE=0; pressDelay=millis()-startTime;
progModeTime=millis();
static int16_t learnTime[20]; learnTime[countLearn]=pressDelay; if (countLearn>19) {count20=1; countLearn=0;}
countLearn++;
CM("Клик: "); CMn(countLearn);
int16_t allTime=0; for_i(0,20) allTime+=learnTime[i]; CM("Двойной клик="); CM(pressDelay+100); CM(" мсек.");
if(!count20) roundDelay=allTime/countLearn+100; else roundDelay=allTime/20+100;
Btnkf=roundDelay/500.00;
if (Btnkf<0.80) Btnkf=0.80; if (Btnkf > 4.00) Btnkf=4.00; startPress=0;
dtostrf(Btnkf,1,2,value); CM(value); CM(" : "); dtostrf(500*Btnkf,1,0,value); CM(value); CMn(" мсек.");
dtostrf(Btnkf,1,2,value);} if(!pressEvent) startPress=0;}

if (prgMode[2]) {static double saveDelay;
if (SCENE == 1 && shotPress) Btnkf-=0.05;
if (SCENE == 1 && longPress) Btnkf-=0.20;
if (SCENE == 2 && shotPress) Btnkf+=0.05;
if (SCENE == 2 && longPress) Btnkf+=0.20;
if(saveDelay != Btnkf) {saveDelay=Btnkf; SCENE=0;
if (Btnkf<0.80) Btnkf=0.80; if (Btnkf > 4.00) Btnkf=4.00; dtostrf(Btnkf,1,2,value);
CM("Задержка кнопки: "); CM(value); CM(" : "); dtostrf(500*Btnkf,1,0,value); CM(value); CMn(" мсек.");
progModeTime=millis();}}}
#endif
} // ----------------------------------------------------------------------------------------------------- Программирование
if(millis()-Press_StopTime < 100) return 0;
if (millis() == btTime) return 0; btTime=millis();
for_i(0,mumOfPINs) if (!digitalRead(btn[i])) registr=1;
if (press>=0 && press < BtnDbSt && registr) press++; if (press<=0 && press > -BtnDbSt && !registr) press--; 
if (press > 0 && !registr) press=0; if (press < 0 && registr) press=0; if (press > -BtnDbSt && press < BtnDbSt) return 0;
if (!pressEvent && !registr) return 0;

if (!registr && press == -BtnDbSt && pressEvent && (EventEND && millis()-Press_StopTime > 200)) {firstPressUp=0; pressEvent=0; shotPress=0; 
longPress=0; doublePress=0; secondPress=0; secondPressUP=0; differentKey=0; EventEND=0; return 0;}

if (EventEND && SCENE==16 && !progMode && longPress && millis() - pressStartTime > 3000) {prgMode[0]=1; programInd=1; progMode=1; CMn("Режим программирования 0"); statusScene(32); return 30;}
if (EventEND && SCENE==17 && !progMode && longPress && millis() - pressStartTime > 3000) {prgMode[1]=1; programInd=1; progMode=1; CMn("Режим программирования 1"); statusScene(33); return 31;}
if (EventEND && SCENE==19 && !progMode && longPress && millis() - pressStartTime > 3000) {prgMode[2]=1; programInd=1; progMode=1; CMn("Програм-е задержек кнопки"); statusScene(34); return 32;}
if (EventEND && SCENE==27 && !progMode && longPress && millis() - pressStartTime > 3000) {prgMode[3]=1; programInd=1; progMode=1; CMn("Обучение двойного нажатия"); statusScene(35); return 33;}

if (EventEND) return 0;
if (press == BtnDbSt && !pressEvent) {pressEvent=1; pressStartTime=millis(); SCENE=0; mScene0=0; mScene1=0;} // нажали 1 раз
if (press == -BtnDbSt && pressEvent && !firstPressUp) firstPressUp=1; // отпустили 1 раз
if (!secondPress && press == BtnDbSt && pressEvent && firstPressUp) {secondPress=1; pressStartTime=millis();} // нажали 2 раз
if (press == -BtnDbSt && pressEvent && firstPressUp && secondPress && !secondPressUP) secondPressUP=1; // отпустили 2 раз

if (!firstPressUp && !secondPress && pressEvent) {
if (!digitalRead(btn[0])) bitSet(mScene0, 0); // SCENE1 - 0001, SCENE2 - 0010, SCENE3 - 0011, SCENE4 - 0100 и т.д.
if (mumOfPINs > 1 && !digitalRead(btn[1])) bitSet(mScene0, 1); // для получения правильной SCENE замкнуть соответствующие пины через диоды
if (mumOfPINs > 2 && !digitalRead(btn[2])) bitSet(mScene0, 2);
if (mumOfPINs > 3 && !digitalRead(btn[3])) bitSet(mScene0, 3);
} else if (firstPressUp && secondPress && pressEvent) {
if (!digitalRead(btn[0])) bitSet(mScene1, 0); // SCENE1 - 0001, SCENE2 - 0010, SCENE3 - 0011, SCENE4 - 0100 и т.д.
if (mumOfPINs > 1 && !digitalRead(btn[1])) bitSet(mScene1, 1); // для получения правильной SCENE замкнуть соответствующие пины через диоды
if (mumOfPINs > 2 && !digitalRead(btn[2])) bitSet(mScene1, 2);
if (mumOfPINs > 3 && !digitalRead(btn[3])) bitSet(mScene1, 3);
if (!differentKey && secondPress && mScene0!=mScene1) {differentKey=1;}
}

if (press == BtnDbSt && secondPress && pressEvent && millis() - pressStartTime >= BtnLONG) {doublePress=1; longPress=1;
SCENE=mScene0;
if(differentKey) {
if (bitRead(mScene0,0) && !bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 2: SCENE=16; break;
case 3: SCENE=18; break;
case 4: SCENE=24; break;
}} else if (!bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=17; break;
case 3: SCENE=26; break;
case 4: SCENE=20; break;
}} else if (bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=19; break;
case 2: SCENE=27; break;
case 4: SCENE=22; break;
}} else if (!bitRead(mScene0,0) && !bitRead(mScene0,1) && bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=25; break;
case 3: SCENE=21; break;
case 4: SCENE=23; break;
}}} //CM("But Scene "); CM(SCENE); CM(" "); CMn("doublePress longPress");
EventEND=1; Press_StopTime=millis(); statusScene(SCENE); return SCENE;}

if (press == BtnDbSt && !secondPress && pressEvent && millis() - pressStartTime >= BtnLONG) {longPress=1;
SCENE=mScene0;
if(differentKey) {
if (bitRead(mScene0,0) && !bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 2: SCENE=16; break;
case 3: SCENE=18; break;
case 4: SCENE=24; break;
}} else if (!bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=17; break;
case 3: SCENE=26; break;
case 4: SCENE=20; break;
}} else if (bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=19; break;
case 2: SCENE=27; break;
case 4: SCENE=22; break;
}} else if (!bitRead(mScene0,0) && !bitRead(mScene0,1) && bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=25; break;
case 3: SCENE=21; break;
case 4: SCENE=23; break;
}}} //CM("But Scene "); CM(SCENE); CM(" "); CMn("longPress");
EventEND=1; Press_StopTime=millis(); statusScene(SCENE); return SCENE;}

if (pressEvent && !firstPressUp) return 0;

if (!prgMode[3] && press == -BtnDbSt && millis() - pressStartTime > BtnHOLD && !secondPress && mScene0 != 0) {shotPress=1; // отпустили быстро
SCENE=mScene0; //CM("But Scene "); CM(SCENE); CM(" "); CMn("shotPress");
EventEND=1; Press_StopTime=millis(); statusScene(SCENE); return SCENE;}

if (pressEvent && !secondPress) return 0;

if (secondPressUP && millis() - pressStartTime <= BtnHOLD) {doublePress=1; // двойное нажатие кнопки
SCENE=mScene0; if(differentKey) {
if (bitRead(mScene0,0) && !bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 2: SCENE=16; break;
case 3: SCENE=18; break;
case 4: SCENE=24; break;
}} else if (!bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=17; break;
case 3: SCENE=26; break;
case 4: SCENE=20; break;
}} else if (bitRead(mScene0,0) && bitRead(mScene0,1) && !bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=19; break;
case 2: SCENE=27; break;
case 4: SCENE=22; break;
}} else if (!bitRead(mScene0,0) && !bitRead(mScene0,1) && bitRead(mScene0,2)) {switch (mScene1) {
case 1: SCENE=25; break;
case 2: SCENE=21; break;
case 3: SCENE=23; break;
}}} //CM("But Scene "); CM(SCENE); CM(" "); CMn("doublePress");
EventEND=1; Press_StopTime=millis(); statusScene(SCENE); return SCENE;} return 0;}

#endif // XIIIMButton_h