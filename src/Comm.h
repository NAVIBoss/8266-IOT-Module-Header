#ifndef XIIIMCommunicate_h
#define XIIIMCommunicate_h

#pragma once
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
WiFiClient wclient;
#define _WIFI_SSID "Keenetic-1486"              // точка доступа WiFi по умолчанию
#define _WIFI_PASSWORD "cdtnbr1973"             // пароль WiFi по умолчанию

#if defined MQTT_SendEnable
#include <PubSubClient.h>
PubSubClient mqttClient(wclient);
#define mqtt_server "192.168.1.35"              // IP сервера MQTT
#define mqtt_user "MQTT"
#define mqtt_pass "cdtnbr"
#define mqtt_port 1883                          // порт MQTT брокера
#endif

class XIIIMCommunicate { // ----------------------------------------------- CLASS -------------------------------------------------------------------------------------
public:
char IPadress[40];
boolean MASTER_ESP = 0;
boolean masterSyncOk=0;                         // модуль синхронизирован по всем контролируемым топикам
#if defined GlobalHouseSwitch || defined MasterBedRoom
boolean LEDSyncOk=0;                            // состояние всех LED топиков синхронизировано
#endif

void loop();

#if defined MQTT_SendEnable
uint8_t SyncTopic[30];                          // топик не синхронизирован - 0, синхронизирован - 1, пустой - 2

#if defined GlobalHouseSwitch || defined MasterBedRoom
uint8_t SyncLEDTopic[30];                       // топик не синхронизирован - 0, синхронизирован - 1, пустой - 2
#endif

XIIIMCommunicate();

void status(const char* param, const char* value);                                                            // "Comm","Val"
void status(const char* param, const char* value, const char* valadd);                                        // "Comm","Val (Add)"
void status(const char* param, const char* paramNum, const char* value, const char* plus);                    // "Comm(x)","Val"
void status(const char* param, int32_t value);                                                                // "Comm","Val"
void status(const char* param, int32_t value, const char* valueAdd);                                          // "Comm","Val (Add)"
void status(const char* param, uint8_t paramNum, char* value, const char* Plus);                              // "Topic(x)","Val" - (Plus)
void status(const char* param, const char* value, int32_t valueAdd);                                          // "Comm","Val : (Add)"
void status(const char* param, const char* paramNum, int32_t value, const char* plus);                        // "Comm(x)","Val"
void status(const char* param, uint8_t paramNum, int8_t value, const char* relay);                            // "Comm(x)","Val"
void status(const char* param, const char* paramNum, int32_t value, const char* valueAdd, const char* plus);  // "Comm(x)","Val (Add)"
void status(const char* param, double &value);                                                                // "Comm","x.xx : xxxms"
void status(const char* param, double &value, int32_t current);                                               // "Comm","Current xxxms Save x.xx : xxxms"

void command(const char* topic, const char* command, const char* value);                                      // "Topic","Command","Value"
void command(const char* topic, const char* command, int value);                                              // "Topic","Command","Value"
void command(const char* topicNum, int32_t value);                                                            // "Command","Value" to Topic0
void command(const char* topic, char command, int value, const char* outControlTopic);                        // "Command","Value" to TopicName

#if defined RelayEnable
void statusRelay();
#endif
#endif

private:
boolean wrongWiFi;
uint32_t wrongWiFiTime;
void getWiFi();
#if defined MQTT_SendEnable
// -------------------------------------------------------------------------- Private function -----------------------------------------------------------------------
void sendMQTT(const char* param, const char* value) {char topicSend[50]; strcpy(topicSend,ESPName); strcat(topicSend,"/Status/"); strcat(topicSend,param); mqttClient.publish(topicSend,value); CM("-в-> MQTT: "); CM(topicSend); CM(": "); CMn(value);};
void commMQTT(const char* param, const char* value) {mqttClient.publish(param,value); CM("-в-> MQTT: "); CM(param); CM(": "); CMn(value);}
void getMQTT();
void ESP_MasterSlave();
#if defined GlobalHouseSwitch || defined MasterBedRoom
void SyncLEDtopics();
#endif
// -------------------------------------------------------------------------- Private function -----------------------------------------------------------------------
#endif
};

void XIIIMCommunicate::getWiFi() {if (WiFiOk && OTApossible) ArduinoOTA.handle(); static uint32_t wtime; static boolean firstStart;
if(millis()-wtime>250) {wtime = millis(); if (!WiFi.isConnected()) {if(WiFiOk) CMn("\nСоединение WiFi потеряно");
if(!firstStart) { WiFi.hostname(ESPName);
#if defined EEPROM_Enable
for_i(0,5) {if(strcmp(save.WIFI_SSID[i],"") && strcmp(save.WIFI_PASSWORD[i],"")) wifiMulti.addAP(save.WIFI_SSID[i],save.WIFI_PASSWORD[i]);}
wifiMulti.addAP(_WIFI_SSID,_WIFI_PASSWORD);
#endif
#if defined MQTT_SendEnable || defined OTAEnable
strcpy(WIFI_SSID,_WIFI_SSID);
#if defined OTAEnable
if(OTApossible) {
ArduinoOTA.setHostname(ESPName);
ArduinoOTA.onStart([]() {CMn("Start");});
ArduinoOTA.onEnd([]() {CMn("\nEnd");});
ArduinoOTA.onProgress([](uint16_t progress, uint16_t total) {CMf("Progress: %u%%\r", (progress / (total / 100)));});
ArduinoOTA.onError([](ota_error_t error) {CMf("Error[%u]: ", error);
if (error == OTA_AUTH_ERROR) CMn("Auth Failed");
else if (error == OTA_BEGIN_ERROR) CMn("Begin Failed");
else if (error == OTA_CONNECT_ERROR) CMn("Connect Failed");
else if (error == OTA_RECEIVE_ERROR) CMn("Receive Failed");
else if (error == OTA_END_ERROR) CMn("End Failed");}); ArduinoOTA.begin();}
#endif
#endif
}
if(!WiFiOk && !firstStart && ((millis()-wrongWiFiTime)<2000)) return;
if(!WiFiOk && firstStart && ((millis()-wrongWiFiTime)<5000)) return;
if(!firstStart || !WiFiOk) {firstStart=1; CMn("\nСоединяемся с WiFi...");} WiFiOk = 0;} if (wifiMulti.run() == WL_CONNECTED) {if (!WiFiOk) {IPAddress ip; ip = WiFi.localIP(); WiFiOk=1;
char Hostname[24] = {"ESP_"}; strcat(Hostname,ESPName); WiFi.hostname(Hostname);
CM("Соединились с "); CMn(WiFi.SSID().c_str()); sprintf(IPadress, "ESP IP: %03d.%03d.%03d.%03d", ip[0], ip[1], ip[2], ip[3]);
CMn(IPadress); wrongWiFiTime=millis();}} else CMn("\nНет cоединения! Повтор через 5 сек.");}}

#if defined MQTT_SendEnable
XIIIMCommunicate::XIIIMCommunicate() {mqttClient.setServer(mqtt_server, mqtt_port); mqttClient.setBufferSize(100);}

void XIIIMCommunicate::status(const char* param, const char* value){sendMQTT(param,value);}
void XIIIMCommunicate::status(const char* param, const char* value, const char* valueAdd){char valueSend[50]; strcpy(valueSend,value); strcpy(valueSend," "); strcat(valueSend,valueAdd); sendMQTT(param,value);}
void XIIIMCommunicate::status(const char* param, const char* paramNum, const char* value, const char* plus){char topicSend[50], paramSend[50]; strcpy(topicSend,param); strcat(topicSend,paramNum); sendMQTT(topicSend,value);}
void XIIIMCommunicate::status(const char* param, int32_t value){char valueSend[50]; itoa(value,valueSend,10); sendMQTT(param,valueSend);}
void XIIIMCommunicate::status(const char* param, int32_t value, const char* valueAdd){char valueSend[50]; itoa(value,valueSend,10); strcat(valueSend," "); strcat(valueSend,valueAdd); sendMQTT(param,valueSend);}
void XIIIMCommunicate::status(const char* param, uint8_t paramNum, char* value, const char* Plus){char topicSend[50], topNum[7]; strcpy(topicSend,param); itoa(paramNum,topNum,10); strcat(topicSend,topNum); sendMQTT(topicSend,value);}
void XIIIMCommunicate::status(const char* param, const char* value, int32_t valueAdd){char valueSend[50], valueSendAdd[7]; strcpy(valueSend,value); strcat(valueSend,": "); itoa(valueAdd,valueSendAdd,10); strcat(valueSend,valueSendAdd); sendMQTT(param,valueSend);}
void XIIIMCommunicate::status(const char* param, const char* paramNum, int32_t value, const char* plus){char topicSend[50], valueSend[7]; strcpy(topicSend,param); strcat(topicSend,paramNum); itoa(value,valueSend,10); sendMQTT(topicSend,valueSend);}
void XIIIMCommunicate::status(const char* param, uint8_t paramNum, int8_t value, const char* relay){char topicSend[50], valueSend[7]; strcpy(topicSend,param); itoa(paramNum,valueSend,10); strcat(topicSend,valueSend); itoa(value,valueSend,10); sendMQTT(topicSend,valueSend);}
void XIIIMCommunicate::status(const char* param, const char* paramNum, int32_t value, const char* valueAdd, const char* plus){char topicSend[50],valueSend[7]; strcpy(topicSend,param); strcat(topicSend,paramNum); itoa(value,valueSend,10); strcat(valueSend," "); strcat(valueSend,valueAdd); sendMQTT(topicSend,valueSend);}
void XIIIMCommunicate::status(const char* param, double &value){char topicSend[50], valueSend[50], val[7]; dtostrf(value,1,2,val); strcpy(valueSend,val); strcat(valueSend," : "); dtostrf(500*value,1,0,val); strcat(valueSend,val); strcat(valueSend,"ms"); sendMQTT(param,valueSend);}
void XIIIMCommunicate::status(const char* param, double &value, int32_t current){char topicSend[50], valueSend[50], val[7]; strcpy(valueSend,"Current "); itoa(current,val,10); strcat(valueSend,val); strcat(valueSend,"ms"); dtostrf(value,1,2,val); strcat(valueSend," Save "); strcat(valueSend,val); strcat(valueSend," : "); dtostrf(500*value,1,0,val); strcat(valueSend,val); strcat(valueSend,"ms"); sendMQTT(param,valueSend);}

void XIIIMCommunicate::command(const char* topic, const char* command, const char* value) {char topicSend[50]; strcpy(topicSend,topic); strcat(topicSend,"/Command/"); strcat(topicSend,command); commMQTT(topicSend,value);}
void XIIIMCommunicate::command(const char* topic, const char* command, int value) {char topicSend[50],valueSend[7]; strcpy(topicSend,topic); strcat(topicSend,"/Command/"); strcat(topicSend,command); itoa(value,valueSend,10); commMQTT(topicSend,valueSend);}
void XIIIMCommunicate::command(const char* topicNum, int32_t value) {char topicSend[50],valueSend[7]; strcpy(topicSend,save.controlTopic[0]); strcat(topicSend,"/Command/"); strcat(topicSend,topicNum); itoa(value,valueSend,10); commMQTT(topicSend,valueSend);}
void XIIIMCommunicate::command(const char* topic, char command, int value, const char* outControlTopic) {char topicSend[50],valueSend[7]; strcpy(topicSend,outControlTopic); strcat(topicSend,"/Command/"); strcat(topicSend,topic); itoa(command,valueSend,10); strcat(topicSend,valueSend); itoa(value,valueSend,10); commMQTT(topicSend,valueSend);}

void XIIIMCommunicate::getMQTT() {ESP_MasterSlave();
#if defined GlobalHouseSwitch || defined MasterBedRoom
SyncLEDtopics();
#endif
if(!WiFiOk) return; mqttClient.loop(); if(MQTTOk && mqttClient.connected()) return; static uint32_t MQTTtime; char topic[40]; static boolean MQTTWarn;
#if defined GlobalHouseSwitch || defined MasterBedRoom
#endif
if (millis() - MQTTtime > 100) {if (!MQTTOk && millis() - MQTTtime < 5000) return; MQTTtime = millis();
if (!MQTTOk || !mqttClient.connected()) {if (!MQTTWarn) {CMn("\nПодключаемся к MQTT серверу..."); MQTTOk = 0;}
strcpy(topic,"ESP_"); strcat(topic,ESPName); mqttClient.setCallback(MQTTread);
if(mqttClient.connect(topic,mqtt_user,mqtt_pass)) {CMn("MQTT сервер подключен"); char topic[50]; strcpy(topic,ESPName); strcat(topic,"/Command/#"); mqttClient.subscribe(topic,0); CM("Подписываемся на: "); CMn(topic);
#if defined ESP_EEPROM_Enable
#if defined GlobalHouseSwitch
mqttClient.subscribe("+/Status/Relay0",0); CMn("Подписываемся на все топики со Status/RelayX");
mqttClient.subscribe("+/Status/Relay1",0);
mqttClient.subscribe("+/Status/Relay2",0);
mqttClient.subscribe("+/Status/Relay3",0);
mqttClient.subscribe("+/Status/Relay4",0);
//mqttClient.subscribe("BedroomCO2/Status/AutoMode",0); CMn("Подписываемся на BedroomCO2/Status/AutoMode");
//mqttClient.subscribe("+/Status/MotionSensor",0); CMn("Подписываемся на все топики со Status/MotionSensor");
mqttClient.subscribe("+/Status/SCENE",0); CMn("Подписываемся на все топики со Status/SCENE");
mqttClient.subscribe("+/Status/IP",0); CMn("Подписываемся на все топики со Status/IP");
if (strcmp(save.controlTopic[0],"")) {strcpy(topic,save.controlTopic[0]); strcat(topic,"/Status/#"); mqttClient.subscribe(topic,0); CM("Подписываемся на: "); CMn(topic);}
//for_i(0,30) {if (strcmp(save.controlTopic[i],"")) {strcpy(topic,save.controlTopic[i]); strcat(topic,"/Command/#"); mqttClient.subscribe(topic,0); CM("Подписываемся на: "); CMn(topic);}}
#else
for_i(0,10) {if (strcmp(save.controlTopic[i],"")) {strcpy(topic,save.controlTopic[i]); strcat(topic,"/Status/#"); mqttClient.subscribe(topic,0); CM("Подписываемся на: "); CMn(topic);}}
#endif
#if defined GlobalHouseSwitch || defined MasterBedRoom
for_t(0,10) {if (strcmp(save.LEDTopic[t],"")) {CM("Подписываемся на: "); CMn(save.LEDTopic[t]); {for_i(0,5) {strcpy(topic,save.LEDTopic[t]); strcat(topic,"/Status/Relay"); 
char RelayNUM[2]; itoa(i,RelayNUM,10); strcat(topic,RelayNUM); mqttClient.subscribe(topic,0); CMn(topic);}
strcpy(topic,save.LEDTopic[t]); strcat(topic,"/Status/IP"); mqttClient.subscribe(topic,0); CMn(topic);}}}
#endif
#endif
MQTTWarn=0; MQTTOk = 1; SendStatus(1);}}}}

#if defined GlobalHouseSwitch || defined MasterBedRoom
void XIIIMCommunicate::SyncLEDtopics() {if(LEDSyncOk || !MQTTOk || !WiFiOk) return; static boolean firstCheckTopics, saveMQTT, saveWiFiOk;
if((!MQTTOk && !saveMQTT) || (!WiFiOk && !saveWiFiOk)) {for_t(0,10) SyncLEDTopic[t]=0; firstCheckTopics=0; LEDSyncOk=0;
CMn("Сброс синхронизации LED топиков"); saveMQTT=!MQTTOk; saveWiFiOk=!WiFiOk; return;} saveMQTT=!MQTTOk; saveWiFiOk=!WiFiOk;

if(LEDSyncOk) return; 
boolean check=0; static uint32_t stime; uint8_t topicCounter=0;

for_t(0,10) if(strcmp("",save.LEDTopic[t])) check=1; if(!check) {LEDSyncOk=1; // Нет контролируемых топиков
status("LED topics","Not control"); return;}

char SndTopic[70]; static uint8_t topicNum, lagTime, statrSync; if(lagTime==1 && millis()-stime<300) return;
if(lagTime==2 && millis()-stime<5000) return; stime=millis(); if(!statrSync) statrSync=1;

if(topicNum>=10) {firstCheckTopics=1; topicNum=0;}

for_t(0,10) {if(SyncLEDTopic[t]==1) {
CM("LED топик "); CM(t); CM(" "); CM(save.LEDTopic[t]); CMn(" синхронизирован, пропускаем");
topicCounter++;}
else if(!strcmp("",save.LEDTopic[t]) && t<10+1) {
//CM("Топик "); CM(t); CM(" "); CM(save.LEDTopic[t]); CMn(" пустой, пропускаем");
SyncLEDTopic[t]=2; topicCounter++;}}

if(topicCounter>=10) {status("LED topics","Synchronization complete");
LEDSyncOk=1; CMn("Все LED топики синхронизированы"); return;}

while(SyncLEDTopic[topicNum]) topicNum++;
if(topicNum>=10) {lagTime=0; return;}

CM("LED топиков синхронизировано "); CM(topicCounter); CM(" из "); CMn(10);

if(!firstCheckTopics) {//strcpy(SndTopic,save.LEDTopic[topicNum]); strcat(SndTopic," - not syncronized"); status("Controlled topic",topicNum,SndTopic,"plus");
CM("Запрос синхронизации от "); LEDSyncOk=0;
CMn(save.LEDTopic[topicNum]); command(save.LEDTopic[topicNum],"Status",1); lagTime=1; topicNum++; return;}

CM("Повтор сихро в LED топик: "); CMn(save.LEDTopic[topicNum]); lagTime=2; LEDSyncOk=0;
command(save.LEDTopic[topicNum],"Status",1); topicNum++;

}
#endif

void XIIIMCommunicate::ESP_MasterSlave() {static boolean slaveState; if((slaveState && masterSyncOk) || !MQTTOk || !WiFiOk) return; static boolean firstCheckTopics, saveMQTT, saveWiFiOk;
#if not defined GlobalHouseSwitch
const uint8_t numsOfTopic=10;
#else
const uint8_t numsOfTopic=30;
#endif
if((!MQTTOk && !saveMQTT) || (!WiFiOk && !saveWiFiOk)) {for_t(0,numsOfTopic) SyncTopic[t]=0; firstCheckTopics=0; masterSyncOk=0; slaveState=0; 
CMn("Сброс синхронизации топиков"); saveMQTT=!MQTTOk; saveWiFiOk=!WiFiOk; return;} saveMQTT=!MQTTOk; saveWiFiOk=!WiFiOk;
if(!slaveState && !MASTER_ESP && masterSyncOk) {// Slave отсылает статус реле после синхронизации
#if defined RelayEnable // Отправить в MQTT статус реле
CMn("Засинхронили, отправляем состояние реле");
for_i(0, sizeof(RELAY_Pin_)) if(RELAY_Pin_[i]!=nPIN) status("Relay",i,RELAY_Value_[i],"Plus");
#endif
slaveState=1; return;} if(masterSyncOk) return; 
boolean check=0; static uint32_t stime; uint8_t topicCounter=0;

for_t(0,numsOfTopic) if(strcmp("",save.controlTopic[t])) check=1; if(!check) {masterSyncOk=1; // Нет контролируемых топиков
if(MASTER_ESP) {status("ESP Module MASTER","Synchronization complete");} else {status("ESP Module SLAVE","Synchronization complete");} return;}

char SndTopic[70]; static uint8_t topicNum, lagTime, statrSync; if(lagTime==1 && millis()-stime<300) return;
if(lagTime==2 && millis()-stime<5000) return; stime=millis(); if(!statrSync) statrSync=1;

if(topicNum>=numsOfTopic) {firstCheckTopics=1; topicNum=0; if(!firstCheckTopics)
if(save.CommandToTopic0) status("Send command to Topic0","Yes"); else status("Send command to Topic0","No");}

for_t(0,numsOfTopic) {if(SyncTopic[t]==1) {
CM("Топик "); CM(t); CM(" "); CM(save.controlTopic[t]); CMn(" синхронизирован, пропускаем");
topicCounter++;}
else if(!strcmp("",save.controlTopic[t]) && t<numsOfTopic+1) {
//CM("Топик "); CM(t); CM(" "); CM(save.controlTopic[t]); CMn(" пустой, пропускаем");
SyncTopic[t]=2; topicCounter++;}}

if(topicCounter>=numsOfTopic) {if(MASTER_ESP) {status("ESP Module MASTER","Synchronization complete");}
else {status("ESP Module SLAVE","Synchronization complete");} masterSyncOk=1; CMn("Все топики синхронизированы"); return;}

while(SyncTopic[topicNum]) topicNum++;
if(topicNum>=numsOfTopic) {lagTime=0; return;}

CM("Топиков синхронизировано "); CM(topicCounter); CM(" из "); CMn(numsOfTopic);

if(!firstCheckTopics) {//strcpy(SndTopic,save.controlTopic[topicNum]); strcat(SndTopic," - not syncronized"); status("Controlled topic",topicNum,SndTopic,"plus");
CM("Запрос синхронизации от "); masterSyncOk=0;
CMn(save.controlTopic[topicNum]); command(save.controlTopic[topicNum],"Status",1); lagTime=1; topicNum++; return;}

CM("Повтор сихро в топик: "); CMn(save.controlTopic[topicNum]); lagTime=2; masterSyncOk=0;
command(save.controlTopic[topicNum],"Status",1); topicNum++;}

#if defined RelayEnable
void XIIIMCommunicate::statusRelay() {for_i(0,5) {if (RELAY_Value_Save_[i] != RELAY_Value_[i]) status("Relay",i,RELAY_Value_[i],"Relay");
if(save.CommandToTopic0 && RELAY_Value_Save_[i]!=RELAY_Value_[i]) {command("Relay",i,RELAY_Value_[i],save.controlTopic[0]);}}}
#endif
#endif // MQTT_SendEnable

void XIIIMCommunicate::loop() {
#if defined OTAEnable || defined MQTT_SendEnable
getWiFi();
#endif
#if defined MQTT_SendEnable
getMQTT();
#endif
}

#endif // XIIIMCommunicate_h