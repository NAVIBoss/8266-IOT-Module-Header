#ifndef XIIIMSensors_h
#define XIIIMSensors_h

// ----------------------------vvvvvvv---------------- Подключение библиотек -----------------vvvvvvv--------------------------------
#if defined AM2301A_Enabled
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT_Unified dht(DHTPIN, DHTTYPE);
sensor_t sensor;
sensors_event_t event;
#endif

#if defined HX711_Enable
#include <HX711.h>
int16_t weight;
HX711 scale;
#endif

#if defined VL6180X_Enable || defined BH1750_Enable || defined BME280_Enable || defined MAX44009_Enabled || defined AM2320_Enabled
#include <Wire.h>        // I2C library
#endif

#if defined VL6180X_Enable
#include <VL6180X.h>
VL6180X sensor;
#endif

#if defined BME280_Enable
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
#endif

#if defined AM2320_Enabled
#include <AM2320.h>
AM2320 th(&Wire);
#endif

#if defined MAX44009_Enabled
#include <Max44009.h>
uint32_t LuxSensor = 0;
Max44009 myLux(0x4A);
#endif

#if defined BH1750_Enable
#include <BH1750FVI.h>
BH1750FVI myBH1750(BH1750_DEFAULT_I2CADDR, BH1750_CONTINUOUS_HIGH_RES_MODE_2, BH1750_SENSITIVITY_DEFAULT, BH1750_ACCURACY_DEFAULT);
uint32_t LuxSensor=0;
#endif

#if defined S8_CO2_Enable
#include <SoftwareSerial.h>
SoftwareSerial s8Serial(Uart_Rx, Uart_Tx);
int16_t s8_co2;
int16_t s8_co2_mean;
int16_t s8_co2_mean2;
double smoothing_factor = 0.5;
double smoothing_factor2 = 0.15;
const int16_t r_len = 7;
const int16_t c_len = 8;
int8_t CO2MeasureProcess = 0;                 // не отправлять в MQTT по прерыванию пока идет измерение CO2 по COM порту
uint8_t cmd_s8[]       = {0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5};
//uint8_t abc_s8[]       = {0xFE, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xA1, 0xC3};
uint8_t response_s8[7] = {0, 0, 0, 0, 0, 0, 0};
uint32_t s8Replay(uint8_t rc_data[]) {int16_t high = rc_data[3]; int16_t low = rc_data[4]; uint32_t val = high*256 + low; return val;}
#endif

#if defined PZEM004T_Enable
#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
SoftwareSerial pzemSWSerial(Uart_Rx, Uart_Tx);
PZEM004Tv30 pzem(pzemSWSerial);
#endif

// ----------------------------^^^^^^^---------------- Подключение библиотек -----------------^^^^^^^--------------------------------

boolean errorInitSens=1; // пытаемся инициализировать раз в сек, если ошибка (Wire раз в 5 сек)

// ----------------------------vvvvvvv---------------- Инициализация датчиков ----------------vvvvvvv--------------------------------

void sensInit() {if(!errorInitSens) return;
#if defined VL6180X_Enable || defined BH1750_Enable || defined BME280_Enable || defined MAX44009_Enabled || defined AM2320_Enabled
static boolean WireInit; static uint32_t time; if(millis() - time < 5000 && !WireInit) return;
if(millis()-time < 500) return;
if(!WireInit) {
Wire.begin(SDA,SCL); // SDA SCL I2C
Wire.setClock(100000); time=millis(); WireInit=1; CMn("Инициализация шины I2C произведена"); return;}
WireInit=0; time=millis();
#endif

#if defined VL6180X_Enable
sensor.init();
sensor.configureDefault();
sensor.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
sensor.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
sensor.setTimeout(500);
sensor.stopContinuous();
sensor.startInterleavedContinuous(100);
CMn("Инициализация сенсора VL6180X произведена"); errorInitSens=0;
#endif

#if defined BH1750_Enable
if (myBH1750.begin(SDA,SCL)) {CMn("Инициализация сенсора BH1750 произведена"); MQTTStatus("Sensor initialization","BH1750 Ok");  errorInitSens=0;} else {CMn("Ошибка инициализации сенсора BH1750"); MQTTStatus("Sensor initialization","BH1750 error");}
#endif

#if defined BME280_Enable
Wire.setClock(100000);
if(!bme.begin(0x76)) {CMn("Ошибка инициализации сенсора BME280"); MQTTStatus("Sensor initialization","BME280 error");} else {CMn("Сенсор BME280 инициализирован"); MQTTStatus("Sensor initialization","BME280 Ok"); errorInitSens=0;}
#endif

#if defined AM2320_Enabled
if(th.Read()) {CMn("Ошибка инициализации сенсора AM2320"); MQTTStatus("Sensor initialization","AM2320 error");} else {CMn("Сенсор AM2320 инициализирован"); MQTTStatus("Sensor initialization","AM2320 Ok"); errorInitSens=0;}
#endif

#if defined MAX44009_Enabled
myLux.setContinuousMode();
if(myLux.getError()) {CMn("Ошибка инициализации сенсора MAX44009"); MQTTStatus("Sensor initialization","MAX44009 error");} else {CMn("Инициализация сенсора MAX44009 произведена"); errorInitSens=0;}
#endif

returnSec(5);

#if defined S8_CO2_Enable
s8Serial.begin(9600);
CMn("Инициализация сенсора S8 CO2 произведена"); errorInitSens=0;
#endif

#if defined HX711_Enable
scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
scale.set_scale(2280.f);
scale.tare();
#endif

#if defined AM2301A_Enabled
dht.begin(); dht.temperature().getEvent(&event);
if (isnan(event.temperature)) {CMn("Инициализация сенсора AM2301A произведена"); errorInitSens=0;} else {CMn("Ошибка инициализации сенсора AM2301A"); MQTTStatus("Sensor initialization","AM2301A error");}
#endif

#if defined PZEM004T_Enable
CMn("Инициализация сенсора PZEM004T произведена"); errorInitSens=0; MQTTStatus("Sensor initialization","PZEM004T Ok");
#endif

}
// ----------------------------^^^^^^^---------------- Инициализация датчиков ----------------^^^^^^^--------------------------------

// ----------------------------vvvvvvv----------------- Считывание показаний -----------------vvvvvvv--------------------------------

#if defined AM2301A_Enabled
void DHTread() {if(errorInitSens) return; return1sec; int16_t tempC, humidity, pressure; char value[10], tempVal[10];
static double tempCsave, humiditysave; static uint8_t newCountT, newCountH;
dht.temperature().getEvent(&event); if (isnan(event.temperature)) CMn("Ошибка чтения температуры!"); else tempC = round(event.temperature*10);
dht.humidity().getEvent(&event); if (isnan(event.relative_humidity)) CMn("Ошибка чтения влажности!"); else humidity = round(event.relative_humidity);

if(tempC>-100 && tempC<100 && save.DecimalTemp) {
if (abs(tempCsave-tempC) > 10) {tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);}
if (tempCsave == tempC) newCountT = 0;
if (tempCsave != tempC && newCountT > 10) {newCountT = 0; tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == tempC) newCountT=0;
} else {
if (abs(tempCsave-(int)tempC/10) > 2) {tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);}
if (tempCsave == (int)tempC/10) newCountT = 0;
if (tempCsave != (int)tempC/10 && newCountT > 10) {newCountT = 0; tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == (int)tempC/10) newCountT=0;}

if (abs(humiditysave-humidity) > 2) {humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%"); MQTTStatus("Humidity",humidity);}
if (humiditysave == humidity) newCountH = 0;
if (humiditysave != humidity && newCountH > 10) {newCountH = 0; humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%");
MQTTStatus("Humidity",humidity);} else newCountH++; if (humiditysave == humidity) newCountH=0;}
#endif

#if defined HX711_Enable
void ReadWeight() {if(errorInitSens) return; return1sec; static int16_t weightSave; static uint32_t SyncTime; static uint8_t newCount;
weight = scale.get_units(10);
//weight = abs(round(weight/10));
weight = round(weight/10);
if (abs(weightSave-weight) > 10) {weightSave = weight; CM("Weight: "); CMn(weight); MQTTStatus("Weight",weight);}
if (weightSave != weight && newCount > 2) {newCount = 0; weightSave = weight; CM("Weight: "); CMn(weight); MQTTStatus("Weight",weight);} else newCount++;
if (weightSave == weight) newCount=0;}
#endif

#if defined BH1750_Enable // Считывание показаний датчика освещенности и отправка в MQTT
void EventLux() {if(errorInitSens) return; return1sec; static uint32_t LuxSave; static uint8_t newCount; char num[6], value[10];
LuxSensor = round(myBH1750.readLightLevel()*10);
CM("BH1750 Освещенность:\t"); CM(LuxSensor/10); CM("."); CM(LuxSensor%10); CMn(" lux.");
if (abs(LuxSave-LuxSensor) > 10) {LuxSave = LuxSensor; itoa(LuxSensor/10,num,10); strcpy(value,num); itoa(LuxSensor%10,num,10); strcat(value,"."); strcat(value,num); MQTTStatus("LuxSensor",value); newCount = 0;}
if (LuxSave == LuxSensor) newCount = 0;
if (LuxSave != LuxSensor && newCount > 5) {newCount = 0; LuxSave = LuxSensor; LuxSave = LuxSensor; itoa(LuxSensor/10,num,10); strcpy(value,num); itoa(LuxSensor%10,num,10); strcat(value,"."); strcat(value,num); MQTTStatus("LuxSensor",value); return;} newCount++;
if (LuxSave == LuxSensor) newCount=0;}
#endif

#if defined MAX44009_Enabled // Считывание показаний датчика освещенности и отправка в MQTT
void EventLux() {if(errorInitSens) return; static uint32_t time; static uint32_t LuxSave; static uint8_t count, newCount; char num[6], value[10]; static boolean initSens;
if(millis()-time < 100) return; time=millis(); count++;
if (count == 5) myLux.clrContinuousMode();
if (count == 10) {count = 0; myLux.setContinuousMode();}
LuxSensor = round(myLux.getLux()*10);
if (myLux.getError()) {if (count == 4) {CMn("MAX44009 Error"); if(initSens) {MQTTStatus("Sensor initialization","MAX44009 error"); initSens=0;}} return;}
if(!initSens) {MQTTStatus("Sensor initialization","MAX44009 Ok"); initSens=1;}
if (count == 4) {CM("MAX44009 Освещенность:\t"); CM(LuxSensor/10); CM("."); CM(LuxSensor%10); CMn(" lux.");}
int32_t mi=LuxSave-LuxSensor; mi=abs(mi);
if (mi > 10) {LuxSave = LuxSensor; itoa(LuxSensor/10,num,10); strcpy(value,num); itoa(LuxSensor%10,num,10); strcat(value,"."); strcat(value,num); MQTTStatus("LuxSensor",value); newCount=0;}
if (LuxSave == LuxSensor) newCount = 0;
if (LuxSave != LuxSensor && newCount > 50) {newCount = 0; LuxSave = LuxSensor; LuxSave = LuxSensor; itoa(LuxSensor/10,num,10); strcpy(value,num); itoa(LuxSensor%10,num,10); strcat(value,"."); strcat(value,num); MQTTStatus("LuxSensor",value); return;} newCount++;
if (LuxSave == LuxSensor) newCount=0;}
#endif

#if defined BME280_Enable
void ReadTemp() {if(errorInitSens) return; returnSec(1); char value[10],tempVal[10];
#if defined S8_CO2_Enable
if (CO2MeasureProcess) return;
#endif
static double tempCsave, humiditysave, pressuresave; static uint8_t newCountT, newCountH, newCountP;
tempC = round(bme.readTemperature()*10);
humidity = round(bme.readHumidity());
pressure = round(bme.readPressure() / 133.322);

if(tempC>-100 && tempC<100 && save.DecimalTemp) {
if (abs(tempCsave-tempC) > 10) {tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);}
if (tempCsave == tempC) newCountT = 0;
if (tempCsave != tempC && newCountT > 10) {newCountT = 0; tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == tempC) newCountT=0;
} else {
if (abs(tempCsave-(int)tempC/10) > 2) {tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);}
if (tempCsave == (int)tempC/10) newCountT = 0;
if (tempCsave != (int)tempC/10 && newCountT > 10) {newCountT = 0; tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == (int)tempC/10) newCountT=0;}

if (abs(humiditysave-humidity) > 2) {humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%"); MQTTStatus("Humidity",humidity);}
if (humiditysave == humidity) newCountH = 0;
if (humiditysave != humidity && newCountH > 10) {newCountH = 0; humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%");
MQTTStatus("Humidity",humidity);} else newCountH++; if (humiditysave == humidity) newCountH=0;

if (abs(pressuresave-pressure) > 2) {pressuresave = pressure; CM("Pressure = "); CM(pressure); CMn("hPa"); MQTTStatus("Pressure",pressure);}
if (pressuresave == pressure) newCountP = 0;
if (pressuresave != pressure && newCountP > 10) {newCountP = 0; pressuresave = pressure; CM("Pressure = "); CM(pressure); CMn("hPa");
MQTTStatus("Pressure",pressure);} else newCountP++; if (pressuresave == pressure) newCountP=0;}
#endif

#if defined AM2320_Enabled
void ReadTemp() {if(errorInitSens) return; return1sec; int16_t tempC, humidity; char value[10],tempVal[10];
#if defined S8_CO2_Enable
if (CO2MeasureProcess) return;
#endif
static double tempCsave, humiditysave; static uint8_t newCountT, newCountH; static boolean err;
if(th.Read() && !err) {CMn("Ошибка чтения сенсора AM2320"); MQTTStatus("Sensor initialization","AM2320 error");}
if(err) {CMn("Сенсор AM2320 восстановлен"); MQTTStatus("Sensor initialization","AM2320 Ok");}
tempC = round(th.cTemp*10);
humidity = round(th.Humidity);

if(tempC>-100 && tempC<100 && save.DecimalTemp) {
if (abs(tempCsave-tempC) > 10) {tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);}
if (tempCsave == tempC) newCountT = 0;
if (tempCsave != tempC && newCountT > 10) {newCountT = 0; tempCsave = tempC; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,tempVal,10); strcpy(value,tempVal); strcat(value,"."); itoa(tempC%10,tempVal,10); strcat(value,tempVal); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == tempC) newCountT=0;
} else {
if (abs(tempCsave-(int)tempC/10) > 2) {tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C"); itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);}
if (tempCsave == (int)tempC/10) newCountT = 0;
if (tempCsave != (int)tempC/10 && newCountT > 10) {newCountT = 0; tempCsave = (int)tempC/10; CM("Temperature = "); CM((int)tempC/10); CM(","); CM(tempC % 10); CMn("°C");
itoa((int)tempC/10,value,10); MQTTStatus("Temperature",value);} else newCountT++; if (tempCsave == (int)tempC/10) newCountT=0;}

if (abs(humiditysave-humidity) > 2) {humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%"); MQTTStatus("Humidity",humidity);}
if (humiditysave == humidity) newCountH = 0;
if (humiditysave != humidity && newCountH > 10) {newCountH = 0; humiditysave = humidity; CM("Humidity = "); CM(humidity); CMn("%");
MQTTStatus("Humidity",humidity);} else newCountH++; if (humiditysave == humidity) newCountH=0;}
#endif

#if defined VL6180X_Enable
void ReadToF() {if(errorInitSens) return;
static boolean switchOn;
if (sensor.readRangeContinuousMillimeters()<180) {
if (!switchOn) {switchOn=1; CMn("ToF Event: 1"); MQTTStatus("TOF",1);}}
else if (switchOn) {switchOn=0; CMn("ToF Event: 0"); MQTTStatus("TOF",0);}}
#endif

#if defined S8_CO2_Enable
void ReadCO2() {static uint32_t SyncTime; static int16_t s8_co2_save; static boolean initSens;
if (CO2MeasureProcess==0 && millis() - SyncTime < 10*1000L) return; SyncTime = millis(); CO2MeasureProcess=1;
int16_t timecount=0; uint32_t timeErr;
CMn("Отправляем запрос S8 CO2"); timeErr=millis();
while(!s8Serial.available() && millis() - timeErr < 1500) {s8Serial.write(cmd_s8, c_len); delay(50);}
timeErr=millis();
while(s8Serial.available() < r_len && millis() - timeErr < 1500) {timecount++; 
if(timecount > 10) {while(s8Serial.available()) {s8Serial.read(); break;}} delay(50);} 

for_i (0,r_len) {response_s8[i] = s8Serial.read();}
if(millis() - timeErr > 1499) {if(!initSens) {CMn("S8 CO2 Error"); MQTTStatus("Sensor initialization","S8 CO2 error"); CO2MeasureProcess=0; initSens=0;} return;}
if(!initSens) {initSens=1; MQTTStatus("Sensor initialization","S8 CO2 Ok");}
s8_co2 = s8Replay(response_s8);
if (!s8_co2_mean) s8_co2_mean = s8_co2; s8_co2_mean = s8_co2_mean - smoothing_factor*(s8_co2_mean - s8_co2);
if (!s8_co2_mean2) s8_co2_mean2 = s8_co2; s8_co2_mean2 = s8_co2_mean2 - smoothing_factor2*(s8_co2_mean2 - s8_co2);
#if defined DebagEnable
Serial.printf("Уровень CO2: %d, С поправкой: %d, Усредненное значение: %d\n", s8_co2, s8_co2_mean, s8_co2_mean2); 
#endif
if(s8_co2_mean2 > 0 && s8_co2_save != s8_co2_mean2) {MQTTStatus("CO2",s8_co2_mean2); s8_co2_save = s8_co2_mean2;} CO2MeasureProcess=0;}
#endif

#if defined PZEM004T_Enable
void ReadPZEM() {return1sec;
static float voltageSave, voltage, currentSave, current, powerSave, power, energySave, energy,
frequencySave, frequency, pfSave, pf; char val[10]; static boolean err;
static uint8_t newCountV, newCountC, newCountP, newCountE, newCountF, newCountPf;
voltage = pzem.voltage();
current = pzem.current();
power = pzem.power();
energy = pzem.energy();
frequency = pzem.frequency();
pf = pzem.pf();
if(isnan(voltage) || voltage >= 380.00) {CMn("Error reading voltage"); voltageSave=voltage; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Voltage");}}
else if (isnan(current)) {CMn("Error reading current"); currentSave = current; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Current");}}
else if (isnan(power)) {CMn("Error reading power"); powerSave = power; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Power");}}
else if (isnan(energy)) {CMn("Error reading energy"); energySave = energy; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Energy");}}
else if (isnan(frequency)) {CMn("Error reading frequency"); frequencySave = frequency; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Frequency");}}
else if (isnan(pf)) {CMn("Error reading power factor"); pfSave = pf; if(!err) {err=1; MQTTStatus("Sensor initialization","Error read Power factor");}}
else {if(err) {err=0; MQTTStatus("Sensor initialization","PZEM004T Ok");}
CM("Voltage: "); CM(voltage); CMn(" V");
CM("Current: "); CM(current); CMn(" A");
CM("Power: "); CM(power); CMn(" W");
CM("Energy: "); CM2(energy,3); CMn(" kWh");
CM("Frequency: "); CM2(frequency, 1); CMn(" Hz");
CM("Power Factor: "); CMn(pf);} CMn("");
if (voltageSave-voltage > 1.00 || voltageSave-voltage < -1.00) {voltageSave = voltage; CM("Voltage = "); CM(voltage); dtostrf(voltage, 3, 2, val); MQTTStatus("Voltage",val);}
if (voltageSave == voltage) newCountV = 0;
if (voltageSave != voltage && newCountV > 10) {newCountV = 0; voltageSave = voltage; CM("Voltage = "); CM(voltage);
dtostrf(voltage, 3, 2, val); MQTTStatus("Voltage",val);} else newCountV++;
if (currentSave-current > 0.10 || currentSave-current < -0.10) {currentSave = current; CM("Current = "); CM(current); dtostrf(current, 2, 2, val); MQTTStatus("Current",val);}
if (currentSave == current) newCountC = 0;
if (currentSave != current && newCountC > 10) {newCountC = 0; currentSave = current; CM("Current = "); CM(current);
dtostrf(current, 2, 2, val); MQTTStatus("Current",val);} else newCountC++;
if (powerSave-power > 1.00 || powerSave-power < -1.00) {powerSave = power; CM("Power = "); CM(power); 
if(power<1000) dtostrf(power, 3, 2, val); else dtostrf(power, 3, 1, val); MQTTStatus("Power",val);}
if (powerSave == power) newCountP = 0;
if (powerSave != power && newCountP > 10) {newCountP = 0; powerSave = power; CM("Power = "); CM(power);
if(power<1000) dtostrf(power, 3, 2, val); else dtostrf(power, 3, 1, val); MQTTStatus("Power",val);} else newCountP++;
if (energySave-energy > 0.01 || energySave-energy < -0.01) {energySave = energy; CM("Energy = "); CM(energy); 
if(energy<100) dtostrf(energy, 2, 2, val); else if(energy<1000) dtostrf(energy, 2, 1, val); else dtostrf(energy, 2, 0, val); MQTTStatus("Energy",val);}
if (energySave == energy) newCountE = 0;
if (energySave != energy && newCountE > 10) {newCountE = 0; energySave = energy; CM("Energy = "); CM(energy);
if(energy<100) dtostrf(energy, 2, 2, val); else if(energy<1000) dtostrf(energy, 2, 1, val); else dtostrf(energy, 2, 0, val); MQTTStatus("Energy",val);} else newCountE++;
if (frequencySave-frequency > 0.2 || frequencySave-frequency < -0.2) {frequencySave = frequency; CM("Frequency = "); CM(frequency); dtostrf(frequency, 2, 1, val); MQTTStatus("Frequency",val);}
if (frequencySave == frequency) newCountP = 0;
if (frequencySave != frequency && newCountP > 10) {newCountP = 0; frequencySave = frequency; CM("Frequency = "); CM(frequency);
dtostrf(frequency, 2, 1, val); MQTTStatus("Frequency",val);} else newCountP++;
if (pfSave-pf > 0.10 || pfSave-pf < -0.10) {pfSave = pf; CM("Power Factor = "); CM(pf); dtostrf(pf, 1, 2, val); MQTTStatus("Power Factor",val);}
if (pfSave == pf) newCountE = 0;
if (pfSave != pf && newCountE > 10) {newCountE = 0; pfSave = pf; CM("Power Factor = "); CM(pf);
dtostrf(pf, 1, 2, val); MQTTStatus("Power Factor",val);} else newCountE++;

}
#endif

// ----------------------------^^^^^^^----------------- Считывание показаний -----------------^^^^^^^--------------------------------

void sensLoop() {
sensInit();
#if defined AM2301A_Enabled
DHTread();
#endif
#if defined BH1750_Enable || defined MAX44009_Enabled
EventLux();
#endif
#if defined HX711_Enable
ReadWeight();
#endif
#if defined BME280_Enable || defined AM2320_Enabled
ReadTemp();
#endif
#if defined VL6180X_Enable
ReadToF();
#endif
#if defined S8_CO2_Enable
ReadCO2();
#endif
#if defined PZEM004T_Enable
ReadPZEM();
#endif
}

#endif // XIIIMSensors_h