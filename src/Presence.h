#ifndef XIIIMPresence_h
#define XIIIMPresence_h

#pragma once
#include <Arduino.h>

#if defined ledIndikator_Enable
#define syncInd(x) Led.SyncInd=x
#else
#define syncInd(x)
#endif

class XIIIMPresence {
public:
XIIIMPresence(uint8_t PIN);
boolean Presence;
uint8_t PresenceSens_PIN;                        // PIN сенсора присутствия

void loop();

private:
boolean PresenceSensor = 0;                     // состояние датчика присутствия
uint32_t presenceSenseStart;                    // начало отсчета времени саработки датчика присутствия
uint32_t timePresenceIgnore;                    // время начала игнорирования присутствия

void EventPresence();
void PresenceSensCountDown();
};

XIIIMPresence::XIIIMPresence(uint8_t PIN) {PresenceSens_PIN=PIN; pinMode(PresenceSens_PIN, INPUT);}

void XIIIMPresence::EventPresence() {if(PresenceSensor) {return1sec;} 
if(!digitalRead(PresenceSens_PIN) && !PresenceSensor) return; boolean ctrlTopic=0;
if(millis()-timePresenceIgnore<save.PresenceIgnore*1000) {CMn("Игнорим присутствие"); return;}
if (digitalRead(PresenceSens_PIN)) {presenceSenseStart=millis();
if (!PresenceSensor && digitalRead(PresenceSens_PIN)) {syncInd(1); PresenceSensor = 1; CMn("Обнаружено присутствие");}
if(!save.PresenceDetectEnable) Presence=1;
if(standByShot && PresenceSensor) {standByTimeStart=millis();}}}

void XIIIMPresence::PresenceSensCountDown() {
if(PresenceSensor && !save.PresenceDetectEnable) {PresenceSensor=0; CMn("Обнаружение присутствия деактивировано");}
if(!save.PresenceDetectEnable) return;
if(!PresenceSensor) return; return1sec; uint8_t PresenceOnMemory = 3;
static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min; boolean ctrlTopic=0;
#if defined EEPROM_Enable
PresenceOnMemory=save.PresenceOnMemory;
#endif
if(standByShot) motionStart=millis();
if (millis() - presenceSenseStart < PresenceOnMemory*1000) {sec = (PresenceOnMemory*1000 - (millis() - presenceSenseStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal==roundVal) return;
CM("Выкл. Presence Sensor через: "); CM(roundVal); if(min) CMn(" мин."); else CMn(" сек.");} else {
PresenceSensor=0; Presence=0; CMn("Выкл. Presence Sensor по таймеру.");} saveVal=roundVal;
if(standByShot) {
#if defined EEPROM_Enable
for_t(0,10) {if(!ctrlTopic && strcmp("",save.controlTopic[t])) ctrlTopic=1;}
#endif
if(!save.MASTER_ESP && !MotionSensor) {MQTTStatus("MotionSensor",1);} MotionSensor=1;
if (save.MASTER_ESP) {MQTTStatus("Motion",1); Motion=1;}}}

void XIIIMPresence::loop() {EventPresence(); PresenceSensCountDown();}

#endif // XIIIMPresence_h