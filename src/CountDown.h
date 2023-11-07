#ifndef XIIIMCountDown_h
#define XIIIMCountDown_h

#pragma once
#include <Arduino.h>

class XIIIMCount {
public:

void loop();

private:

void StandByCountDown();
void StandByShotCountDown();
void StandByQuickCountDown();
#if defined kitchenVent_Enable || defined MasterBathRoom
void VentCountDown();
#endif
#if defined MasterSceneKitchen
void WashCountDown();
#endif
};

void XIIIMCount::StandByCountDown() {returnSec(1); static boolean standBySave;
#if defined EEPROM_Enable && defined MQTT_SendEnable && not defined GlobalHouseSwitch
if(!save.MASTER_ESP) for_t(0,10) if(strcmp("",save.controlTopic[t])) return;
#endif
if(standBySave!=standBy) {standBySave=standBy; MQTTStatus("StandBy",standBy); if(standBySave) {standByTimeStart=millis(); standByShot=0; standByQuick=0;}}
if(!save.autoMode || !standBy || standByQuick) return; static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min;
if (millis() - standByTimeStart < save.standByTime*1000) {
sec = (save.standByTime*1000 - (millis() - standByTimeStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal==roundVal) return;
CM("Выкл. StandBy через: "); CM(roundVal); if(min) {CMn(" мин.");} else {CMn(" сек.");}
if(saveVal!=roundVal || !min) {if(min) {MQTTStatus3("StandByOffTime",roundVal,"min");} else {MQTTStatus3("StandByOffTime",roundVal,"sec");}
}} else {standBy=0; CMn("Выкл. standBy по таймеру.");
#if defined MasterBathRoom
brightMode=0;
RELAY_Value_[0]=0; RELAY_Value_[1]=0; RELAY_Value_[3]=0;
if (!RELAY_Value_Save_[1] && RELAY_Value_[1]) {mRGB.powerON(0); CMn("StandBy вкл RGB Power0");}
else if (RELAY_Value_Save_[1] && !RELAY_Value_[1]) {mRGB.powerOFF(0); CMn("StandBy выкл RGB Power0");}
if (!RELAY_Value_Save_[2] && RELAY_Value_[2]) {mRGB.powerON(1); CMn("StandBy вкл RGB Power1");}
else if (RELAY_Value_Save_[2] && !RELAY_Value_[2]) {mRGB.powerOFF(1); CMn("StandBy выкл RGB Power1");}
#if defined RelayEnable || defined RGB_LED_Enable || defined RGB_MODULE_LED_Enable
for_i(0,sizeof(RELAY_Pin_)) if (RELAY_Value_Save_[i] != RELAY_Value_[i]) {CM("StandByOff реле "); CM(i); CM(" в "); CMn(RELAY_Value_[i]);} saveRelay=1;
#endif
#endif
}saveVal=roundVal;}

void XIIIMCount::StandByShotCountDown() {returnSec(1); static boolean standBySave;
if (!save.MASTER_ESP) for_t(0,10) if(strcmp("",save.controlTopic[t])) return;
if(standBySave!=standByShot) {standBySave=standByShot; MQTTStatus("StandByShot",standByShot); if(standBySave) {brightMode=1;
#if defined MasterBedRoom && defined MQTT_SendEnable
Comm.command(save.LEDTopic[0],"BrightMode","1"); // включение яркой LED в спальне на движение
#endif
standByTimeStart=millis();} else if (!standByQuick) {brightMode=0;
#if defined MasterBedRoom && defined MQTT_SendEnable
Comm.command(save.LEDTopic[0],"BrightMode","0");
#endif
}}

if(!save.autoMode || !standByShot || standByQuick || standBy) return; static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min;
if (millis() - standByTimeStart < save.standByShotTime*1000) {
sec = (save.standByShotTime*1000 - (millis() - standByTimeStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal==roundVal) return;
CM("Выкл. StandByShot через: "); CM(roundVal); if(min) {CMn(" мин.");} else {CMn(" сек.");}
if(saveVal!=roundVal || !min) {if(min) {MQTTStatus3("StandByShotOffTime",roundVal,"min");} else {MQTTStatus3("StandByShotOffTime",roundVal,"sec");}
}} else {standByShot=0; 
CMn("Выкл. standByShot по таймеру.");} saveVal=roundVal;}

void XIIIMCount::StandByQuickCountDown() {returnSec(1); static boolean standBySave;
#if defined EEPROM_Enable
if(!save.MASTER_ESP) for_t(0,10) if(strcmp("",save.controlTopic[t])) return;
#endif
if(standBySave!=standByQuick) {standBySave=standByQuick; MQTTStatus("StandByQuick",standByQuick); if(standBySave) {brightMode=1; standByTimeStart=millis(); standBy=0; standByShot=0;} else {brightMode=0;}}
if(!standByQuick) return; static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min;
if (millis() - standByTimeStart < save.standByQuickTime*1000) {
sec = (save.standByQuickTime*1000 - (millis() - standByTimeStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal==roundVal) return;
CM("Выкл. StandByQuick через: "); CM(roundVal); if(min) {CMn(" мин.");} else {CMn(" сек.");}
if(saveVal!=roundVal || !min) {if (min) {MQTTStatus3("StandByQuickOffTime",roundVal,"min");} else {MQTTStatus3("StandByQuickOffTime",roundVal,"sec");}
}} else {standByQuick=0; CMn("Выкл. standByQuick по таймеру.");} saveVal=roundVal;}

#if defined kitchenVent_Enable // Задержка отключения вытяжки кухни после отключения света
void XIIIMCount::VentCountDown() {returnSec(1); static boolean holdVentTemp, holdVentHUM, holdVentTime;
static uint32_t startVentAutoTime; // начало отсчета времени выкл вытяжки, после перекл реле и когда только вытяжка

if(!standBy && !holdVentTime && !ventStandBy && RELAY_Value_[4] && !RELAY_Value_[2]) {ventStandBy=1; startVentAutoTime=millis(); 
MQTTStatus("VentStandBy",ventStandBy); CMn("Вкл. таймер вытяжки");}

#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
if(save.autoMode) {if (!holdVentTemp && (tempC/10)>=save.thresholdTemp) {CMn("Вкл. превышение температуры"); holdVentTemp=1;}
else if (holdVentTemp && (tempC/10)<(save.thresholdTemp-save.hysteresisTemp)) {CMn("Выкл. превышение температуры"); holdVentTemp=0;}
if (!holdVentHUM && humidity>=save.thresholdHUM) {CMn("Вкл. превышение влажности"); holdVentHUM=1;}
else if (holdVentHUM && humidity<(save.thresholdHUM-save.hysteresisHUM)) {CMn("Выкл. превышение влажности"); holdVentHUM=0;}}
#endif

#if (defined RelayEnable || defined RGB_LED_Enable || defined RGB_MODULE_LED_Enable) && defined CommandToRelay
if(!RELAY_Value_[4] && (holdVentTemp || holdVentHUM) && save.autoMode) {RELAY_Value_[4] = 1; saveRelay=1; 
MQTTStatus4("Relay",4,RELAY_Value_[4],"Relay"); CMn("Включили вытяжку");}
if(RELAY_Value_[4] && !ventStandBy && !holdVentTemp && !holdVentHUM && !standBy && save.autoMode) {RELAY_Value_[4] = 0; saveRelay=1; 
MQTTStatus4("Relay",4,RELAY_Value_[4],"Relay"); CMn("Выключили вытяжку"); holdVentTime=0;}
#endif

if(standBy || (RELAY_Value_[4] && RELAY_Value_[2])) holdVentTime=0;
if(!RELAY_Value_[4] || (RELAY_Value_[4] && RELAY_Value_[2])) ventStandBy=0;

if(!RELAY_Value_[4] || (RELAY_Value_[4] && RELAY_Value_[2]) || standBy || holdVentTime) return;
//if(!ventStandBy) {ventStandBy=1; startVentAutoTime=millis(); MQTTStatus("VentStandBy",ventStandBy);}
static uint32_t sec, saveVal, roundVal; if (millis() - startVentAutoTime >= save.ventAutoTime*1000) {
if(ventStandBy) {CMn("Выкл. таймер вытяжки"); ventStandBy=0; holdVentTime=1; MQTTStatus("VentStandBy",ventStandBy);} return;}

sec = (save.ventAutoTime*1000 - (millis() - startVentAutoTime));
(sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000; if(saveVal==roundVal && sec>=60000) return;
CM("Выкл. таймер через: "); if (sec>=60000) {CM(roundVal); CMn(" мин.");} else {CM(sec/1000); CMn(" сек.");}
if(saveVal!=roundVal || sec<60000) {sec>=60000 ? MQTTStatus3("VentOffTime",roundVal,"min") : MQTTStatus3("VentOffTime",sec/1000,"sec");
if(sec>=60000) saveVal=roundVal; else saveVal=0;}}
#endif

#if defined MasterBathRoom // Задержка отключения вытяжки ванной после отключения света
void XIIIMCount::VentCountDown() {returnSec(1); static boolean holdVentTime; boolean holdVentRelay=0;
static uint32_t startVentAutoTime; // начало отсчета времени выкл вытяжки, после перекл реле и когда только вытяжка

if(save.autoMode) {if(RELAY_Value_[0] || RELAY_Value_[1] || RELAY_Value_[3]) holdVentRelay=1; else holdVentRelay=0;}

if(!standBy && !holdVentTime && !ventStandBy && RELAY_Value_[4] && !holdVentRelay) {ventStandBy=1; startVentAutoTime=millis(); 
MQTTStatus("VentStandBy",ventStandBy); CMn("Вкл. таймер вытяжки");}

#if (defined RelayEnable || defined RGB_LED_Enable || defined RGB_MODULE_LED_Enable) && defined CommandToRelay
if(RELAY_Value_[4] && !ventStandBy && !holdVentRelay && !standBy && save.autoMode) {RELAY_Value_[4] = 0; saveRelay=1; 
CMn("Выключили вытяжку"); holdVentTime=0;}
#endif

if(standBy || (RELAY_Value_[4] && holdVentRelay)) holdVentTime=0;
if(ventStandBy && (!RELAY_Value_[4] || (RELAY_Value_[4] && holdVentRelay))) {ventStandBy=0; MQTTStatus("VentStandBy",ventStandBy); return;}

if(!RELAY_Value_[4] || (RELAY_Value_[4] && holdVentRelay) || standBy) return;
static uint32_t sec, saveVal, roundVal; if (millis() - startVentAutoTime >= save.ventAutoTime*1000) {
if(ventStandBy) {CMn("Выкл. таймер вытяжки"); ventStandBy=0; holdVentTime=1; MQTTStatus("VentStandBy",ventStandBy);} return;}

sec = (save.ventAutoTime*1000 - (millis() - startVentAutoTime));
(sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000; if(saveVal==roundVal && sec>=60000) return;
CM("Выкл. таймер через: "); if (sec>=60000) {CM(roundVal); CMn(" мин.");} else {CM(sec/1000); CMn(" сек.");}
if(saveVal!=roundVal || sec<60000) {if(sec>=60000) {MQTTStatus3("VentOffTime",roundVal,"min");} else {MQTTStatus3("VentOffTime",sec/1000,"sec");}
if(sec>=60000) saveVal=roundVal; else saveVal=0;}}
#endif

#if defined MasterSceneKitchen                 // Управляющий блок над мойкой в кухне
void XIIIMCount::WashCountDown() {if(!WorkZoneLight) return;
if(WorkZoneLight && (standBy || standByQuick || !RELAY_Value_[2])) {WorkZoneLight=0; return;} //CMn("Выкл. Раб зону."); RELAY_Value_[2]=0; saveRelay=1;
#if defined EEPROM_Enable
if(!save.autoMode) {WorkZoneLight=0; return;}
#endif
#if defined MotionSens_Enable
if(MotionSensor) return;
#endif
returnSec(1);
static uint32_t sec, saveVal, roundVal; if (millis() - motionWashStart < save.MotionWashTime*1000) {

sec = (save.MotionWashTime*1000 - (millis() - motionWashStart));

(sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000; if(saveVal==roundVal && sec>=60000) return;

CM("Выкл. Раб зону через: "); if (sec>=60000) {CM(roundVal); CMn(" мин.");} else {CM(sec/1000); CMn(" сек.");}
if(saveVal!=roundVal || sec<60000) {sec>=60000 ? MQTTStatus3("Wash Off Light",roundVal,"min") : MQTTStatus3("Wash Off Light",sec/1000,"sec");
if (sec>=60000) saveVal=roundVal; else saveVal=0;}} else {CMn("Выкл. Раб зону по таймеру.");
#if (defined RelayEnable || defined RGB_LED_Enable || defined RGB_MODULE_LED_Enable) && defined CommandToRelay
RELAY_Value_[2] = 0; saveRelay=1; MQTTStatus4("Relay",2,RELAY_Value_[2],"Relay");
#endif
}}
#endif

void XIIIMCount::loop() {
if(save.standByTime) StandByCountDown();
if(save.standByShotTime) StandByShotCountDown();
if(save.standByQuickTime) StandByQuickCountDown();
#if defined MasterSceneKitchen
WashCountDown();
#endif
#if defined kitchenVent_Enable || defined MasterBathRoom
VentCountDown();
#endif
}

#endif //XIIIMCountDown_h