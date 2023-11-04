#ifndef XIIIMSave_h
#define XIIIMSave_h

#pragma once
#include <Arduino.h>
#include <EEPROM.h>

class XIIIMSave {
public:

void ReadData();
void SaveData();

uint16_t startAdress;         // стартовый адрес хранения данных в EEPROM
private:

};

void XIIIMSave::SaveData() {
#if defined ESP_EEPROM_Enable
EEPROM.begin (4096);
delay(10);
#endif
uint16_t addr = 4095;
#if defined ledIndikator_Enable
Led.Save_I=1;
#endif
EEPROM.put (addr, 'x');
addr = 0;
EEPROM.get (addr, startAdress);

if(save.saveCount >= 1000 || startAdress + sizeof(save) > 4095) {startAdress += sizeof(save); save.saveCount = 0; // меняем адрес каждые 1000 сохранений
if ((startAdress + sizeof(save)) > 4095) {startAdress = sizeof(startAdress); CM("startAdress = "); CMn(startAdress);} EEPROM.put (0, startAdress);} save.saveCount++;

addr = startAdress;
EEPROM.put (addr, save);
addr = addr+(sizeof(save));
EEPROM.put (addr,save.saveCount);
#if defined ESP_EEPROM_Enable
EEPROM.end();
#endif
CM("Записали "); CM(sizeof(save)); CM(" bytes "); CM("по адресу: "); CM(startAdress); CM(" | "); 
CM(save.saveCount); CMn(" раз(а).");
}

void XIIIMSave::ReadData() {uint8_t initread=0; int16_t addr=4095;
#if defined ESP_EEPROM_Enable
EEPROM.begin(4096);
delay(10);
#endif
EEPROM.get (addr, initread); if (char(initread) != 'x') {CMn("Первый запуск. Инициализация EEPROM."); 
#if defined ESP_EEPROM_Enable
EEPROM.end(); delay(10); 
#endif
saveChange=1;} else {
addr = 0;
EEPROM.get (addr, startAdress);
addr = startAdress;
EEPROM.get (addr, save);
#if defined ESP_EEPROM_Enable
EEPROM.end();
#endif
}
CM("Читаем данные по адресу: "); CMn(startAdress);
#if defined MQTT_SendEnable || defined OTAEnable
//CM("WiFi сеть: "); CMn(WIFI_SSID);
boolean wifiPresent=0; for_i(0,5) {if(strcmp(save.WIFI_SSID[i],"")) {wifiPresent=1; CM("Доп WiFi сеть "); CM(i); CM(": "); CMn(save.WIFI_SSID[i]);}} 
if(!wifiPresent) CMn("Нет доп WiFi сетей");
#endif
#if defined MQTT_SendEnable
#if defined GlobalHouseSwitch
uint8_t ctrlNumTopic=30;
#else
uint8_t ctrlNumTopic=10;
#endif
boolean topicPresent=0; for_i(0,ctrlNumTopic) if(strcmp(save.controlTopic[i],"")) topicPresent=1;
if(topicPresent) {for_i(0,ctrlNumTopic) {if(strcmp(save.controlTopic[i],"")) {CM("Контролим топик "); CM(i); CM(": "); CMn(save.controlTopic[i]);}}
} else CMn("Не контролим топики");

#if defined GlobalHouseSwitch || defined MasterBedRoom
topicPresent=0; for_i(0,10) if(strcmp(save.LEDTopic[i],"")) topicPresent=1;
if(topicPresent) {for_i(0,10) {if(strcmp(save.LEDTopic[i],"")) {CM("Включать LED топик "); CM(i); CM(": "); CMn(save.LEDTopic[i]);}}
} else CMn("Не контролим LED топики");

CMn(save.LEDControl ? "Контролим LED квартиры" : "Не контролим LED квартиры");
#endif

CM("Дублировать команды в 0 топик: "); CMn(save.CommandToTopic0 ? "Да" : "Нет");

CM("ESP модуль: "); CMn(save.MASTER_ESP ? "MASTER" : "SLAVE");
#endif
CM("Авто режим: "); CMn(save.autoMode ? "Включен" : "Отключен");
CM("Время StandBy режима: "); CM(save.standByTime); CMn(" сек.");
CM("Время StandByShot режима: "); CM(save.standByShotTime); CMn(" сек.");
CM("Время StandByQuick режима: "); CM(save.standByQuickTime); CMn(" сек.");
#if defined kitchenVent_Enable || defined MasterBathRoom
CM("Дежурная работа вытяжки после выкл света: "); CM(save.ventAutoTime); CMn(" сек.");
#endif
#if defined ButtonEnable
if(save.pressSpeed < 0.8) save.pressSpeed=0.8; if(save.pressSpeed > 4) save.pressSpeed=4; char value[7]; dtostrf(save.pressSpeed,1,2,value);
CM("Задержка кнопки: "); CM(value); CM(" : "); dtostrf(500*save.pressSpeed,1,0,value); CM(value); CMn("мсек.");
#endif
#if defined BuzerEnable
CMn(save.buzer ? "Buzer Enable" : "Buzer Disable");
#endif
#if defined MasterSceneKitchen
CM("Движ возле мойки: "); CMn(save.MotionWashEnable ? "Учитывать" : "Игнорить");
CM("Свет возле мойки на: "); CM(save.MotionWashTime); CMn(" сек.");
#endif
#if defined MotionSens_Enable
CM("Реагировать на движение: "); CMn(save.MotionDetectEnable ? "Да" : "Нет");
CM("Игнорировать движение: "); CM(save.MotionIgnore); CMn(" сек.");
CM("Память движения: "); CM(save.MotionOnMemory); CMn(" сек.");
#else
if (save.MASTER_ESP) {
CM("Реагировать на движение: "); CMn(save.MotionDetectEnable ? "Да" : "Нет");
CM("Игнорировать движение: "); CM(save.MotionIgnore); CMn(" сек.");
CM("Память движения: "); CM(save.MotionOnMemory); CMn(" сек.");}
#endif
#if defined MotionSens_Enable && defined PresenceSens_Enable
CM("Реагировать на присутствие: "); CMn(save.PresenceDetectEnable ? "Да" : "Нет");
CM("Игнорировать присутствие: "); CM(save.PresenceIgnore); CMn(" сек.");
CM("Память присутствия: "); CM(save.PresenceOnMemory); CMn(" сек.");
#endif
#if defined Vibro_Enable
CMn(save.VibroDetectEnable ? "Реагировать на сенсор" : "Не реагировать на сенсор");
CM("Игнорим после сработки: "); CM(save.timeIgnoreVibroEvent); CMn(" сек.");
CM("Порог сработки: "); CMn(save.vibroLevel);
CM("Добавляем вибро на "); CM(save.vibroTimePlus); CMn(" мин.");
CM("Кол-во сработок для активации: "); CMn(save.vibroCount);
CM("Считать по-новой после: "); CM(save.vibroCountReset); CMn(" сек.");
CM("Время отображения сработки: "); CM(save.vibroWarnTime); CMn(" сек.");
CM("Время шага: "); CM(save.timeStep); CMn(" Мсек.");
CM("Время между шагами: "); CM(save.timeWait); CMn(" Мсек.");
CM("Минимум шагов: "); CMn(save.minSteps);
CM("Максимум шагов: "); CMn(save.maxSteps);
CM("Мин до след шагов: "); CM(save.minNext); CMn(" сек.");
CM("Макс до след шагов: "); CM(save.maxNext); CMn(" сек.");
#endif
#if defined RGB_LED_Enable
CM("Color: "); CMn(save.hexColor);
CM("Favorite Color: "); CMn(save.favoriteColor);
CM("Bright Color: "); CMn(save.brightColor);
CM("Gamma Correction: "); CMn(save.GammaCorrection ? "ON" : "OFF");
CM("StartMode: "); if (save.StartMode == 0) CMn("Restore state"); else if (save.StartMode == 1) CMn("Turn OFF");
else if (save.StartMode == 2) CMn("Favorite Color");
CM("Fade delay: "); CM(save.FadeDelay); CMn(" ms");
#endif
#if defined RGB_MODULE_LED_Enable
for_t(0,NUM_LEDS) {
CM("Color module"); CM(t); CM(": "); CMn(save.SaveModRGB[t].hexColor);
CM("Favorite Color module"); CM(t); CM(": "); CMn(save.SaveModRGB[t].favoriteColor);
CM("Bright Color module"); CM(t); CM(": "); CMn(save.SaveModRGB[t].brightColor);
CM("StartMode module"); CM(t); CM(": "); if (save.StartMode[t] == 0) CMn("Restore state"); else if (save.StartMode[t] == 1) CMn("Turn OFF");
else if (save.StartMode[t] == 2) CMn("Favorite Color");
}
CM("Fade delay: "); CM(save.FadeDelay); CMn(" ms");
CM("Gamma Correction: "); CMn(save.GammaCorrection ? "ON" : "OFF");
#endif
#if defined Cold_Warm_LED_Enable
CM("ColdWarm: "); CM(save.ColdWarm); CMn(" %");
CM("Normal Light value: "); CM(save.currentLight); CMn(" %");
CM("Night Light value: "); CM(save.nightLight); CMn(" %");
CM("Fade Delay: "); CM(save.fadeDelay); CMn(" ms");
#endif
}

#endif // XIIIMSave_h