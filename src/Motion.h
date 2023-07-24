#ifndef XIIIMMotion_h
#define XIIIMMotion_h

#pragma once
#include <Arduino.h>

#if defined ledIndikator_Enable
#define syncInd(x) Led.SyncInd=x
#else
#define syncInd(x)
#endif

#if defined MQTT_SendEnable
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTStat(x,y,z) Comm.status(x,y,z)
#else
#define MQTTStatus(x,y)
#define MQTTStat(x,y,z)
#endif

class XIIIMMotion {
public:

XIIIMMotion(uint8_t PIN);
uint8_t MotionSens_PIN;                        // PIN сенсора vibro

#if defined MasterSceneKitchen
boolean MotionWashEnable = 1;                  // реагировать на движение возле мойки на кухне
uint8_t MotionWashTime = 40;                   // время включения раб зоны кухни от движения возле мойки
#endif

void loop();

private:

uint8_t vibroCount=0;

void EventMoution();
void MotionSensCountDown();
};

XIIIMMotion::XIIIMMotion(uint8_t PIN) {MotionSens_PIN=PIN; pinMode(MotionSens_PIN, INPUT);}

void XIIIMMotion::EventMoution() {if (!save.MotionDetectEnable) return; if(MotionSensor) {return1sec;} if(!digitalRead(MotionSens_PIN) && !MotionSensor) return; boolean ctrlTopic=0;
if(millis()-timeMotionIgnore<save.MotionIgnore*1000) {CMn("Игнорим движение"); return;}
if (digitalRead(MotionSens_PIN)) motionStart=millis();
if(ctrlTopic) MQTTStatus("MotionSensor",MotionSensor); // отсылаем каждую сек для топика
if (MotionSensor) {standByTimeStart=millis(); 
#if defined MasterSceneKitchen
motionWashStart = millis();
#endif
return;}
if (digitalRead(MotionSens_PIN)) {syncInd(1); MotionSensor = 1; CMn("Обнаружено движение");
#if defined EEPROM_Enable
for_t(0,10) {if(!ctrlTopic && strcmp("",save.controlTopic[t])) ctrlTopic=1;}
#endif
if(!save.MASTER_ESP) {MQTTStatus("MotionSensor",MotionSensor); if (save.MASTER_ESP) {MQTTStatus("Motion",1); Motion=1;}
if(save.autoMode && !standBy && !standByShot && !standByQuick && !ctrlTopic) {standByShot=1; CMn("Включаем standByShot");}}
standByTimeStart=millis();
#if defined MasterSceneKitchen
if(!WorkZoneLight && !RELAY_Value_[2] && save.autoMode && save.MotionWashEnable && !standBy && !standByQuick) {
WorkZoneLight=1; RELAY_Value_[2]=1; saveRelay=1; CMn("Вкл подсветку раб зоны");}
#endif
}}

void XIIIMMotion::MotionSensCountDown() {if(!MotionSensor) return; return1sec; uint8_t MotionOnMemory = 3;
static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min; boolean ctrlTopic=0;
#if defined EEPROM_Enable
MotionOnMemory=save.MotionOnMemory;
#endif
if (millis() - motionStart < save.MotionOnMemory*1000) {
sec = (MotionOnMemory*1000 - (millis() - motionStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal==roundVal) return;
CM("Выкл. Motion Sensor через: "); CM(roundVal); if(min) CMn(" мин."); else CMn(" сек.");}
#if defined MotionSens_Enable && defined PresenceSens_Enable
else if(!Presen.Presence)
#else
else
#endif
{MotionSensor=0; CMn("Выкл. Motion Sensor по таймеру."); 
#if defined EEPROM_Enable
for_t(0,10) {if(!ctrlTopic && strcmp("",save.controlTopic[t])) ctrlTopic=1;}
#endif
if(!ctrlTopic && !save.MASTER_ESP) {MQTTStatus("MotionSensor",MotionSensor);}
} saveVal=roundVal;}

void XIIIMMotion::loop() {
#if defined MotionSens_Enable
EventMoution();
MotionSensCountDown();
#else
#if defined MQTT_SendEnable && defined EEPROM_Enable
if(save.MASTER_ESP) MotionCountDown();
#endif
#endif
}

#endif // XIIIMMotion_h