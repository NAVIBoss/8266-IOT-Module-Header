#ifndef XIIIMVibro_h
#define XIIIMVibro_h

#pragma once
#include <Arduino.h>

#define readVibroSensor !digitalRead(VibroSens_PIN)
#if defined MQTT_SendEnable
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTStat(x,y,z) Comm.status(x,y,z)
#else
#define MQTTStatus(x,y)
#define MQTTStat(x,y,z)
#endif

class XIIIMVibro {
public:

XIIIMVibro(uint8_t PIN, uint8_t r_PIN);
uint8_t VibroSens_PIN;                         // PIN сенсора vibro
uint8_t VibroSensor = 0;                       // состояние сенсора 0-нет 1-превышает барьер 2-не превышает барьер
boolean VibroDetectEnable = 1;                 // использовать сенсор вибрации или звукового давления
uint8_t timeIgnoreVibroEvent = 10;             // время не реагируем после сработки сенсора (сек)
int16_t vibroLevel = 1000;                     // порог превышения вибрации
uint8_t vibroTimePlus = 30;                    // сколько времени добавляем (мин)
uint8_t vibroCountSave = 3;                    // на какой раз сработки запускаем Event
int16_t vibroCountReset = 180;                 // сброс счетчика событий, если сенсор не сработал, через (сек)
uint8_t vibroWarnTime = 5;                     // сколько времени отображаем сработку сенсора (сек)
uint8_t timeStep = 25;                         // время шага (Мсек)
uint16_t timeWait = 400;                       // время между шагами (Мсек)
uint8_t minSteps = 2;                          // минимум шагов
uint8_t maxSteps = 4;                          // максимум шагов
uint8_t minNext = 2;                           // минимальное время после шагов до следующих (сек)
uint8_t maxNext = 20;                          // максимальное время после шагов до следующих (сек)
uint32_t VibroTimer = 0;                       // счетчик оставшегося времени

void loop();

private:

uint8_t vibroCount=0;
uint8_t Relay_PIN=3;                           // PIN управления вибро

void EventSmash();
void VibroCountDown();
void step();
void init();
};

XIIIMVibro::XIIIMVibro(uint8_t PIN, uint8_t r_PIN) {VibroSens_PIN=PIN; pinMode(VibroSens_PIN, INPUT); Relay_PIN=r_PIN;}

void XIIIMVibro::init() {static boolean init; if(init) return; init=1;
#if defined EEPROM_Enable
VibroDetectEnable=save.VibroDetectEnable;
timeIgnoreVibroEvent=save.timeIgnoreVibroEvent;
vibroLevel=save.vibroLevel;
vibroTimePlus=save.vibroTimePlus;
vibroCountSave=save.vibroCount;
vibroCountReset=save.vibroCountReset;
vibroWarnTime=save.vibroWarnTime;
timeStep=save.timeStep;
timeWait=save.timeWait;
minSteps=save.minSteps;
maxSteps=save.maxSteps;
minNext=save.minNext;
maxNext=save.maxNext;
pinMode(Relay_PIN, OUTPUT); writeRelay(Relay_PIN,0);
CM("PIN управления вибро: "); CMn(Relay_PIN); MQTTStatus("Vibro Step PIN",Relay_PIN);
#endif
}

void XIIIMVibro::EventSmash() {if (!VibroDetectEnable) return; static int readValue, smashValueSave, maxValue; static uint32_t eTime, stopTime;
char topic[70], value[70]; if (readVibroSensor) readValue++;

if (millis() - eTime < 100) return; eTime = millis();
static uint32_t smashTime;
static boolean warning;
bool smashGO;
int CountResetTime;
if (timeIgnoreVibroEvent * 1000 > 60 * 1000) CountResetTime = 60 * 1000; else CountResetTime = timeIgnoreVibroEvent * 1000 / 2;
if (timeIgnoreVibroEvent > vibroCountReset) CountResetTime = vibroCountReset * 1000 / 2;
if (readValue > vibroLevel) smashGO = 1; else smashGO = 0;
if (readValue > 0) stopTime = millis();

if (readValue < smashValueSave - 5 || readValue > smashValueSave + 5) {smashValueSave = readValue;
if (VibroSensor && maxValue < smashValueSave) {maxValue = smashValueSave; MQTTStatus("VibroValue",maxValue);}
if (!VibroSensor && maxValue > smashValueSave) {maxValue = smashValueSave; MQTTStatus("VibroValue",maxValue);}}

if (VibroSensor == 0 && readValue > 0 && !smashGO) {VibroSensor = 2; CMn("VibroSensor = 2"); MQTTStatus("VibroSensor",VibroSensor);}

readValue = 0;

if (VibroSensor > 0 && millis() - stopTime > vibroWarnTime * 1000) {
VibroSensor = 0; CMn("VibroSensor = 0"); MQTTStatus("VibroSensor",VibroSensor); MQTTStatus("VibroValue",0);}

if (vibroCount > 0 && !smashGO && millis() - smashTime >= vibroCountReset * 1000) {
CM("VibroSensor отключен дольше "); CM(vibroCountReset); CMn(" сек. Сброс счетчика."); MQTTStatus("vibroCount",0);
warning = 0; vibroCount = 0; return;}

if (warning && millis() - smashTime < timeIgnoreVibroEvent * 1000) return;

warning = 0;
if (vibroCount > 0 && !smashGO && millis() - smashTime < vibroCountReset * 1000) return; smashTime = millis();

if (VibroSensor!=1 && smashGO) {CMn("VibroSensor = 1"); VibroSensor = 1; MQTTStatus("VibroSensor",VibroSensor);
vibroCount++; warning = 1; CM("Счетчик событий: "); CMn(vibroCount); MQTTStatus("vibroCount",vibroCount);
if (vibroCount < vibroCountSave) return;
vibroCount = 0; CM("Счетчик событий: "); CMn(vibroCount); MQTTStatus("vibroCount",vibroCount);
VibroTimer += vibroTimePlus * 60 * 1000; CM("Добавили "); CM(vibroTimePlus); CMn(" мин.");
CM("Вибро таймер: "); CM(VibroTimer/60000); CMn(" мин.");
if(!RELAY_Value_Save_[0]) {RELAY_Value_[0]=1; MQTTStatus("Relay0",RELAY_Value_[0]); RELAY_Value_Save_[0]=RELAY_Value_[0];
// saveRelay=1;
}}}

void XIIIMVibro::VibroCountDown() {static uint32_t vibroTime; char topic[50], value[50]; if (VibroTimer <= 0) return;
static uint32_t timeLag, TimeRand; static boolean state; static uint32_t saveValue, sendValue; 
//if(millis()-TimeRand > timeLag) {TimeRand=millis();
//state=!state; writeRelay(RELAY_Pin_[0],state); if(state) timeLag=random(100,1000); else timeLag=random(50,300);}
return1sec;
VibroTimer-1000 < VibroTimer ? VibroTimer-=1000 : VibroTimer=0; if(VibroTimer) {//CM("VibroTimer = "); CMn(VibroTimer); 
if (VibroTimer>=60000) {(VibroTimer/1000)%60>29 ? sendValue=VibroTimer/60000+1 : sendValue=VibroTimer/60000; 
if(saveValue!=sendValue) {CM("Выкл. вибро через: "); CM(sendValue); CMn(" мин"); MQTTStat("VibroTimer",sendValue,"min");}} else {
sendValue=VibroTimer/1000; if(saveValue!=sendValue) {CM("Выкл. вибро через: "); CM(sendValue); CMn(" сек"); MQTTStat("VibroTimer",sendValue,"sec");}}
saveValue=sendValue;} else {CMn("Выкл. вибро по таймеру."); RELAY_Value_[0]=0; MQTTStatus("Relay0",RELAY_Value_[0]); VibroTimer=0; saveRelay=1;}}

void XIIIMVibro::step() {static boolean begin, relay; static uint8_t st, steps; static uint32_t timeLag, lastTime, waitTime, waitStep;
if(VibroTimer <= 0) {if(relay) {writeRelay(Relay_PIN,0); 
RELAY_Value_[0]=0; MQTTStatus("Relay0",RELAY_Value_[0]); RELAY_Value_Save_[0]=RELAY_Value_[0];
relay=0;} begin=0; return;}
if(!begin) {st=random(minSteps,maxSteps); begin=1;}
if((millis()-waitTime)<waitStep) return;
if((millis()-lastTime)<timeLag) return; lastTime=millis();

if(steps<st) {relay=!relay; writeRelay(Relay_PIN,relay); if(relay) {steps++; timeLag=timeStep;} else timeLag=timeWait+random(0,200); return;}

writeRelay(Relay_PIN,0); steps=0; waitTime=millis(); waitStep=random(minNext*1000, maxNext*1000); begin=0;

}

void XIIIMVibro::loop() {VibroCountDown(); EventSmash(); step(); init();}

#endif // XIIIMVibro_h