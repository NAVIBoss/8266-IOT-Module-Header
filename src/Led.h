#ifndef XIIIMLed_h
#define XIIIMLed_h

#pragma once
#include <Arduino.h>

#if defined InverseOutIndikator
#define dBlueLED(x) digitalWrite(blueLED,!x)
#define aBlueLED(x) analogWrite(blueLED,255-x)

#else
#define dBlueLED(x) digitalWrite(blueLED,x)
#define aBlueLED(x) analogWrite(blueLED,x)
#endif

#if not defined MonoIndikator
#define dRedLED(x) digitalWrite(redLED,x)
#define aRedLED(x) analogWrite(redLED,x)
#else
#define aRedLED(x)
#define dRedLED(x)
#endif

#if defined led3ColorIndikator_Enable
#define dBlueLED(x)
#define aBlueLED(x)
#define dRedLED(x)
#define aRedLED(x)
#endif

class XIIIMLED {
public:

XIIIMLED();
XIIIMLED(uint8_t PinBlue);
XIIIMLED(uint8_t PinBlue, uint8_t PinRed);
XIIIMLED(uint8_t Pin1Red, uint8_t Pin1Green, uint8_t Pin1Blue, uint8_t Pin2Red, uint8_t Pin2Green, uint8_t Pin2Blue);

uint8_t blueLED=LED_BUILTIN;
uint8_t redLED=99;
uint8_t red0LED=99; // левый
uint8_t red1LED=99; // правый
uint8_t green0LED=99;
uint8_t green1LED=99;
uint8_t blue0LED=99;
uint8_t blue1LED=99;

boolean Save_I=0;
boolean Program_I=0;
boolean NoWifi_I=0;
boolean NoMQTT_I=0;
boolean NoSync_I=0;
boolean Sync_I0=0;
boolean Sync_I1=0;
boolean ventStandBy_I=0;
boolean StandByQuick_I=0;
boolean StandByShot_I=0;
boolean StandBy_I=0;
boolean Lon_I=0;
boolean Ron_I=0;
boolean NoAutoMode_I=0;

#if defined led3ColorIndikator_Enable
#if defined InverseOutIndikator
#define dR0LED(x) digitalWrite(red0LED,!x)
#define dG0LED(x) digitalWrite(green0LED,!x)
#define dB0LED(x) digitalWrite(blue0LED,!x)
#define dR1LED(x) digitalWrite(red1LED,!x)
#define dG1LED(x) digitalWrite(green1LED,!x)
#define dB1LED(x) digitalWrite(blue1LED,!x)
#define aR0LED(x) analogWrite(red0LED,255-x)
#define aG0LED(x) analogWrite(green0LED,255-x)
#define aB0LED(x) analogWrite(blue0LED,255-x)
#define aR1LED(x) analogWrite(red1LED,255-x)
#define aG1LED(x) analogWrite(green1LED,255-x)
#define aB1LED(x) analogWrite(blue1LED,255-x)
#else
#define dR0LED(x) digitalWrite(red0LED,x)
#define dG0LED(x) digitalWrite(green0LED,x)
#define dB0LED(x) digitalWrite(blue0LED,x)
#define dR1LED(x) digitalWrite(red1LED,x)
#define dG1LED(x) digitalWrite(green1LED,x)
#define dB1LED(x) digitalWrite(blue1LED,x)
#define aR0LED(x) analogWrite(red0LED,x)
#define aG0LED(x) analogWrite(green0LED,x)
#define aB0LED(x) analogWrite(blue0LED,x)
#define aR1LED(x) analogWrite(red1LED,x)
#define aG1LED(x) analogWrite(green1LED,x)
#define aB1LED(x) analogWrite(blue1LED,x)
#endif
#else
#define dR0LED(x)
#define dG0LED(x)
#define dB0LED(x)
#define dR1LED(x)
#define dG1LED(x)
#define dB1LED(x)
#define aR0LED(x)
#define aG0LED(x)
#define aB0LED(x)
#define aR1LED(x)
#define aG1LED(x)
#define aB1LED(x)
#endif

void status();
void loop();

private:

void Save();
void Program();
void NoWifi();
void NoMQTT();
void NoSync();
void Sync();
void StandByQuick();
void ventStandBy();
void StandByShot();
void StandBy();
#if defined led3ColorIndikator_Enable
void Lon();
void Ron();
#endif
void NoAutoMode();
void Idle();
#if defined DebagEnable
void checkRGB(); boolean check3RGB=0;
#endif

void State();
uint32_t alltimer;
boolean allLedSync;
};

XIIIMLED::XIIIMLED() {pinMode(blueLED, OUTPUT); dBlueLED(1);}
XIIIMLED::XIIIMLED(uint8_t PinBlue) {blueLED=PinBlue; pinMode(blueLED, OUTPUT); dBlueLED(1);}
XIIIMLED::XIIIMLED(uint8_t PinBlue, uint8_t PinRed) {blueLED=PinBlue; pinMode(blueLED, OUTPUT); dBlueLED(1); redLED=PinRed;
#if not defined MonoIndikator
pinMode(redLED, OUTPUT); dRedLED(0);
#endif
}
XIIIMLED::XIIIMLED(uint8_t Pin1Red, uint8_t Pin1Green, uint8_t Pin1Blue, uint8_t Pin2Red=99, uint8_t Pin2Green=99, uint8_t Pin2Blue=99) {
red0LED=Pin1Red; red1LED=Pin2Red; green0LED=Pin1Green; green1LED=Pin2Green; blue0LED=Pin1Blue; blue1LED=Pin2Blue;
pinMode(red0LED, OUTPUT); pinMode(red1LED, OUTPUT); pinMode(green0LED, OUTPUT); pinMode(green1LED, OUTPUT); pinMode(blue0LED, OUTPUT);
pinMode(blue1LED, OUTPUT); dR0LED(0); dG0LED(0); dB0LED(0); dR1LED(0); dG1LED(0); dB1LED(0);} 

void XIIIMLED::status() {
#if defined led3ColorIndikator_Enable
CM("LED Red 1 PIN: "); CMn(red0LED);
CM("LED Green 1 PIN: "); CMn(green0LED);
CM("LED Blue 1 PIN: "); CMn(blue0LED);
if(red1LED!=99) {CM("LED Red 2 PIN: "); CMn(red1LED);} else CMn("LED Red 2 PIN: None");
if(green1LED!=99) {CM("LED Green 2 PIN: "); CMn(green1LED);} else CMn("LED Green 2 PIN: None");
if(blue1LED!=99) {CM("LED Blue 2 PIN: "); CMn(blue1LED);} else CMn("LED Blue 2 PIN: None");
#else
CM("LED Blue PIN: "); CMn(blueLED);
#if not defined MonoIndikator
CM("LED Red PIN: "); CMn(redLED);
#endif
#endif
}

void XIIIMLED::StandBy() {static boolean start; if(!StandBy_I || Save_I || Program_I || NoWifi_I || NoMQTT_I || NoSync_I || Sync_I0 || Sync_I1 || StandByQuick_I || StandByShot_I || ventStandBy_I) {start=0; return;}
static uint8_t m=0; static int16_t i0=255; 
static uint32_t timer1, timeLag1=6;

if(!start || allLedSync) {start=1; m=1; i0=255; aRedLED(50); if(!Lon_I) aR0LED(50); if(!Ron_I) aR1LED(50); timeLag1=2; aBlueLED(i0); if(!Lon_I) aB0LED(i0); if(!Ron_I) aB1LED(i0);}
if(millis()-timer1>=timeLag1) {timer1 = millis();
#if defined MonoIndikator
switch (m) {
case 1: if(i0==255) {timeLag1=2;} aBlueLED(i0); i0--; if(i0==200) {timeLag1=6; m=2;} break;
case 2: i0--; aBlueLED(i0); if(i0==50) {timeLag1=100; m=3;} break;
case 3: timeLag1=6; m=4; break;
case 4: i0++; aBlueLED(i0); if(i0==199) dBlueLED(0); if(i0==200) {timeLag1=4; m=5; dBlueLED(0);} break;
case 5: if(i0==203) dBlueLED(1); if(i0==206) dBlueLED(0); i0++; if(i0>208) aBlueLED(i0); if(i0==255) {m=6;} break;}
return;
#endif
switch (m) {
case 1: if(i0==255) {aRedLED(50); if(!Lon_I) aR0LED(50); if(!Ron_I) aR1LED(50); timeLag1=2;} aBlueLED(i0); if(!Lon_I) aB0LED(i0); if(!Ron_I) aB1LED(i0); i0--; if(i0==200) {timeLag1=6; m=2;} break;
case 2: i0--; aBlueLED(i0); if(!Lon_I) aB0LED(i0); if(!Ron_I) aB1LED(i0); if(i0==50) {timeLag1=100; m=3;} break;
case 3: timeLag1=6; m=4; break;
case 4: i0++; aBlueLED(i0); if(!Lon_I) aB0LED(i0); if(!Ron_I) aB1LED(i0); if(i0==200) {timeLag1=4; m=5; dRedLED(1); if(!Lon_I) dR0LED(1);} break;
case 5: if(i0==201) aRedLED(50); if(!Lon_I) aR0LED(50); if(!Ron_I) aR1LED(50); i0++; aBlueLED(i0); if(!Lon_I) aB0LED(i0); if(!Ron_I) aB1LED(i0); if(i0==231) if(!Ron_I) dR1LED(1); if(i0==255) {m=6;} break;}}}

void XIIIMLED::StandByShot() {static uint8_t m0=1; static boolean go; if(!StandByShot_I) {m0=1; go=0; return;}
static uint32_t timer0, timeLag=4; static uint8_t i0=255;
if(millis()-timer0<timeLag) return; timer0=millis(); //CMn(i0);
#if defined MonoIndikator
switch (m0) {
case 0: i0--; if(i0==0) m0=1; aBlueLED(i0); break;
case 1: i0++; if(i0==255) m0=2; aBlueLED(i0); break;
case 2: timeLag=50; dBlueLED(0); m0=3; break;
case 3: timeLag=20; dBlueLED(1); m0=4; break;
case 4: timeLag=50; m0=5; break;
case 5: timeLag=50; dBlueLED(0); m0=6; break;
case 6: timeLag=4; dBlueLED(1); m0=0; break;}
#else
static uint8_t i1=255, m1, m2=1, m3, i2=255, i3=255; if(m0==3 && m3==9) m0=1;
#if defined led3ColorIndikator_Enable
if(!go) {go=1; if(!Lon_I) {dB0LED(0); dR0LED(0); dG0LED(1);} if(!Ron_I) {dB1LED(0); dR1LED(0); dG1LED(1);}}
switch (m0) {
case 1: i0--; if(i0==0) m0=2; if(i0==200) m1=1; if(i0==150) m2=1; if(!Lon_I) aG0LED(i0); break;
case 2: i0++; if(i0==255) m0=3; if(!Lon_I) aG0LED(i0); break;}

switch (m1) {
case 1: i1++; if(i1==80) m1=2; if(!Lon_I) aR0LED(i1); break;
case 2: i1--; if(i1==0) m1=3; if(!Lon_I) aR0LED(i1); break;
case 3: timeLag=50; m1=4; break;
case 4: timeLag=20; if(!Lon_I) dG0LED(1); if(!Lon_I) dR0LED(1); m1=5; break;
case 5: timeLag=50; if(!Lon_I) dG0LED(0); if(!Lon_I) dR0LED(0); m1=6; break;
case 6: timeLag=20; if(!Lon_I) dG0LED(1); if(!Lon_I) dR0LED(1); m1=7; break;
case 7: timeLag=50; if(!Lon_I) dG0LED(0); if(!Lon_I) dR0LED(0); m1=8; break;
case 8: timeLag=4; if(!Lon_I) dG0LED(1); m1=9; break;}

switch (m2) {
case 1: i2--; if(i2==0) m2=2; if(i2==200) m3=1; if(!Ron_I) aG1LED(i2); break;
case 2: i2++; if(i2==255) m2=3; if(!Ron_I) aG1LED(i2); break;}

switch (m3) {
case 1: i3++; if(i3==80) m3=2; if(!Ron_I) aR1LED(i3); break;
case 2: i3--; if(i3==0) m3=3; if(!Ron_I) aR1LED(i3); break;
case 3: timeLag=50; m3=4; break;
case 4: timeLag=20; if(!Ron_I) dG1LED(1); if(!Ron_I) dR1LED(1); m3=5; break;
case 5: timeLag=50; if(!Ron_I) dG1LED(0); if(!Ron_I) dR1LED(0); m3=6; break;
case 6: timeLag=20; if(!Ron_I) dG1LED(1); if(!Ron_I) dR1LED(1); m3=7; break;
case 7: timeLag=50; if(!Ron_I) dG1LED(0); if(!Ron_I) dR1LED(0); m3=8; break;
case 8: timeLag=4; m3=9; break;}
#else
switch (m0) {
case 1: i0--; if(i0==0) m0=2; if(i0==127) m1=1; aBlueLED(i0); break;
case 2: i0++; if(i0==255) m0=3; aBlueLED(i0); break;}

switch (m1) {
case 1: i1--; if(i1==0) m1=2; aRedLED(i1); break;
case 2: i1++; if(i1==255) m1=3; aRedLED(i1); break;
case 3: timeLag=50; m1=4; break;
case 4: timeLag=20; aBlueLED(127); aRedLED(127); m1=5; break;
case 5: timeLag=50; dBlueLED(0); dRedLED(0); m1=6; break;
case 6: timeLag=20; aBlueLED(127); aRedLED(127); m1=7; break;
case 7: timeLag=50; dBlueLED(0); dRedLED(0); m1=8; break;
case 8: timeLag=4; dRedLED(1); m1=9; m0=1; break;}
#endif
#endif
}

void XIIIMLED::StandByQuick() {if(!StandByQuick_I) return;
static uint32_t timeLag; static uint8_t m;
if(millis()-timeLag < 50) return; timeLag=millis(); 
#if defined led3ColorIndikator_Enable
switch (m) {
case 1: case 3: case 5: case 7: case 9: case 11:  dG0LED(0); dB0LED(0); dR0LED(0); break;
case 0: dG0LED(1); break;
case 2: aG0LED(127); aR0LED(127); break;
case 4: dG0LED(1); break;
case 12: m=0; break;} 
switch (m) {
case 1: case 3: case 5: case 7: case 9: case 11: dG1LED(0); dB1LED(0); dR1LED(0); break;
case 6: dG1LED(1); break;
case 8: aG1LED(127); aR1LED(127); break;
case 10: dG1LED(1); break;
case 12: m=0; break;} 
m++;
#else
#if not defined MonoIndikator
if(m==5 && millis()-timeLag < 400) return;
switch (m) {
case 1: case 3: case 5: dRedLED(0); dBlueLED(0); break;
case 0: aRedLED(127); aBlueLED(127); break;
case 2: aRedLED(70); aBlueLED(140); break;
//case 4: dRedLED(0); dBlueLED(1); break;
} m++;
if(m>5) m=0;
#else
static boolean state;
state=!state; m++; if(m>5) {m=0; state=0;} dBlueLED(!state);
#endif
#endif
}

void XIIIMLED::Sync() {if(!Sync_I0 && !Sync_I1) return; static uint32_t timeLag; static uint8_t mode;
if(millis()-timeLag < 50) return; timeLag=millis(); 
#if not defined MonoIndikator
#if not defined led3ColorIndikator_Enable
switch (mode) {
case 1: case 3: case 5: dRedLED(0); dBlueLED(0); break;
case 0: aRedLED(127); aBlueLED(127); break;
case 2: aRedLED(70); aBlueLED(140); break;
case 4: dRedLED(0); dBlueLED(1); break;} mode++;
if(mode>6) {mode=0; Sync_I0=0; Sync_I1=0; dBlueLED(1); dRedLED(0);}
#else
if(Sync_I0) {switch (mode) { // LED 0 - левый
case 1: case 3: case 5: dR0LED(0); dG0LED(0); dB0LED(0); break;
case 0: aR0LED(255); aG0LED(0); aB0LED(208); break;
case 2: aR0LED(0); aG0LED(255); aB0LED(0); break;
case 4: aR0LED(255); aG0LED(102); aB0LED(51); break;
default: mode=0; Sync_I0=0; dR1LED(0); dG0LED(0); dB0LED(0);}}
if(Sync_I1) { // LED 1 - правый
switch (mode) {
case 1: case 3: case 5: dR1LED(0); dG1LED(0); dB1LED(0); break;
case 0: aR1LED(255); aG1LED(0); aB1LED(208); break;
case 2: aR1LED(0); aG1LED(255); aB1LED(0); break;
case 4: aR1LED(255); aG1LED(102); aB1LED(51); break;
default: mode=0; Sync_I1=0; dR1LED(0); dG1LED(0); dB1LED(0);}}
if(!Sync_I0 && !Sync_I1) {allLedSync=1; alltimer=millis();}
mode++;
#endif
#else
static boolean state;
state=!state; dBlueLED(state); mode++; if(mode>6) {mode=0; state=0; Sync_I0=0; dBlueLED(1);}
#endif
}

void XIIIMLED::NoWifi() {if(!NoWifi_I) return; static uint32_t timer; static uint8_t mode;
if(millis()-timer<50) return;
switch(mode){
case 0: 
#if not defined MonoIndikator
dRedLED(1); dR0LED(1); dG0LED(0); dG1LED(0); dB0LED(0); dB1LED(0);
#else
dBlueLED(1);
#endif
break;
case 2: if(millis()-timer<250) return; dR1LED(1); break;
case 4: if(millis()-timer<600) return; break;
default: dRedLED(0); dBlueLED(0); dR0LED(0); dR1LED(0);
} mode++; if(mode>6) mode=0; timer=millis();}

void XIIIMLED::NoMQTT() {
//CM("Условия: "); CM(" "); CM(NoWifiInd); CM(" "); CM(MQTTOk); CM(" "); CM(masterSyncOk); CM(" "); CM(ProgramInd); CM(" "); CM(ventStandByInd); CM(" "); CMn(SaveInd);
if(!NoMQTT_I) return;
static uint8_t mode; static uint32_t timer; if(millis()-timer<50) return;
switch (mode) {
case 0: case 3:
#if not defined MonoIndikator
dRedLED(1); dR0LED(1); dG0LED(0); dG1LED(0); dB0LED(0); dB1LED(0);
#else
dBlueLED(1);
#endif
break;
//case 1: case 7: if(millis()-timer < 250) return; break;
case 5: if(millis()-timer < 150) return; break;
case 6: case 11: dR1LED(1); break;
case 14: if(millis()-timer < 350) return; break;
default: dRedLED(0); dBlueLED(0); dR0LED(0); dR1LED(0);}
mode++; if(mode>14) mode=0; timer = millis();}

void XIIIMLED::NoSync() {if(!NoSync_I) return;
static uint8_t mode; static uint32_t timer; if(millis()-timer < 50) return;
switch (mode) {
case 0: 
#if not defined MonoIndikator
dG0LED(0); dG1LED(0); dB0LED(0); dB1LED(0);
#else
dBlueLED(1);
#endif
break;
case 1: if(millis()-timer < 400) return; break;
case 2: if(millis()-timer < 250) return; break;
#if not defined led3ColorIndikator_Enable
case 4: if(millis()-timer < 400) return; mode=0; return; break;
#endif
case 5: if(millis()-timer < 400) return; break;
case 6: if(millis()-timer < 250) return; break;
case 8: if(millis()-timer < 200) return; break;}
switch(mode) {
case 0: case 2:
#if not defined MonoIndikator
dRedLED(1); dR0LED(1);
#else
dBlueLED(1);
#endif
break;
case 1: case 3: dRedLED(0); dBlueLED(0); dR0LED(0); dR1LED(0); break;
case 4: case 6: dR1LED(1); break;
case 5: case 7: dR1LED(0); break;}
mode++; 
if(mode>8) mode=0; timer = millis();}


#if defined DebagEnable
void XIIIMLED::checkRGB() {if(!check3RGB) return; static uint32_t timer;
if(millis()-timer<1000) return; timer=millis(); static uint8_t m;
switch(m) {
case 0: dR0LED(1); dG0LED(0); dB0LED(0); dR1LED(1); dG1LED(0); dB1LED(0); m++; CMn("Check Red"); break;
case 1: dR0LED(0); dG0LED(1); dB0LED(0); dR1LED(0); dG1LED(1); dB1LED(0); m++; CMn("Check Green"); break;
case 2: dR0LED(0); dG0LED(0); dB0LED(1); dR1LED(0); dG1LED(0); dB1LED(1); m=0; CMn("Check Blue"); break;}}
#endif

void XIIIMLED::Save() {static boolean start; if(!Save_I) {start=0; return;}
static uint8_t mode, blueOut, redOut;  static uint32_t time; uint16_t timeLag;
if(mode==0) timeLag=3; else timeLag=60;
if(millis()-time < timeLag) return; time=millis(); 
if(!start) {start=1; timeLag = millis(); blueOut=255; redOut=0;}
switch (mode) {
case 0: if(blueOut>0) blueOut--; aBlueLED(blueOut); aB0LED(blueOut); aB1LED(blueOut); if(blueOut==0) mode++;
dR0LED(0); dG0LED(0); dR1LED(0); dG1LED(0);
#if not defined MonoIndikator
if(redOut<255) redOut++; aRedLED(redOut); aR0LED(redOut);
#endif
break;
case 1: dBlueLED(1); dB0LED(0); dR0LED(0); dG0LED(1); dB1LED(0); dR1LED(0); dG1LED(1); break;
case 2: dBlueLED(0); dG0LED(0); dG1LED(0); break;
case 3: 
#if not defined MonoIndikator
aR0LED(192); aB0LED(64); dG0LED(0); aR1LED(192); aB1LED(64); dG1LED(0);
aRedLED(192); aBlueLED(64);
#else
dBlueLED(1);
#endif
break;
case 4: dBlueLED(0); dRedLED(0); dR0LED(0); dB0LED(0); dR1LED(0); dB1LED(0);
break;
case 5: 
#if not defined MonoIndikator
dRedLED(1); dG0LED(1); dR0LED(1); dG1LED(1); dR1LED(1);
#else
dBlueLED(1); 
#endif
break;
case 6: dBlueLED(0); dRedLED(0); dG0LED(0); dR0LED(0); dG1LED(0); dR1LED(0);
break;
case 7: dRedLED(1); dR0LED(1); dR1LED(1); break;
case 8: dBlueLED(0); dRedLED(0); dG0LED(0); dR0LED(0); dG1LED(0); dR1LED(0);
break;
default: Save_I=0; start=0; mode=0; dRedLED(1); dB0LED(0); dG0LED(1); dB1LED(0); dG1LED(1); break;
} if(mode) mode++;}

void XIIIMLED::ventStandBy() {if(!ventStandBy_I) return; // вытяжка на кухне
static int16_t ind0, ind1; static uint32_t timer, timeLag=6; static boolean vector;
#if not defined MonoIndikator
#endif
if(millis()-timer<timeLag) return; timer=millis();
if (!vector && ind0<260) {if(ind0==0) timeLag=6; ind0++; if(ind0==200) timeLag=8; if(ind0==255) {vector=1; timeLag=2;} ind1=123*(ind0/2.55)/100; aBlueLED(ind0); aR0LED(ind0); aR1LED(ind0); aRedLED(ind1); aG0LED(ind1); aG1LED(ind1);}
if (vector && ind0>0) {ind0--; if(ind0<=0) {ind0=0; ind1=0; timeLag=150; vector=0;} if(ind0) ind1=123*(ind0/2.55)/100; aBlueLED(ind0); aR0LED(ind0); aR1LED(ind0); aRedLED(ind1); aG0LED(ind1); aG1LED(ind1);}}

void XIIIMLED::Program() {if(!Program_I) return;
static uint8_t mode, i0; static uint32_t timeLag;
switch (mode) {
case 0: if(millis()-timeLag < 50) return; break;
case 1: if(millis()-timeLag < 300) return; break;
case 2: if(millis()-timeLag < 50) return; break;
case 3: if(millis()-timeLag < 20) return; break;
case 4: if(millis()-timeLag < 50) return; i0=127; break;
case 5: if(millis()-timeLag < 20) return; break;
case 6: if(millis()-timeLag < 50) return; i0=127; break;
case 7: if(millis()-timeLag < 20) return; break;
case 8: if(millis()-timeLag < 600) return; break;}
timeLag = millis();

switch (mode) {
case 0: aBlueLED(127); aG0LED(80); break;
case 2: aRedLED(127); aBlueLED(127); dG0LED(0); aG1LED(127); aB0LED(127); break;
case 4: aBlueLED(127); dG0LED(1); aB0LED(127); dG1LED(1); aB1LED(127); break;
case 6: aBlueLED(127); aG0LED(127); aB1LED(127); break;
default: dRedLED(0); dBlueLED(0); dB0LED(0); dB1LED(0); dR0LED(0); dR1LED(0); dG0LED(0); dG1LED(0); break;}
mode++; if(mode>8) mode=0;}

#if defined led3ColorIndikator_Enable
void XIIIMLED::Lon() {static boolean start; if(!Lon_I|| Save_I || Program_I || NoWifi_I || NoMQTT_I || NoSync_I || Sync_I0 || Sync_I1 || StandByQuick_I || ventStandBy_I) {start=0; return;}
static uint8_t m1=0, i0=255; static uint32_t timer1, timeLag1=12;

if(!start || allLedSync) {start=1; m1=1; timer1 = millis(); i0=255; dR0LED(0); dB0LED(0);} if(allLedSync) dG0LED(1);

if(millis()-timer1<timeLag1) return; timer1 = millis();
switch (m1) {
case 1: if(i0==255) timeLag1=12; aG0LED(i0); i0--; if(i0<230) {timeLag1=2; m1=2;} break;
case 2: aG0LED(i0); i0--; if(i0<125) {timeLag1=100; m1=3;} break;
case 3: if(i0==124) timeLag1=2; aG0LED(i0); i0++; if(i0>230) {timeLag1=12; m1=4;} break;
case 4: aG0LED(i0); i0++; if(i0>254) {m1=0;} break;}}

void XIIIMLED::Ron() {static boolean start; if(!Ron_I|| Save_I || Program_I || NoWifi_I || NoMQTT_I || NoSync_I || Sync_I0 || Sync_I1 || StandByQuick_I || ventStandBy_I) {start=0; return;}
static uint8_t m1=0, m2, i0=255, i1=255; static uint32_t timer1, timer2, timeLag1=12, timeLag2=12;

if(!start || allLedSync) {start=1; m1=1; m2=0; timer1 = millis(); i0=255, i1=255; dR1LED(0); dB1LED(0);} if(allLedSync) dG1LED(1);

if(millis()-timer1>=timeLag1) {timer1 = millis();
switch (m1) {
case 1: if(i0==255) timeLag1=12; i0--; if(i0<230) {timeLag1=2; m1=2;} break;
case 2: i0--; if(i0==180) m2=1; if(i0<125) {timeLag1=100; m1=3;} break;
case 3: if(i0==124) timeLag1=2; i0++; if(i0>230) {timeLag1=12; m1=4;} break;
case 4: i0++; if(i0>254) {m1=0;} break;}}

if(millis()-timer2<timeLag2) return; timer2 = millis();
switch (m2) {
case 1: if(i1==255) timeLag2=12; aG1LED(i1); i1--; if(i1<230) {timeLag2=2; m2=2;} break;
case 2: aG1LED(i1); i1--; if(i1<125) {timeLag2=100; m2=3;} break;
case 3: if(i1==124) timeLag2=2; aG1LED(i1); i1++; if(i1>230) {timeLag2=12; m2=4;} break;
case 4: aG1LED(i1); i1++; if(i1>254) {m2=0;} break;}}
#endif

void XIIIMLED::NoAutoMode() {static boolean start; if(!NoAutoMode_I || Save_I || Program_I || NoWifi_I || NoMQTT_I || NoSync_I || Sync_I0 || Sync_I1 || StandByQuick_I || StandByShot_I || ventStandBy_I || StandBy_I) {start=0; return;}
static uint8_t m0;
#if defined led3ColorIndikator_Enable
dB0LED(0); dB1LED(0); // 241
static uint8_t m1=1, i0=255, i1=255, i2, i3; static uint32_t timer1, timer2, timeLag1=12, timeLag2=12;
if(!start || allLedSync) {start=1; m1=0; m0=1; i0=255; if(!Lon_I) aG0LED(i0); i2=i0*0.95; if(!Lon_I) aR0LED(i2); i1=255; if(!Ron_I) aG1LED(i1); i3=i1*0.95; if(!Ron_I) aR1LED(i3);}

if(millis()-timer1>=timeLag1) {timer1 = millis();
switch (m0) {
case 1: if(i0==255) timeLag1=12; if(!Lon_I) aG0LED(i0); i2=i0*0.95; if(!Lon_I) aR0LED(i2); i0--; if(i0<230) {timeLag1=2; m0=2;} break;
case 2: if(!Lon_I) aG0LED(i0); i2=i0*0.95; if(!Lon_I) aR0LED(i2); i0--; if(i0==180) m1=1; if(i0<125) {timeLag1=100; m0=3;} break;
case 3: if(i0==124) timeLag1=2; if(!Lon_I) aG0LED(i0); i2=i0*0.95; if(!Lon_I) aR0LED(i2); i0++; if(i0>230) {timeLag1=12; m0=4;} break;
case 4: if(!Lon_I) aG0LED(i0); i2=i0*0.95; if(!Lon_I) aR0LED(i2); i0++; if(i0>254) {m0=0;} break;}}

if(Ron_I || millis()-timer2<timeLag2) return; timer2 = millis();
switch (m1) {
case 1: if(i1==255) timeLag2=12; aG1LED(i1); i3=i1*0.95; aR1LED(i3); i1--; if(i1<230) {timeLag2=2; m1=2;} break;
case 2: aG1LED(i1); i3=i1*0.95; aR1LED(i3); i1--; if(i1<125) {timeLag2=100; m1=3;} break;
case 3: if(i1==124) timeLag2=2; aG1LED(i1); i3=i1*0.95; aR1LED(i3); i1++; if(i1>230) {timeLag2=12; m1=4;} break;
case 4: aG1LED(i1); i3=i1*0.95; aR1LED(i3); i1++; if(i1>254) {m1=0;} break;}

#else
static uint32_t timeLag;
switch(m0) {
case 0: case 2: case 4: if(millis()-timeLag < 50) return; 
#if not defined MonoIndikator
aR0LED(231); aG0LED(235);
aRedLED(10); aBlueLED(30);
#else
dBlueLED(1);
#endif
break;
case 1: case 3: case 5: if(m0==1 && millis()-timeLag < 3000) return;
if(millis()-timeLag < 10) return;
#if not defined MonoIndikator
aR0LED(241); aG0LED(255);
dRedLED(0);
#endif
switch(m0) {
case 1: aBlueLED(200); break;
case 3: aBlueLED(180); break;
case 5: aBlueLED(160); break;
}
break;
case 6: m0=0; return; break;
} timeLag = millis(); m0++;
#endif
}

void XIIIMLED::Idle() {static boolean start; if(NoAutoMode_I || Save_I || Program_I || NoWifi_I || NoMQTT_I || NoSync_I || Sync_I0 || Sync_I1 || StandByQuick_I || StandByShot_I || ventStandBy_I || StandBy_I) {start=0; return;}
static uint8_t m1=0, m2=1, i0=255, i1=255; static uint32_t timer1, timer2, timeLag1=12, timeLag2=12;

if(!start || allLedSync) {start=1; m1=1; m2=0; i0=255; aBlueLED(i0); dRedLED(0); if(!Lon_I) {aB0LED(i0); dR0LED(0); dG0LED(0);} i1=255; if(!Ron_I) {aB1LED(i1); dR1LED(0); dG1LED(0);}}

if(millis()-timer1>=timeLag1) {timer1 = millis();
switch (m1) {
case 1: if(i0==255) timeLag1=12; aBlueLED(i0); if(!Lon_I) aB0LED(i0); i0--; if(i0<230) {timeLag1=2; m1=2;} break;
case 2: if(!Lon_I) aB0LED(i0); aBlueLED(i0); i0--; if(i0==180) m2=1; if(i0<125) {timeLag1=100; m1=3;} break;
case 3: if(i0==124) timeLag1=2; if(!Lon_I) aB0LED(i0); aBlueLED(i0); i0++; if(i0>230) {timeLag1=12; m1=4;} break;
case 4: if(!Lon_I) aB0LED(i0); aBlueLED(i0); i0++; if(i0>254) {m1=0;} break;}}

if(Ron_I || millis()-timer2<timeLag2) return; timer2 = millis();
switch (m2) {
case 1: if(i1==255) timeLag2=12; aB1LED(i1); i1--; if(i1<230) {timeLag2=2; m2=2;} break;
case 2: aB1LED(i1); i1--; if(i1<125) {timeLag2=100; m2=3;} break;
case 3: if(i1==124) timeLag2=2; aB1LED(i1); i1++; if(i1>230) {timeLag2=12; m2=4;} break;
case 4: aB1LED(i1); i1++; if(i1>254) {m2=0;} break;}}

void XIIIMLED::loop() {
#if defined DebagEnable
//checkRGB();
#endif
StandBy(); 												          		// Ожидание
#if defined led3ColorIndikator_Enable
Lon();																					// Свет включен - левый LED
Ron();																					// Свет включен - правый LED
#endif
NoAutoMode();																		// Режим ожидания - Авто режим отключен
Idle();																					// Режим ожидания - Авто режим вкключен
allLedSync=0; if(millis()-alltimer>=3000) {allLedSync=1; alltimer=millis();}
if(Save_I) {Save(); return;}                		// Сохранили данные
if(Program_I) {Program(); return;}          		// Программирование
if(NoWifi_I) {NoWifi(); return;}            		// Нет сети WiFi
if(NoMQTT_I) {NoMQTT(); return;}            		// Нет соединения с MQTT или синхронизации
if(NoSync_I) {NoSync(); return;}
if(Sync_I0 || Sync_I1) {Sync(); return;}        // Синхронизация
if(StandByQuick_I) {StandByQuick(); return;}		// Отсчет дежурной подсветки на 15 сек.
if(ventStandBy_I) {ventStandBy(); return;}  		// Обратный отсчет - вытяжка
if(StandByShot_I) {StandByShot(); return;}  		// Отсчет подсветки при движении
}
#endif // XIIIMLed_h