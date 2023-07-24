#ifndef XIIIMIR_h
#define XIIIMIR_h

#pragma once
#include <Arduino.h>

#if defined MQTT_SendEnable
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTStat(x,y,z) Comm.status(x,y,z)
#else
#define MQTTStatus(x,y)
#define MQTTStat(x,y,z)
#endif

class XIIIMIR {
public:

XIIIMIR(uint8_t PIN);
uint8_t scan();
uint8_t IrSens_PIN;
private:
void statusScene() {standBy=1; COMPort("SCENE: 31"); if(shotPress==1) COMPort(" Shot"); if(doublePress) COMPort(" Double"); if(longPress) COMPort(" Long"); COMPortln();}
};

XIIIMIR::XIIIMIR(uint8_t PIN) {IrSens_PIN=PIN; pinMode(IrSens_PIN, INPUT);}

uint8_t XIIIMIR::scan() {static int16_t press; static boolean pressEvent, EventEND, firstPressUp, IRsens; boolean registr;
static uint32_t pressStartTime, IrTime, StopTime;
if(millis()-StopTime < 100) return 0;
registr = !digitalRead(IrSens_PIN);

if (millis() == IrTime) return 0; IrTime = millis();
if (press>=0 && press < 10 && registr) press++; if (press<=0 && press > -10 && !registr) press--; 
if (press > 0 && !registr) press = 0; if (press < 0 && registr) press = 0; if (press > -10 && press < 10) return 0;
if (!pressEvent && !registr) return 0;

if (!registr && press == -10 && pressEvent && EventEND) {firstPressUp = 0; pressEvent = 0; EventEND=0;
shotPress=0; longPress=0; doublePress=0; return 0;}

if (EventEND) return 0;

if (press == 10 && !pressEvent) {pressEvent = 1; pressStartTime = millis(); IRsens=0;}
if (!IRsens && !digitalRead(IrSens_PIN)) IRsens=1; // SCENE 31 - IR Sensor
if (press == 10 && !firstPressUp && pressEvent && millis() - pressStartTime >= 200) {longPress = 1;
EventEND=1; StopTime=millis(); statusScene(); return 31;}
if (press == -10 && pressEvent && !firstPressUp) firstPressUp = 1; // отпустили 1 раз
if (pressEvent && !firstPressUp) return 0;
if (press == -10 && millis() - pressStartTime > 400 && IRsens) { // отпустили быстро
shotPress = 1; EventEND=1; StopTime=millis(); statusScene(); return 31;}
if (press == 10 && IRsens && millis() - pressStartTime <= 400) {doublePress = 1; // двойной взмах
EventEND=1; StopTime=millis(); statusScene(); return 31;} return 0;}

#endif // XIIIMIR_h