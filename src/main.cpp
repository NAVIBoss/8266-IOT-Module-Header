#define ESPName "Test"                 // топик MQTT для отправки сообщений (Command, Status) max 20 символов
#define FirmwareVersion "5.3"                  // версия прошивки

//#define clearMemory                          // записать в память начальные параметры
#define DebagEnable                          // вывод в порт
#define EEPROM_Enable                        // сохранение данных в Arduino
#define ESP_EEPROM_Enable                    // сохранение данных в EPS8266
#define MQTT_SendEnable                      // отправка данных в MQTT
#define OTAEnable                            // прошивка по воздуху
#define ledIndikator_Enable                  // индикация режимов работы
#define MonoIndikator                        // индикация только синим
#define InverseOutIndikator                  // инвертировать выход индикаторов (для внутреннего)
//#define BH1750_Enable                        // датчик освещенности
//#define MAX44009_Enabled                     // датчик освещенности
//#define VL6180X_Enable                       // определение взмаха рука по датчику VL6180X
//#define BME280_Enable                        // датчик температуры, влажности, давления
//#define AM2301A_Enabled                      // датчик температуры, влажности
//#define AM2320_Enabled                       // датчик температуры, влажности
//#define S8_CO2_Enable                        // датчик углекислого газа
//#define HX711_Enable                         // тензодатчик
//#define Vibro_Enable                         // датчик вибрации (сенсор PIN 2, Реле PIN 3)
//#define PZEM004T_Enable                      // датчик нарпяжения и тока PZEM004T
//#define ButtonEnable                         // управление c кнопок
//#define MotionSens_Enable                    // датчик движения
//#define PresenceSens_Enable                  // датчик присутствия - учитывается только после чработки датчика движения
//#define MasterSceneLivingRoom                // сцены управления в зале
//#define MasterSceneKitchen                   // сцены управления на кухне
//#define MasterSceneCorridor
//#define GlobalHouseSwitch                    // сцены управления всей квартирой в коридоре (кнопка на входе)
//#define BadRoomRGBRule_Enable                // для спальни - откл светодиоды, если вкл яркий свет и наоборот
//#define MasterBedRoom                        // сцены управления в спальне (LED подсветка по всей квартире) - модуль CO2
//#define MasterBathRoom                       // сцены управления ванной
//#define RelayEnable                          // управление реле
//#define CommandToRelay                       // выполнять команды реле напрямую
#define InverseOutRelay                      // когда 0 - реле замкнуто
//#define IRSens_Enable                        // ИК датчик приближения (взмаха) руки
//#define kitchenVent_Enable                   // вентилятор на вытяжке (по взмаху) 2-LED 12-Sens n,n,4,n,5-Relay(x)
//#define RGB_LED_Enable                       // подсветка RGB управление по Relay(x) - nPIN,nPIN,RGBPIN - Relay2
//#define RGB_MODULE_LED_Enable                // подсветка RGB управление модулями по Relay(x) - nPIN,nPIN,RGBPIN0 - Relay2

//#define Cold_Warm_LED_Enable                 // светодиодный светильник Cold-Warm Relay0 - CWPIN

/*  Команды настройки из MQTT:
*   SSIDx                     Login WiFi x
*   PASSx                     Password WiFi x
*   Master                    Синхронизирующий/синхронизируемый модуль (1/0)
*   AutoMode                  Авто режим - будет ли включаться свет от датчиков (1/0)
*   StandByTime               На сколько отключается Авто режим после управления кнопками или IR сенсором (сек) (0-не работает)
*   StandByShotTime           Через сколько отключить рабочую зону после прекращения в ней движения (0-не работает)
*   StandByQuickTime          Время дежурной подсветки после выключения всего света (SCENE 2 Shot) (сек) (0-не работает)
*   ButtonDelay               Коэффициент задержки кнопки - умножается 500мс на коэффициент - время shot нажатия (0.80-4.00 - до 2 знаков)
*   VentTime                  Время работы вытяжки после выключения рабочей зоны кухни, света в ванной (сек)
*   MotionMemory              Время, на которое сенсор считается сработавшим после отсутствия движения (сек)
*   MotionIgnore              Сколько не реагировать на движение после перехода в неактивное состояние (сек)
*   MotionEnable              Реагировать на движение (1/0)
*   PresenceEnable            Реагировать на присутствие (1/0)
*   PresenceMemory            Время, на которое сенсор считается сработавшим после перехода в неактивное состояние (сек)
*   PresenceIgnore            Сколько не реагировать на присутствие после перехода в неактивное состояние (сек)
*   MotionWashEnable          Реагировать на движение возле мойки (1/0)
*   MotionWashTime            На какое время включать свет возле мойки от движения (сек)
*   TopicX                    10 контролируемых топиков модулей (до 20 символов)
*   LEDTopicX                 10 топиков для включения LED подсветки
*   LEDControl                управлять LED подсветкой
*   CommandToTopic0           отсылать команды в топик 0
*   Status                    статус только для синхронизации модулей (Relay, Motion, StandBy)
*   AllStat                   Выдать статус всех параметров и исполнителей
*   Reset                     Перезагрузить модуль
*   Default                   Записать в память начальные параметры по умолчанию
*   
*   RelayX                    Переключить реле X (1/0)
*   DecimalTemp               Показывать температуру до десятых в пределах -10 <> 10 °C
*   ThresholdTemp             Порог температуры срабатывания
*   ThresholdHUM              Порог влажности срабатывания
*   HysteresisTemp            Гистерезис температуры срабатывания
*   HysteresisHUM             Гистерезис влажности срабатывания
*   Tare                      Сброс веса на 0
*   VibroSensor               Реагировать на вибро (1/0)
*   VibroLevel                Порог сработки вибро сенсора
*   VibroWarnTime             Время отображения сработки (сек)
*   VibroTimePlus             Добавляем вибро на (x) минут
*   VibroEventCount           Кол-во сработок для активации
*   TimeCountReset            Считать по-новой, если нет вибрации после (x) сек
*   TimeVibroIgnore           Игнорим после сработки вибро до мледующей (сек)
*   TimeStep                  Время шага (Мсек)
*   TimeWait                  Время между шагами (Мсек)
*   MinSteps                  Минимум шагов
*   MaxSteps                  Максимум шагов
*   MinNext                   Мин до след шагов (сек)
*   MaxNext                   Макс до след шагов (сек)

*   Color                     Установка цвета: #8D2613
*   RelayX                    Включение/выключение 0/1 [0] - выкл, 1 - вкл
*   MyColor                   Смена любимого цвета: [#62006C] (можно установить при включении/запуске/перезагрузке)
*   BrColor                   Цвет яркой подсветки: [#E700FF] для StandBy режимов
*   BrightMode                Включить яркую подсветку: 1/0 [0] режим яркой подсветки
*   Gamma                     Вкл/Откл гамма коррекцию: 0/1 [1] - вкл, 0 - выкл
*   Fade                      Смена задержки переходов: [4] чем меньше задержка, тем быстрее переход (в мСек)
*   Mode                      Установить при запуске: 0/1/2 [0] - венуть как было, 1 - выключить, 2 - любимый цвет
*   
*   ColdWarm                  Процентное соотношение от холодного к тепломк свету
*   Light                     Максимальная яркость %
*   NightLight                Яркость в дежурном режиме %
*   Fade                      Смена задержки переходов: [2] чем меньше задержка, тем быстрее переход (в мСек)
*
*   ResEnergy                 Сброс счетчика электроэнергии kWh
*/

#include <Arduino.h>

#define StopHere {CMn("Programm stoped"); for(;;);} // вечный цикл остановит выполнение в этой точке (if (criticalError) StopHere;)

#define EVERY_MS(x) \
static uint32_t tmr;\
bool flag = millis() - tmr >= (x);\
if (flag) tmr += (x);\
if (flag)                                           // Выполнять каждые x мс - EVERY_MS(100) {...}

#define returnMS(x) \
{static uint32_t tms;\
if (millis() - tms >= x) tms = millis();\
else return;}                                       // Возврат, если прошло меньше x мс

#define returnSec(x) \
{static uint32_t tms;\
if (millis() - tms >= x*1000) tms = millis();\
else return;}                                       // Возврат, если прошло меньше x с

#if defined DebagEnable
#define CMn2(x,y) Serial.println(x,y)
#define CM2(x,y) Serial.print(x,y)
#define CMn(x) Serial.println(x)
#define CM(x) Serial.print(x)
#define CMf(x,y) Serial.printf(x,y)
#else
#define CMn2(x,y)
#define CM2(x,y)
#define CMn(x)
#define CM(x)
#define CMf(x,y)
#endif

#define nPIN 99                                 // незадействованный пин
#define RGBPIN 55                               // PIN реле управления RGB подсветкой (Relay(x))
#define RGBPIN0 56                              // PIN реле управления RGB подсветкой (Relay(x))
#define RGBPIN1 57                              // PIN реле управления RGB подсветкой (Relay(x))
#define RGBPIN2 58                              // PIN реле управления RGB подсветкой (Relay(x))
#define RGBPIN3 59                              // PIN реле управления RGB подсветкой (Relay(x))
#define RGBPIN4 60                              // PIN реле управления RGB подсветкой (Relay(x))
#define CWPIN 66                                // PIN реле управления Cold Warm светильником (Relay(x))

#if defined InverseOutRelay
#define writeRelay(x,i) digitalWrite(x,!i)
#else
#define writeRelay(x,i) digitalWrite(x,i)
#endif

#define for_i(from, to) for(uint8_t i = (from); i < (to); i++)
#define for_t(from, to) for(uint8_t t = (from); t < (to); t++)

boolean standBy = 0;                            // режим StandBy
boolean standByShot = 0;                        // режим standByShot - включение Авто режима после 60 сек, после окончания движения
boolean standByQuick = 0;                       // режим standByQuick - включение Авто режима после 15 сек, если Выкл все
boolean ventStandBy = 0;                        // идет отсчет отключения вытяжки
boolean WorkZoneLight = 0;                      // режим подсветки возле мойки от движения
uint8_t SCENE=0;                                // сцена кнопки
boolean shotPress=0;                            // быстрое нажатие
boolean longPress=0;                            // долгое нажатие
boolean doublePress=0;                          // двойное нажатие
uint32_t standByTimeStart;                      // начало отсчета standBy режимов
boolean OTApossible = 0;                        // хватит ли места в памяти для OTA прошивки
uint32_t MotionTimer = 0;                       // счетчик оставшегося времени
uint32_t motionStart;                           // начало отсчета времени индикации движения
uint32_t timeMotionIgnore;                      // время начала игнорирования движения
boolean Motion = 0;                             // на MASTER или SLAVE есть движение
boolean MotionSensor = 0;                       // состояние движения - если есть датчик или модуль MASTER
boolean brightMode = 0;                         // режим яркой подсветки
boolean InitializationOk = 0;                   // Инициализация завершена (Setup)

#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
int16_t tempC, humidity, pressure;
#endif

#if defined GlobalHouseSwitch || defined MasterBedRoom
boolean RELAY_State_[10][5];                    // Состояние LED подсветки для восстановления
boolean SyncLEDTopic[]{0,0,0,0,0,0,0,0,0,0};    // Состояние LED топиков получено
#endif

#if defined GlobalHouseSwitch
boolean AnybodyHome=1;                          // Кто-то дома (движение, переключение)
#endif

#if defined MQTT_SendEnable || defined OTAEnable
boolean WiFiOk = 0;                             // есть подключение к WiFi
boolean MQTTOk = 0;                             // есть подключение к MQTT
char WIFI_SSID[40];
#endif

#if defined MQTT_SendEnable
char ReciveTopic[50];                           // входящий топик MQTT
char ReceiveValue[50];                          // входящее сообщение MQTT
void MQTTread(char* intopic, byte* payload, unsigned int length);
void SendStatus(uint8_t sendSt);
#endif

#if defined MasterSceneKitchen
int32_t motionWashStart= -3600*1000;            // начало отсчета времени включения света около мойки
#endif

#if defined ButtonEnable || defined RelayEnable || defined IRSens_Enable
uint8_t RELAY_Value_[] = {0,0,0,0,0};           // обрабатываемые состояния реле
uint8_t RELAY_Value_Save_[] = {0,0,0,0,0};      // сохраненные состояния реле
#endif

#if defined RelayEnable
uint8_t RELAY_Pin_[] = {12,14};    // управление реле - для ESP8266-01 - только 0,3 работают с SSD-DC | nPIN - вирт пин
boolean saveRelay = 0;                          // сохранение состояний реле только после отсылки статуса
#endif

#if defined RGB_MODULE_LED_Enable
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_FORCE_SOFTWARE_SPI
#include <FastLED.h>                           // управление RGB модулями P9813
#define NUM_LEDS 2                             // сколько модулей
#define DATA_PIN 1                            // Data PIN
#define CLOCK_PIN 15                           // Clock PIN
CRGB leds[NUM_LEDS];
#endif

#if defined RGB_MODULE_LED_Enable
struct ModRGB {                                 // данные RGB модулей P9813
uint8_t Led_Value_Save[3] = {0,0,0};
char hexColor[8] = "#62006C";
char favoriteColor[8] = "#62006C";
char brightColor[8] = "#E700FF";
};
#endif

#if defined EEPROM_Enable
#include <EEPROM.h>
boolean saveChange = 0;                         // нужно сохранить данные
struct Save {
uint16_t saveCount=0;                           // счетчик записи в одну и ту же ячейку
char WIFI_SSID[5][20];                          // точка доступа WiFi сетей
char WIFI_PASSWORD[5][20];                      // пароль WiFi сетей
boolean autoMode = 1;                           // задействовать датчики | только ручное управление
#if defined MQTT_SendEnable
#if defined GlobalHouseSwitch
char controlTopic[30][20];                      // 30 контролируемых топиков
#else
char controlTopic[10][20];                      // контролируемые топики
#endif
#endif
boolean CommandToTopic0 = 0;                    // отправлять команды в нулевой контролируемый топик Command
boolean MASTER_ESP = 0;                         // ESP Master/Slave модуль | Master синхронизирует все контролируемые топики
#if defined ButtonEnable && not defined GlobalHouseSwitch
uint16_t standByTime = 0;                       // время StandBy режима (сек) = 0, если модуль управления с кнопок
#else
uint16_t standByTime = 3600;                    // время StandBy режима (сек) | переключили кнопками или IR
#endif
uint16_t standByShotTime = 120;                 // время StandShotBy режима (сек) | переключили от движения
uint16_t standByQuickTime = 15;                 // время StandQuickBy режима (сек) | нажали Выкл Все - SCENE 2 Shot
#if defined MotionSens_Enable
boolean MotionDetectEnable = 1;                 // реагировать на движение общее
#else
boolean MotionDetectEnable = 0;                 // реагировать на движение общее
#endif
uint8_t MotionIgnore = 0;                       // сколько не реагировать после перехода сенсора в режим Off (сек) | отключения квартиры (Коридор)
uint8_t MotionOnMemory = 3;                     // сколько считать сенсор сработавшим после отключения (сек)

#if defined MotionSens_Enable && defined PresenceSens_Enable
boolean PresenceDetectEnable = 0;               // реагировать на присутствие
uint8_t PresenceIgnore = 5;                     // сколько не реагировать после перехода сенсора в режим Off (сек)
uint8_t PresenceOnMemory = 3;                   // сколько считать сенсор сработавшим после отключения (сек)
#endif

#if defined kitchenVent_Enable || defined MasterBathRoom
int16_t ventAutoTime = 60;                      // время работы вытяжки после отключения рабочей зоны кухни, света в ванной (сек)
#endif
#if defined ButtonEnable
double pressSpeed = 0.80;                       // коэффициент задержек срабатывания кнопки 0.8 - оригинал 0.8 - 2.1 - 4.0 и т.д.
#endif
#if defined MasterSceneKitchen
boolean MotionWashEnable = 1;                   // реагировать на движение возле мойки на кухне
uint8_t MotionWashTime = 40;                    // время включения раб зоны кухни от движения возле мойки
#endif
#if defined Vibro_Enable
boolean VibroDetectEnable = 1;                  // использовать сенсор вибрации или звукового давления
uint8_t timeIgnoreVibroEvent = 10;              // время не реагируем после сработки сенсора (сек)
int16_t vibroLevel = 1000;                      // порог превышения вибрации
uint8_t vibroTimePlus = 30;                     // сколько времени добавляем (мин)
uint8_t vibroCount = 3;                         // на какой раз сработки запускаем Event
int16_t vibroCountReset = 180;                  // сброс счетчика событий, если сенсор не сработал, через (сек)
uint8_t vibroWarnTime = 5;                      // сколько времени отображаем сработку сенсора (сек)
uint8_t timeStep = 25;                          // время шага (Мсек)
uint16_t timeWait = 400;                        // время между шагами (Мсек)
uint8_t minSteps = 2;                           // минимум шагов
uint8_t maxSteps = 4;                           // максимум шагов
uint8_t minNext = 2;                            // минимальное время после шагов до следующих (сек)
uint8_t maxNext = 20;                           // максимальное время после шагов до следующих (сек)

#endif
#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
boolean DecimalTemp = 0;                        // Показывать температуру до десятых в пределах -10 <> 10 °C
int16_t tempC, humidity, pressure;
int16_t thresholdTemp=26;
int16_t thresholdHUM=40;
uint8_t hysteresisTemp=2;
uint8_t hysteresisHUM=10;
#endif
#if defined RGB_LED_Enable
uint8_t Led_Value_Save_[3] = {0,0,0};
int16_t FadeDelay = 10;
char hexColor[8] = "#62006C";
char favoriteColor[8] = "#62006C";
boolean Power = 0;
boolean GammaCorrection = 1;
uint8_t StartMode = 0;
char brightColor[8] = "#E700FF";
#endif
#if defined RGB_MODULE_LED_Enable
int16_t FadeDelay = 10;
boolean GammaCorrection = 1;
ModRGB SaveModRGB[5];                           // цвета обычный, любимый, яркий
uint8_t StartMode[5] = {0,0,0,0,0};
boolean Power[5] = {0,0,0,0,0};                 // состояние реле RGB вкл/выкл
#endif
#if defined Cold_Warm_LED_Enable
uint8_t nightLight = 5;                         // уровень яркости в ночном режиме %
uint8_t currentLight = 90;                      // текущий уровень яркости в обычном режиме %
uint8_t ColdWarm = 80;                          // соотношение Cold - Warm %
uint16_t fadeDelay = 2;                         // задержка для димирования освещенности
#endif
#if defined GlobalHouseSwitch || defined MasterBedRoom
char LEDTopic[10][20];                          // топики для пробуждения квартиры (включение LED подсветки)
boolean LEDControl=1;                           // управлять LED подсветкой
#endif
} save;
#endif

#if defined ledIndikator_Enable
#include "Led.h"
#if defined MonoIndikator && defined InverseOutIndikator
XIIIMLED Led(2);                                // BUILTIN_LED
#else
XIIIMLED Led(13);                            // ([Синий PIN][, красный PIN]) без параметров - BUILTIN_LED
#endif
#define SyncInd(x) Led.SyncInd=x
#else
#define SyncInd(x)
#endif

#if defined EEPROM_Enable
#include "Save.h"
XIIIMSave dataToEEPROM;
#define saveChange(x) saveChange=1
#else
#define saveChange(x)
struct Save {
boolean autoMode = 1;                           // задействовать датчики | только ручное управление
#if defined GlobalHouseSwitch
char controlTopic[30][20];                      // 30 контролируемых топиков
#else
char controlTopic[10][20];                      // контролируемые топики
#endif
boolean CommandToTopic0 = 0;                    // отправлять команды в нулевой контролируемый топик Command
boolean MASTER_ESP = 0;                         // ESP Master/Slave модуль | Master синхронизирует все контролируемые топики
uint16_t standByTime = 10;                    // время StandBy режима (сек) | переключили кнопками или IR
uint16_t standByShotTime = 8;                 // время StandShotBy режима (сек) | переключили от движения
uint16_t standByQuickTime = 5;                 // время StandQuickBy режима (сек) | нажали Выкл Все - SCENE 2 Shot
#if defined MotionSens_Enable 
boolean MotionDetectEnable = 1;                 // реагировать на движение общее
#else 
boolean MotionDetectEnable = 0;                 // реагировать на движение общее
#endif 
uint8_t MotionIgnore = 0;                       // сколько не реагировать после перехода сенсора в режим Off (сек) | отключения квартиры (Коридор)
uint8_t MotionOnMemory = 3;                     // сколько считать сенсор сработавшим после отключения (сек)
#if defined MotionSens_Enable && defined PresenceSens_Enable
boolean PresenceDetectEnable = 1;               // реагировать на присутствие
uint8_t PresenceIgnore = 0;                     // сколько не реагировать после перехода сенсора в режим Off (сек)
uint8_t PresenceOnMemory = 3;                   // сколько считать сенсор сработавшим после отключения (сек)
#endif
#if defined kitchenVent_Enable || defined MasterBathRoom
int16_t ventAutoTime = 60;                      // время работы вытяжки после отключения рабочей зоны кухни, света в ванной (сек)
#endif
#if defined ButtonEnable
double pressSpeed = 0.8;                        // коэффициент задержек срабатывания кнопки 0.8 - оригинал 0.8 - 2.1 - 4.0 и т.д.
#endif
#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
boolean DecimalTemp = 0;                        // Показывать температуру до десятых в пределах -10 <> 10 °C
int16_t tempC, humidity, pressure;
int16_t thresholdTemp=26;
int16_t thresholdHUM=40;
uint8_t hysteresisTemp=2;
uint8_t hysteresisHUM=10;
#endif

#if defined RGB_MODULE_LED_Enable
int16_t FadeDelay = 10;
boolean GammaCorrection = 1;
ModRGB SaveModRGB[5];                           // цвета обычный, любимый, яркий
uint8_t StartMode[5] = {0,0,0,0,0};
boolean Power[5] = {0,0,0,0,0};                 // состояние реле RGB вкл/выкл
#endif
} save;
#endif

#if defined OTAEnable
#include <ArduinoOTA.h>
#endif

#if defined OTAEnable || defined MQTT_SendEnable
#include "Comm.h"
XIIIMCommunicate Comm;
#endif

#if defined MQTT_SendEnable
#define MQTTStatus4(i,x,y,z) Comm.status(i,x,y,z)
#define MQTTStatus3(x,y,z) Comm.status(x,y,z)
#define MQTTStatus(x,y) Comm.status(x,y)
#define MQTTSnd(x) Comm.status(x)
#else
#define MQTTStatus4(i,x,y,z)
#define MQTTStatus3(x,y,z)
#define MQTTStatus(x,y)
#define MQTTSnd(x)
#endif

#if defined ButtonEnable
#include "Button.h" // !первый 0 - INPUT_PULLUP
XIIIMButton Button(0,0,2);                     // 0/1 INPUT_PULLUP/INPUT, пины под кнопки с замыканием на 0 - для ESP8266-01 Button (0,2) до 4
#endif

#if defined Vibro_Enable
#include "Vibro.h"
XIIIMVibro Vibro(2,3);                         // PIN сенсора vibro, PIN управления вибро
#endif

#if defined MotionSens_Enable && defined PresenceSens_Enable
#include "Presence.h"
XIIIMPresence Presen(16);                       // PIN сенсора присутствия
#endif

#if defined MotionSens_Enable
#include "Motion.h"
XIIIMMotion Move(14);                          // PIN сенсора движения
#endif

#if defined IRSens_Enable
#include "IRSens.h"
XIIIMIR IRSens(12);
boolean IRSensor = 0;                          // состояние ИК датчика взмаха
#endif

#if defined RGB_LED_Enable
#include "RGB.h"
XIIIMRGB RGB(0,1,3);                         // PIN ESP Red Greeen Blue (ESP-01s 0,2,3)
#endif

#if defined RGB_MODULE_LED_Enable
#include  "moduleRGB.h"
XIIIMmoduleRGB mRGB;
#endif

#include "CountDown.h"
XIIIMCount CountDown;

#if defined Cold_Warm_LED_Enable
#include "CWLED.h"
XIIIMCWLED CWLED(4,5);                         // PIN ESP Cold Warm (ESP-01s 0,2)
#endif

#if defined HX711_Enable
const uint8_t LOADCELL_DOUT_PIN = 4;           // Указываем номер вывода, к которому подключен вывод DT  датчика
const uint8_t LOADCELL_SCK_PIN = 5;            // Указываем номер вывода, к которому подключен вывод SCK датчика
#endif

#if defined VL6180X_Enable || defined BH1750_Enable || defined BME280_Enable || defined MAX44009_Enabled || defined AM2320_Enabled// Wire
#define SDA 4                                  // GPIO 0 on ESP-01 module 4-Wemos
#define SCL 5                                  // GPIO 2 on ESP-01 module 5-Wemos
#endif

#if defined AM2301A_Enabled
#define DHTPIN 5                               // сигнальный выход датчика
#endif

#if defined S8_CO2_Enable
#define Uart_Rx 12                             // подключаем Uart_Tx датчика S8 CO2
#define Uart_Tx 14                             // подключаем Uart_Rx датчика S8 CO2
#endif

#if defined PZEM004T_Enable
#define Uart_Rx 4                              // подключаем Uart_Tx датчика S8 CO2
#define Uart_Tx 5                              // подключаем Uart_Rx датчика S8 CO2
#endif

#if defined BH1750_Enable || defined VL6180X_Enable || defined BME280_Enable || defined HX711_Enable || defined AM2301A_Enabled || defined MAX44009_Enabled || defined S8_CO2_Enable || defined AM2320_Enabled || defined PZEM004T_Enable
#include "Sensors.h"
#endif

#if defined GlobalHouseSwitch && defined MQTT_SendEnable
void AnybodyatHome(boolean akt) {
if(akt == AnybodyHome || !save.autoMode) return; AnybodyHome = akt;
switch (akt) {
case 0: // Выключаем квартиру
CMn("Выключаем квартиру"); AnybodyHome=0; Comm.status("AnybodyHome",0);
for_t(1,30) {if(!strcmp(save.controlTopic[t],"")) return; for_i(0,5) {Comm.command("Relay",i,0,save.controlTopic[t]);}}
break;
case 1: // Восстанавливаем квартиру
CMn("Восстанавливаем квартиру"); for_t(0,10) {if(strcmp(save.LEDTopic[t],"")) {
for_i(0,5) {if(RELAY_State_[t][i]) Comm.command("Relay",i,1,save.LEDTopic[t]);}}}
AnybodyHome=1; Comm.status("AnybodyHome",1);
break;
}}
#endif

void SwitchScene() {                           // Управление в зависимости от сцен
#if defined MasterBedRoom
return;
#endif

if (!SCENE) return; boolean ctrl=0;
CM(">>> SS Scene: "); CM(SCENE); if(shotPress) CM(" Shot"); if(longPress) CM(" Long"); if(doublePress) CM(" Double"); CMn();
#if defined RelayEnable && defined ButtonEnable && defined CommandToRelay && not defined MasterSceneKitchen && not defined kitchenVent_Enable && not defined GlobalHouseSwitch && not defined MasterSceneCorridor && not defined MasterBathRoom// Управление реле от кнопок
boolean flag = 0;
if (SCENE > sizeof(RELAY_Pin_)) for_i(0, sizeof(RELAY_Pin_)) RELAY_Value_[i] = 0;
else if (doublePress) { // double
if (Button.mumOfPINs == 1 && sizeof(RELAY_Pin_) == 1) RELAY_Value_[0] = 1; 
else if (Button.mumOfPINs == 1) RELAY_Value_[1] = 1; 
else if (Button.mumOfPINs > 1 && sizeof(RELAY_Pin_) == 1 && SCENE != 1) RELAY_Value_[0] = 1;
else RELAY_Value_[SCENE-1] = !RELAY_Value_[SCENE-1];
} else if (longPress) {for_i(0, sizeof(RELAY_Pin_)) RELAY_Value_[i] = 1; // long
} else { // shot
if (Button.mumOfPINs == 1) {
for_i(0, sizeof(RELAY_Pin_)) if(RELAY_Value_[i]) flag = 1; if(!flag) RELAY_Value_[0] = 1; else for_i(0, sizeof(RELAY_Pin_)) RELAY_Value_[i] = 0;
} else {if (!RELAY_Value_[SCENE-1]) RELAY_Value_[SCENE-1] = 1;} // but > 1
}
#if defined BadRoomRGBRule_Enable
if (RELAY_Value_[0] && SCENE == 1) RELAY_Value_[1] = 0; // для спальни откл светодиоды, если вкл белый свет
else if (RELAY_Value_[1] && SCENE == 2) RELAY_Value_[0] = 0; // для спальни откл белый свет, если вкл светодиоды
#endif
for_i(0,sizeof(RELAY_Pin_)) if (RELAY_Value_Save_[i] != RELAY_Value_[i]) {CM("Переключаем реле "); CM(i); CM(" в "); CMn(RELAY_Value_[i]);}
#endif

#if defined MasterBathRoom // Сцены управления в ванной
switch (SCENE) {
case 1: if (shotPress) {if(RELAY_Value_[0] && RELAY_Value_[1] && RELAY_Value_[3]) {
RELAY_Value_[0]=0; RELAY_Value_[1]=0; RELAY_Value_[3]=0; if(save.standByQuickTime) {brightMode=1; standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} else {
for_i(0,4) RELAY_Value_[i]=1; brightMode=0; mRGB.SetBrightMode(0);}}
if (!doublePress && longPress) {if(RELAY_Value_[1] && (RELAY_Value_[0] || RELAY_Value_[3])) {RELAY_Value_[0]=0; RELAY_Value_[3]=0;} else RELAY_Value_[1]=!RELAY_Value_[1]; brightMode=0; mRGB.SetBrightMode(0);}
if (doublePress) {RELAY_Value_[0]=!RELAY_Value_[0];} break;
case 2: if (shotPress) {RELAY_Value_[0]=0; RELAY_Value_[1]=0; RELAY_Value_[3]=0; if(save.standByQuickTime) {brightMode=1; standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (!doublePress && longPress) {RELAY_Value_[4]=!RELAY_Value_[4];}
if (doublePress) {RELAY_Value_[3]=!RELAY_Value_[3];} break;
case 3: if (shotPress) {RELAY_Value_[3]=!RELAY_Value_[3];}
if (!doublePress && longPress) {RELAY_Value_[3]=!RELAY_Value_[3];}
if (doublePress) {CMn("Не назначено");} break;
case 16: {RELAY_Value_[2]=!RELAY_Value_[2];} break;
case 17: {RELAY_Value_[2]=!RELAY_Value_[2];} break;
}
brightMode=0;
#endif

#if defined MasterSceneLivingRoom // Сцены управления в спальне/зале
switch (SCENE) { // 0,1 спальня, 2,3 зал
case 1: if (shotPress) {if(!RELAY_Value_Save_[0] && !RELAY_Value_Save_[1]) RELAY_Value_[0]=1; else {RELAY_Value_[0]=0; RELAY_Value_[1]=0;}}
if (!doublePress && longPress) {RELAY_Value_[0]=1; RELAY_Value_[1]=1;}
if (doublePress) {if(!RELAY_Value_Save_[1]) RELAY_Value_[1]=1; else {RELAY_Value_[0]=0; RELAY_Value_[1]=0;}} break;
case 2: if (shotPress) {if(!RELAY_Value_Save_[2] && !RELAY_Value_Save_[3]) RELAY_Value_[2]=1; else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;}}
if (!doublePress && longPress) {RELAY_Value_[2]=1; RELAY_Value_[3]=1;}
if (doublePress) {if(!RELAY_Value_Save_[3]) RELAY_Value_[3]=1; else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;}} break;
case 3: if (!doublePress) {if(!RELAY_Value_Save_[0] || !RELAY_Value_Save_[1])
{RELAY_Value_Save_[0]=1; RELAY_Value_Save_[1]=1;} else {RELAY_Value_Save_[0]=0; RELAY_Value_Save_[1]=0;}}
if (doublePress) {if(!RELAY_Value_Save_[2] || !RELAY_Value_Save_[3])
{RELAY_Value_[2]=1; RELAY_Value_[3]=1;} else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;}} break;
case 11: if (shotPress || doublePress) {if(!RELAY_Value_Save_[2]) RELAY_Value_[2]=1; else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;}}
if (!doublePress && longPress) {RELAY_Value_[2]=1; RELAY_Value_[3]=1;} break;
case 12: if (shotPress || doublePress) {if(!RELAY_Value_Save_[3]) RELAY_Value_[3]=1; else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;}}
if (!doublePress && longPress) {RELAY_Value_[2]=1; RELAY_Value_[3]=1;} break;
case 13: if(!RELAY_Value_Save_[2] && !RELAY_Value_Save_[3])
{RELAY_Value_[2]=1; RELAY_Value_[3]=1;} else {RELAY_Value_[2]=0; RELAY_Value_[3]=0;} break;
case 16: if(!longPress) Comm.command("BedRoomRGBWindow","Relay0","1"); else Comm.command("LivingRoomRGBWindow","Relay0","1"); break;
case 17: if(!longPress) Comm.command("BedRoomRGBWindow","Relay0","0"); else Comm.command("LivingRoomRGBWindow","Relay0","0"); break;
case 26: Comm.command("LivingRoomRGBWindow","Relay0","1"); break;
case 27: Comm.command("LivingRoomRGBWindow","Relay0","0"); break;
}
#endif

#if defined MasterSceneKitchen // Сцены управления светом на кухне
switch (SCENE) { // Управление реле от кнопок на кухне 
case 1: if (shotPress) {RELAY_Value_Save_[1]=0; RELAY_Value_Save_[2]=0; RELAY_Value_Save_[3]=0; for_i(1,4) RELAY_Value_[i]=1; RELAY_Value_[0]=0;}
if (!doublePress && longPress) {RELAY_Value_[0]=0; RELAY_Value_Save_[1]=0; RELAY_Value_[1]=1; RELAY_Value_Save_[2]=1; RELAY_Value_[2]=0; RELAY_Value_Save_[3]=0; RELAY_Value_[3]=1;}
if (doublePress && !longPress) RELAY_Value_[3]=!RELAY_Value_[3];
if (doublePress && longPress) RELAY_Value_[1]=!RELAY_Value_[1]; break;
case 2: if (shotPress) {RELAY_Value_[0]=2; RELAY_Value_[2]=0;
WorkZoneLight=0; if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (!doublePress && longPress) {if(!RELAY_Value_Save_[4] && !RELAY_Value_[4]) {RELAY_Value_[4]=1; RELAY_Value_[2]=1;} else RELAY_Value_[4]=!RELAY_Value_[4];}
if (doublePress && !longPress) RELAY_Value_[2]=!RELAY_Value_[2];
if (doublePress && longPress) {for_i(0,5) RELAY_Value_[i]=0; if(standBy) {standBy=0;} if(standByShot) standByShot=0;
if(standByQuick) {standByQuick=0;} goto SwitchGo;} break;
case 3: if (shotPress) RELAY_Value_[0]=!RELAY_Value_[0];
if (!doublePress && longPress) if(RELAY_Value_[2] || RELAY_Value_[4]) {RELAY_Value_[2]=0; RELAY_Value_[4]=0;} else {RELAY_Value_[2]=1; RELAY_Value_[4]=1;}
if (doublePress && !longPress) {save.MotionWashEnable=0; MQTTStatus("Wash Motion Detect",save.MotionWashEnable);}
if (doublePress && longPress) {save.MotionWashEnable=1; MQTTStatus("Wash Motion Detect",save.MotionWashEnable);} break;
case 16: for_i(0,4) RELAY_Value_[i]=1; break;
case 17: if (!longPress) {RELAY_Value_[0]=0; RELAY_Value_Save_[1]=0; RELAY_Value_[1]=1; RELAY_Value_[2]=0; RELAY_Value_[3]=0;}
else {for_i(0,3) RELAY_Value_[i]=0; RELAY_Value_[3]=1;} break;
case 19: if (!longPress) {save.autoMode=1; MQTTStatus("AutoMode",save.autoMode); CMn("Auto Mode On"); return;}
else {save.MotionDetectEnable=1; if(save.MotionDetectEnable) MQTTStatus("Motion Detect","save.MotionDetectEnable"); CMn("Motion Detect On"); return;} break;
case 27: if (!longPress) {save.autoMode=0; MQTTStatus("AutoMode",save.autoMode); CMn("Auto Mode Off"); standBy=0; standByShot=0; return;}
else {save.MotionDetectEnable=0; if(save.MotionDetectEnable) MQTTStatus("Motion Detect","save.MotionDetectEnable"); CMn("Motion Detect Off"); standByShot=0;return;} break;}
#endif

#if defined MasterSceneCorridor
switch (SCENE) { // Управление реле от кнопки на входе коридор
case 1: if (shotPress) RELAY_Value_[0]=1;
if (!doublePress && longPress) RELAY_Value_[0]=2;
if (doublePress && !longPress) RELAY_Value_[0]=1;
if (doublePress && longPress) RELAY_Value_[0]=1; break;
case 2: if (shotPress) {RELAY_Value_[0]=0; if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (!doublePress && longPress) {RELAY_Value_[0]=0; if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (doublePress && !longPress) {RELAY_Value_[0]=0; if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (doublePress && longPress) {RELAY_Value_[0]=0; if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
break;
case 3: if (shotPress) {RELAY_Value_[0]=1; RELAY_Value_[1]=1;}
if (!doublePress && longPress) {if(save.standByQuickTime) {standByTimeStart=millis(); standByQuick=1;} goto SwitchGo;} // StandByQuick
if (doublePress && !longPress) {}
if (doublePress && longPress) {} break;
case 16: RELAY_Value_[1]=1; break;
case 17: RELAY_Value_[1]=0; break;
}
#endif

#if defined GlobalHouseSwitch && defined MQTT_SendEnable
switch (SCENE) {
case 1: if (shotPress) AnybodyatHome(1); break;
case 2: if (shotPress) AnybodyatHome(1);
if (!doublePress && longPress) AnybodyatHome(0); break;}
#endif

if(SCENE==220) {// команда переключения реле из MQTT
#if defined Vibro_Enable
CM("SCENE 220 Relay0 = "); CM(RELAY_Value_[0]); CM(" RELAY0 Save = "); CMn(RELAY_Value_Save_[0]);
if(RELAY_Value_[0]) {
Vibro.VibroTimer+=save.vibroTimePlus * 60 * 1000; if (Vibro.VibroTimer > 8 * 60 * 60 * 1000) Vibro.VibroTimer = 8 * 60 * 60 * 1000;
CM("Увеличиваем таймер на "); CM(save.vibroTimePlus); CMn(" мин");} else if(RELAY_Value_Save_[0]) {CMn("Отключаем таймер"); RELAY_Value_[0] = 0; MQTTStatus("Relay0",RELAY_Value_[0]); saveRelay=1; 
Vibro.vibroCountSave=0; Vibro.VibroTimer=0;}
#endif
}

#if defined IRSens_Enable && (defined MasterSceneKitchen || defined kitchenVent_Enable)
switch (SCENE) {
case 30: // Управление реле от движения на кухне 
if (doublePress) { // double
{if (RELAY_Value_[2] || RELAY_Value_[4]) {RELAY_Value_[2] = 0; RELAY_Value_[4] = 0;} else {RELAY_Value_[2] = 1; RELAY_Value_[4] = 1;}}}
else if (longPress) {RELAY_Value_[4]=!RELAY_Value_[4];} // long
else if(shotPress) {RELAY_Value_[2] = !RELAY_Value_[2];} // shot
if (!RELAY_Value_Save_[4] && RELAY_Value_[4]) RELAY_Value_[2] = 1;  break;
case 31: // Управление реле от ИК сенсора для вентилятора на кухне
if (shotPress) RELAY_Value_[2]=!RELAY_Value_[2];
if (!doublePress && longPress) {if(!RELAY_Value_Save_[4] && !RELAY_Value_[4]) {RELAY_Value_[4]=1; RELAY_Value_[2]=1;} else RELAY_Value_[4]=!RELAY_Value_[4];}
if (doublePress && !longPress) if(RELAY_Value_[2] || RELAY_Value_[4]) {RELAY_Value_[2]=0; RELAY_Value_[4]=0;} else {RELAY_Value_[2]=1; RELAY_Value_[4]=1;} break;}
#endif

#if defined EEPROM_Enable && defined MQTT_SendEnable
#if defined GlobalHouseSwitch
if(!save.MASTER_ESP) for_t(0,30) if(strcmp("",save.controlTopic[t])) ctrl=1;
#else
if(!save.MASTER_ESP) for_t(0,10) if(strcmp("",save.controlTopic[t])) ctrl=1;
#endif
#endif
if(!ctrl) {if(save.autoMode) {standByTimeStart=millis(); if(!standBy && save.standByTime) {CMn("Сцена вкл standBy"); standBy=1; standByQuick=0;
standByShot=0;}} else {standByQuick=0;}}
brightMode=0;
SwitchGo:
#if defined MasterBathRoom
if (!RELAY_Value_Save_[1] && RELAY_Value_[1]) mRGB.powerON(0);
else if (RELAY_Value_Save_[1] && !RELAY_Value_[1]) mRGB.powerOFF(0);
if (!RELAY_Value_Save_[2] && RELAY_Value_[2]) mRGB.powerON(1);
else if (RELAY_Value_Save_[2] && !RELAY_Value_[2]) mRGB.powerOFF(1);
#endif
#if defined RelayEnable
for_i(0,sizeof(RELAY_Pin_)) if (RELAY_Value_Save_[i] != RELAY_Value_[i]) {CM("Сцена реле "); CM(i); CM(" в "); CMn(RELAY_Value_[i]);} saveRelay=1;
#endif
SCENE=0; shotPress=0; longPress=0; doublePress=0;}

#if defined RelayEnable
void SaveRelay() {returnMS(500); if(!saveRelay) return;
#if defined MQTT_SendEnable
if(MQTTOk) {for_i(0,5) {if (RELAY_Value_Save_[i] != RELAY_Value_[i]) MQTTStatus4("Relay",i,RELAY_Value_[i],"Relay");
if(save.CommandToTopic0 && RELAY_Value_Save_[i]!=RELAY_Value_[i]) {MQTTStatus4("Relay",i,RELAY_Value_[i],save.controlTopic[0]);}}}
#endif
for_i(0,5) {if (RELAY_Value_Save_[i] != RELAY_Value_[i]) {RELAY_Value_Save_[i] = RELAY_Value_[i];
CM("Сохраняем состояние Relay"); CM(i); CM(" = "); CMn(RELAY_Value_[i]); if(RELAY_Pin_[i]!=99) 
#if defined MasterBathRoom
if (i==3) writeRelay(RELAY_Pin_[i],!RELAY_Value_[i]); else writeRelay(RELAY_Pin_[i],RELAY_Value_[i]); // на зеркало в ванне ключ на 12В, не инвертируем как для реле
#else
writeRelay(RELAY_Pin_[i],RELAY_Value_[i]);
#endif
}} saveRelay=0;}
#endif

#if defined MQTT_SendEnable
void SendStatus(uint8_t sendSt) {
static boolean syncOk; if(!sendSt && !MQTTOk) {if(syncOk) syncOk=0; return;}
if(!sendSt && !syncOk) {returnSec(1);} char value[7], stat[50], topic[50]; static boolean firstSend, firstSendRelay;
if(!sendSt && syncOk) return;
if(sendSt) MQTTStatus("IP",Comm.IPadress);
if(sendSt==1 || !firstSend) {//CMn("Отправляем весь статус");
MQTTStatus("WiFi SSID",WiFi.SSID().c_str());
for_t(0,5) if(strcmp(save.WIFI_SSID[t],"")) {if(strcmp(save.WIFI_SSID[t],"")) strcpy(ReceiveValue,save.WIFI_SSID[t]); else strcpy(ReceiveValue,"Not assigned"); strcat(ReceiveValue," , password ");
if(strcmp(save.WIFI_PASSWORD[t],"")) {char pass[15] = {""}; for_i(0,2) pass[i]=save.WIFI_PASSWORD[t][i]; strcat(pass,"**** - ****");
uint16_t p=2; while(p<40 && save.WIFI_PASSWORD[t][p+2]!='\0') p++; for_i(13,15) {pass[i]=save.WIFI_PASSWORD[t][p]; p++;} pass[15]='\0';
strcat(ReceiveValue,pass);} else strcat(ReceiveValue," not assigned");
MQTTStatus4("WiFi SSID ",t,ReceiveValue,"plus");} else break;
MQTTStatus("Firmware version",FirmwareVersion);
if(OTApossible) MQTTStatus("ESP Module OTA","Available"); else MQTTStatus("ESP Module OTA","Not possible");
#if defined EEPROM_Enable
MQTTStatus("Save Data in EEPROM","Yes");
#else
MQTTStatus("Save Data in EEPROM","No");
#endif

#if not defined GlobalHouseSwitch
const uint8_t numsOfTopic=10;
#else
const uint8_t numsOfTopic=30;
#endif
boolean topicPresent=0;
for_t(0,numsOfTopic) if(strcmp(save.controlTopic[t],"")) {topicPresent=1; strcpy(topic,save.controlTopic[t]);
if(Comm.SyncTopic[t]==1) strcat(topic," - syncronized"); else strcat(topic," - not syncronized"); MQTTStatus4("Controlled topic",t,topic,"plus");}
if(!topicPresent) {MQTTStatus("Controlled topic","No monitored topics");} // Нет контролируемых топиков
else {MQTTStatus("Controlled topic","Control topics"); if(Comm.masterSyncOk)
{if (Comm.MASTER_ESP) MQTTStatus("ESP Module MASTER","Synchronization complete"); else MQTTStatus("ESP Module SLAVE","Synchronization complete");} else
{if (Comm.MASTER_ESP) MQTTStatus("ESP Module MASTER","Wait Synchronization"); else MQTTStatus("ESP Module SLAVE","Wait Synchronization");}}

#if defined GlobalHouseSwitch || defined MasterBedRoom
topicPresent=0;
for_t(0,10) if(strcmp(save.LEDTopic[t],"")) {topicPresent=1; MQTTStatus4("LED topic",t,save.LEDTopic[t],"plus");}
if(!topicPresent) {MQTTStatus("LED topics","Not control");} // Нет включаемых LED топиков
else MQTTStatus("LED topics","Control LED topics");

Comm.status("LED control",ReceiveValue);
#endif

#if defined EEPROM_Enable && defined ESP_EEPROM_Enable
if (save.MASTER_ESP) MQTTStatus("ESP module","MASTER"); else MQTTStatus("ESP module","SLAVE");
#endif

#if defined EEPROM_Enable
MQTTStatus("AutoMode",save.autoMode);
#endif

#if defined EEPROM_Enable && defined ESP_EEPROM_Enable
MQTTStatus3("StandByTime",save.standByTime,"sec");
MQTTStatus3("StandByShotTime",save.standByShotTime,"sec");
MQTTStatus3("StandByQuickTime",save.standByQuickTime,"sec");
#endif

#if defined ButtonEnable
char value[50], stat[50], topic[50]; itoa(Button.btn[0], value,10); strcpy(stat, value); for_i(1, Button.mumOfPINs) {strcat(stat,", "); itoa(Button.btn[i], value,10); strcat(stat, value);}
strcpy(topic,"Button PIN"); if(Button.mumOfPINs > 1) strcat(topic,"s"); MQTTStatus(topic, stat); MQTTStatus("Button delay",Button.Btnkf);
#endif

#if defined ledIndikator_Enable
MQTTStatus("LED Blue PIN",Led.blueLED);
if(Led.redLED!=99) MQTTStatus("LED Red PIN",Led.redLED);
#endif

#if defined RelayEnable // Отправить в MQTT пины реле
strcpy(topic,"Relay PIN"); if(sizeof(RELAY_Pin_)>1) strcat(topic,"s"); strcpy(stat,"");
for_i(0, sizeof(RELAY_Pin_)) {if (i) strcat(stat,", "); if(RELAY_Pin_[i]!=nPIN && RELAY_Pin_[i]!=RGBPIN && RELAY_Pin_[i]!=CWPIN &&
RELAY_Pin_[i]!=RGBPIN0 && RELAY_Pin_[i]!=RGBPIN1 && RELAY_Pin_[i]!=RGBPIN2 && RELAY_Pin_[i]!=RGBPIN3 && RELAY_Pin_[i]!=RGBPIN4) {
itoa(RELAY_Pin_[i], value,10); strcat(stat, value);}
if(RELAY_Pin_[i]==nPIN) strcat(stat,"No"); if(RELAY_Pin_[i]==RGBPIN) {strcat(stat,"RGB Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==RGBPIN0) {strcat(stat,"RGB0 Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==RGBPIN1) {strcat(stat,"RGB1 Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==RGBPIN2) {strcat(stat,"RGB2 Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==RGBPIN3) {strcat(stat,"RGB3 Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==RGBPIN4) {strcat(stat,"RGB4 Relay"); itoa(i, value,10); strcat(stat,value);}
if(RELAY_Pin_[i]==CWPIN) {strcat(stat,"Cold Warm Relay"); itoa(i, value,10); strcat(stat,value);}} MQTTStatus(topic,stat);
#endif

#if defined IRSens_Enable
MQTTStatus("IRSensor PIN",IRSens.IrSens_PIN);
#endif

#if defined kitchenVent_Enable || defined MasterBathRoom // Отправить в MQTT время автоотключения
MQTTStatus3("Vent Auto Off Time",save.ventAutoTime,"sec");
#endif

#if defined MotionSens_Enable
MQTTStatus("Motion Sensor PIN",Move.MotionSens_PIN);
MQTTStatus("Motion Detect",save.MotionDetectEnable);
MQTTStatus3("MotionOn Memory",save.MotionOnMemory,"sec");
MQTTStatus3("Motion Ignore",save.MotionIgnore,"sec");
if (save.MASTER_ESP) MQTTStatus("Motion",Motion);
#else
#if defined EEPROM_Enable
if (save.MASTER_ESP) {
if(save.MotionDetectEnable) MQTTStatus("Motion Detect",save.MotionDetectEnable);
MQTTStatus3("MotionOn Memory",save.MotionOnMemory,"sec");
MQTTStatus3("Motion Ignore",save.MotionIgnore,"sec");}
#endif
#endif
#if defined MotionSens_Enable && defined PresenceSens_Enable
MQTTStatus("Presence Sensor PIN",Presen.PresenceSens_PIN);
MQTTStatus("Presence Detect",save.PresenceDetectEnable);
MQTTStatus3("PresenceOn Memory",save.PresenceOnMemory,"sec");
MQTTStatus3("Presence Ignore",save.PresenceIgnore,"sec");
#endif
#if defined MasterSceneKitchen
if(save.MotionWashEnable) Comm.status("Wash Motion Detect",save.MotionDetectEnable);
MQTTStatus3("Wash light",save.MotionWashTime," sec");
#endif

#if defined MotionSens_Enable
MQTTStatus("MotionSensor",MotionSensor); //MotionSensor
#endif

#if defined Vibro_Enable
MQTTStatus("Vibro Sensor PIN",Vibro.VibroSens_PIN);
MQTTStatus("Vibro Detect",save.VibroDetectEnable);
MQTTStatus("VibroSensor",Vibro.VibroSensor);
MQTTStatus("VibroValue",0);
MQTTStatus("VibroTimer",Vibro.VibroTimer);
MQTTStatus("Vibro Level",save.vibroLevel);
MQTTStatus3("Vibro Warn Time",save.vibroWarnTime,"sec");
MQTTStatus3("Vibro Time Plus",save.vibroTimePlus,"min");
MQTTStatus3("Vibro Event Count",save.vibroCount,"num");
MQTTStatus3("Vibro time count Reset",save.vibroCountReset,"sec");
MQTTStatus3("Vibro ignore time after Event",save.timeIgnoreVibroEvent,"sec");
MQTTStatus3("Time step",save.timeStep,"Msec");
MQTTStatus3("Time between steps",save.timeWait,"Msec");
MQTTStatus("Minimum steps",save.minSteps);
MQTTStatus("Maximum steps",save.maxSteps);
MQTTStatus3("MinTime next steps",save.minNext,"sec");
MQTTStatus3("MaxTime next steps",save.maxNext,"sec");
#endif

#if defined VL6180X_Enable || defined BH1750_Enable || defined BME280_Enable || defined MAX44009_Enabled || defined AM2320_Enabled
strcpy(stat,"SDA - "); itoa(SDA, value,10); strcat(stat, value); strcat(stat,", SCL - ");
itoa(SCL, value,10); strcat(stat, value); MQTTStatus("Sensor PINs",stat);
#endif

#if defined S8_CO2_Enable
strcpy(stat, "Uart_Rx - "); itoa(Uart_Rx, value,10); strcat(stat, value); strcat(stat,", Uart_Tx - ");
itoa(Uart_Tx, value,10); strcat(stat, value); MQTTStatus("CO2 Sensor PINs",stat);
#endif

#if defined PZEM004T_Enable
strcpy(stat, "Uart_Rx - "); itoa(Uart_Rx, value,10); strcat(stat, value); strcat(stat,", Uart_Tx - ");
itoa(Uart_Tx, value,10); strcat(stat, value); MQTTStatus("PZEM004T Sensor PINs",stat);
#endif

#if defined HX711_Enable
strcpy(stat, "DT - "); itoa(LOADCELL_DOUT_PIN, value,10); strcat(stat, value); strcat(stat,", SCK - ");
itoa(LOADCELL_SCK_PIN, value,10); strcat(stat, value); MQTTStatus("HX711 Sensor PINs",stat);
MQTTStatus("Weight",weight); // Вес
#endif

#if defined AM2301A_Enabled
MQTTStatus("AM2301A sensor PIN",DHTPIN);
#endif

#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
save.DecimalTemp ? MQTTStatus("Temperature decimal point >10<","Yes") : MQTTStatus("Temperature decimal point >10<","No");
Comm.status("Threshold temperature",save.thresholdTemp,"°C");
Comm.status("Threshold humidity",save.thresholdHUM,"%");
Comm.status("Hysteresis temperature",save.hysteresisTemp,"°C");
Comm.status("Hysteresis humidity",save.hysteresisHUM,"%");
#endif

#if defined RGB_MODULE_LED_Enable
strcpy(stat, "Data PIN - "); itoa(DATA_PIN, value,10); strcat(stat, value); strcat(stat,", Clock PIN - ");
itoa(CLOCK_PIN, value,10); strcat(stat, value); MQTTStatus("RGB Data Clock PINs",stat);
for_t(0,NUM_LEDS) {
MQTTStatus4("Color module",t,save.SaveModRGB[t].hexColor,"Module");
MQTTStatus4("Favorite color module",t,save.SaveModRGB[t].favoriteColor,"Module");
MQTTStatus4("Bright color module",t,save.SaveModRGB[t].brightColor,"Module");
if (save.StartMode[t] == 0) MQTTStatus4("StartMode module",t,"Restore state","Module"); else if (save.StartMode[t] == 1) MQTTStatus4("StartMode module",t,"Turn OFF","Module");
else if (save.StartMode[t] == 2) MQTTStatus4("StartMode module",t,"Favorite Color","Module");}
MQTTStatus("BrightMode",brightMode);
save.GammaCorrection ? MQTTStatus("Gamma Correction","ON") : MQTTStatus("Gamma Correction","OFF");
MQTTStatus3("Fade delay",save.FadeDelay,"ms");
#endif

#if defined RGB_LED_Enable
strcpy(stat, "Red - "); itoa(RGB.Red_PIN, value,10); strcat(stat, value); strcat(stat, ", Green - "); itoa(RGB.Green_PIN, value,10); strcat(stat, value); strcat(stat, ", Blue - ");
itoa(RGB.Blue_PIN, value,10); strcat(stat, value); MQTTStatus("LED RGB PINs",stat);
MQTTStatus("Color",save.hexColor);
MQTTStatus("Favorite Color",save.favoriteColor);
MQTTStatus("Bright Color",save.brightColor);
MQTTStatus("BrightMode",brightMode);
save.GammaCorrection ? MQTTStatus("Gamma Correction","ON") : MQTTStatus("Gamma Correction","OFF");
if (save.StartMode == 0) MQTTStatus("StartMode","Restore state"); else if (save.StartMode == 1) MQTTStatus("StartMode","Turn OFF");
else if (save.StartMode == 2) MQTTStatus("StartMode","Favorite Color");
MQTTStatus3("Fade delay",save.FadeDelay,"ms");
#endif

#if defined Cold_Warm_LED_Enable
strcpy(stat, "Cold - "); itoa(CWLED.Led_Pin_[0], value,10); strcat(stat, value); strcat(stat, ", Warm - "); itoa(CWLED.Led_Pin_[1], value,10); strcat(stat, value);
MQTTStatus("Cold Warm PINs",stat);
MQTTStatus("ColdWarm",save.ColdWarm);
MQTTStatus3("Normal Light value",save.currentLight,"%");
MQTTStatus3("Night Light value",save.nightLight,"%");
MQTTStatus3("Fade Delay",save.fadeDelay,"ms");
#endif
firstSend=1;}

#if defined EEPROM_Enable && defined ESP_EEPROM_Enable
if(!Comm.masterSyncOk) {CMn("Ждем синхро"); return;} syncOk=1;
if (save.MASTER_ESP) {                    // MASTER ESP
#if defined RelayEnable                   // Отправить в MQTT статус реле
for_i(0,sizeof(RELAY_Pin_)) Comm.status("Relay",i,RELAY_Value_[i],"Plus");
#endif
MQTTStatus("StandBy",standBy);            //StandBy
MQTTStatus("StandByShot",standByShot);    //StandByShot
MQTTStatus("StandByQuick",standByQuick);  //StandByQuick
MQTTStatus("Motion",Motion);              //Motion
MQTTStatus("BrightMode",brightMode);      //BrightMode
syncOk=1;} else if (sendSt) {             // SLAVE ESP
#if defined RelayEnable
for_i(0,sizeof(RELAY_Pin_)) if(RELAY_Pin_[i]!=nPIN) Comm.status("Relay",i,RELAY_Value_[i],"Plus"); // Slave статус реле после синхронзации при запросе
#endif
}
#endif
firstSendRelay=1;
}

boolean resiveCommand(const char* Command) {char tempTop[50]; strcpy(tempTop,ESPName); strcat(tempTop,"/Command/"); strcat(tempTop,Command); if (!strcmp(ReciveTopic,tempTop)) return 1; return 0;}
boolean resiveCommand(int Num, const char* Command) {char tempTop[50], tempNum[7]; strcpy(tempTop,ESPName); itoa(Num,tempNum,10); strcat(tempTop,tempNum); strcat(tempTop,"/Command/"); strcat(tempTop,Command); if (!strcmp(ReciveTopic,tempTop)) return 1; return 0;}

void MQTTread(char* intopic, byte* payload, unsigned int length) {char topic[50], value[50]; char compareStr[50];
#if defined GlobalHouseSwitch
uint8_t ctrlNumTopic=30;
#else
uint8_t ctrlNumTopic=10;
#endif
strcpy(ReciveTopic, intopic);
#if defined GlobalHouseSwitch
if (strstr(ReciveTopic,"corridorButton0/Status")!=NULL) return; // отсеиваем свои статусы
#endif
for_i(0, length) ReceiveValue[i] = (char)payload[i]; ReceiveValue[length] = '\0';

static char oldPayload[50], oldTopic[50]; static uint32_t time;
if (!strcmp(oldPayload,ReceiveValue) && !strcmp(ReciveTopic,oldTopic) && millis()-time < 1000) {CM("<- Повтор "); CM(ReciveTopic); CM(": "); CMn(ReceiveValue); time=millis(); return;} // отсеиваем
strcpy(oldPayload,ReceiveValue); strcpy(oldTopic,ReciveTopic); time=millis();

#if defined GlobalHouseSwitch
boolean topicNotPresent=1; uint8_t topicEmpty=0;
char ReciveTopicName[50]; strcpy(ReciveTopicName,ReciveTopic); char *strtokIndx;
//char ResiveTopicAct[40], 
strtokIndx = strtok(ReciveTopicName, "/"); // if (strtokIndx != NULL) strcpy(ResiveTopic,strtokIndx);
strtokIndx = strtok(ReciveTopicName, "/"); //if (strtokIndx != NULL) strcpy(ResiveTopicAct,strtokIndx);
strtokIndx = strtok(ReciveTopicName, "/"); //if (strtokIndx != NULL) strcpy(ReciveTopicName,strtokIndx);

if (strstr(ReciveTopic,"Status/Relay")!=NULL) {
for_t(0,30) {if(!strcmp(save.controlTopic[t],"")) {topicEmpty=t; break;}
if (!strcmp(save.controlTopic[t],ReciveTopicName)) topicNotPresent=0;
if (topicNotPresent && t>28) {CMn("База топиков переполнена!"); MQTTStatus("Controlled topic","Monitored topics overload!");}
} // Топик уже в базе
if(topicNotPresent) { // Relay от нового топика, добавляем в базу
SyncInd(1); CMn("Relay от нового топика");
strcpy(save.controlTopic[topicEmpty],ReciveTopicName); CM("Сохраняем новый топик: "); CM(ReciveTopicName);
CM(" в позицию "); CMn(topicEmpty); saveChange(1);}
}
#endif

CM("<-из- MQTT: "); CM(ReciveTopic); CM(": "); CMn(ReceiveValue);

#if defined MasterBedRoom
static boolean LED_State;                   // 0 - сохраняем состояние LED
static boolean bedRoomAutomode_State;       // Состояние AutoMode спальни до выкл LED
if (save.LEDControl && Comm.LEDSyncOk && strstr(ReciveTopic,"Status/Relay1")!=NULL) { // если есть слово Status/Relay1 - управление LED подсветкой квартиры
strcpy(compareStr,save.controlTopic[0]); strcat(compareStr,"/Status/Relay1");
if(!strcmp(ReciveTopic,compareStr)) {if(atoi(ReceiveValue)) {LED_State=0;
CMn("Включаем LED подсветку"); CM("Восстанавливаем AutoMode = "); CMn(bedRoomAutomode_State);
if(bedRoomAutomode_State && bedRoomAutomode_State!=save.autoMode) {save.autoMode=1; MQTTStatus("AutoMode",save.autoMode);}
for_t(0,10) {if(strcmp(save.LEDTopic[t],"")) {for_i(0,5) {if(RELAY_State_[t][i]) Comm.command("Relay",i,1,save.LEDTopic[t]);}}}
} else {if(!LED_State) bedRoomAutomode_State=save.autoMode; CM("Сохраняем AutoMode = "); CMn(bedRoomAutomode_State);
 LED_State=1; CMn("Выключаем LED подсветку"); if(bedRoomAutomode_State) {save.autoMode=0; MQTTStatus("AutoMode",save.autoMode);}
for_t(0,10) {if(strcmp(save.LEDTopic[t],"")) {for_i(0,5) {if(RELAY_State_[t][i]) Comm.command("Relay",i,0,save.LEDTopic[t]);}}}}}}

if (!LED_State && strstr(ReciveTopic,"Status/Relay")!=NULL) { // если слово Status/Relay - запоминаем состояние (0 топик пропускаем)
for_t(0,10) {for_i(0,5) {strcpy(compareStr,save.LEDTopic[t]); strcat(compareStr,"/Status/Relay");
itoa(i, value,10); strcat(compareStr, value);
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); RELAY_State_[t][i]=atoi(ReceiveValue);
CM("Сохраняем топик: "); CM(save.LEDTopic[t]); CM(" состояние реле "); CM(i); CM(" = "); CMn(RELAY_State_[t][i]);
return;}}}}
#endif

#if defined GlobalHouseSwitch

if (!AnybodyHome && strstr(ReciveTopic,"Status/SCENE")!=NULL) { // если есть слово Status/SCENE - управление от кнопок
SyncInd(1); standBy=0; AnybodyatHome(1); Comm.status("AnybodyHome","1"); CMn("Кто-то дома");}

if (!AnybodyHome && strstr(ReciveTopic,"Status/Motion")!=NULL && atoi(ReceiveValue)) { // если есть слово Status/MotionSensor - где-то есть движ
SyncInd(1); standBy=0; AnybodyatHome(1); Comm.status("AnybodyHome","1"); CMn("Кто-то дома");}

if (AnybodyHome && strstr(ReciveTopic,"Status/Relay")!=NULL) { // если слово Status/Relay - запоминаем состояние (0 топик пропускаем)
for_t(0,10) {for_i(0,5) {strcpy(compareStr,save.LEDTopic[t]); strcat(compareStr,"/Status/Relay");
itoa(i, value,10); strcat(compareStr, value);
if(AnybodyHome && !strcmp(ReciveTopic,compareStr)) {SyncInd(1); RELAY_State_[t][i]=atoi(ReceiveValue);
CM("Сохраняем топик: "); CM(save.LEDTopic[t]); CM(" состояние реле "); CM(i); CM(" = "); CMn(RELAY_State_[t][i]);
return;}}}}
#endif

if (strstr(ReciveTopic,"Status/IP")!=NULL) { // если есть слово Status/IP флаг подтверждения синхронизации
#if not defined GlobalHouseSwitch
const uint8_t numsOfTopic=10;
#else
const uint8_t numsOfTopic=30;
#endif
for_t(0,numsOfTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/IP");
if(!strcmp(ReciveTopic,compareStr)) {if (!Comm.SyncTopic[t]) {SyncInd(1); Comm.SyncTopic[t]=1; CM("Синхронизация для ");
CM(save.controlTopic[t]); CMn(" подтверждена");
Comm.SyncTopic[t]=1; strcpy(topic,save.controlTopic[t]); strcat(topic," - syncronized"); Comm.status("Controlled topic",t,topic,"plus"); return;}}}
#if defined GlobalHouseSwitch || defined MasterBedRoom
for_t(0,10) {strcpy(compareStr,save.LEDTopic[t]); strcat(compareStr,"/Status/IP");
if(!strcmp(ReciveTopic,compareStr)) {if (!Comm.SyncLEDTopic[t]) {SyncInd(1); Comm.SyncLEDTopic[t]=1; CM("Синхронизация LED для ");
CM(save.LEDTopic[t]); CMn(" подтверждена");
Comm.SyncLEDTopic[t]=1; strcpy(topic,save.LEDTopic[t]); strcat(topic," - syncronized"); Comm.status("LED topic",t,topic,"plus"); return;}}}
#endif
}

#if defined RelayEnable && not defined GlobalHouseSwitch // контроль топика Status
if (strstr(ReciveTopic,"Status/Relay")!=NULL) { // если есть слово Status/Relay - синхронизация
for_t(0,ctrlNumTopic) {for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/Relay");
itoa(i, value,10); strcat(compareStr, value);
if(!strcmp(ReciveTopic,compareStr)) {
if(!save.MASTER_ESP && RELAY_Pin_[i]==nPIN) {CM("Пустой PIN "); CM(i); CMn(" пропускаем"); return;}
RELAY_Value_[i] = atoi(ReceiveValue); if(RELAY_Value_[i]==RELAY_Value_Save_[i]) {
CM("Реле "); CM(i); CM(" уже = "); CM(RELAY_Value_[i]); CMn(" пропускаем"); return;}
#if defined Cold_Warm_LED_Enable
if(RELAY_Pin_[i] == CWPIN) CWLED.switchLED=1;
#endif
#if defined kitchenVent_Enable
if (!RELAY_Value_Save_[4] && RELAY_Value_[4]) RELAY_Value_[2] = 1;
#endif
#if defined RGB_LED_Enable
if(millis() - RGB.BrightTimeStart < 500) return;
if(RELAY_Pin_[i] == RGBPIN) {RELAY_Value_[i] ? RGB.powerON() : RGB.powerOFF(); save.Power=RELAY_Value_[i];}
#endif
#if defined RGB_MODULE_LED_Enable
if(millis() - mRGB.BrightTimeStart < 500) return;
if(RELAY_Pin_[i] == RGBPIN0 || RELAY_Pin_[i] == RGBPIN1 || RELAY_Pin_[i] == RGBPIN2 || RELAY_Pin_[i] == RGBPIN3
 || RELAY_Pin_[i] == RGBPIN4) {RELAY_Value_[i] ? mRGB.powerON(i) : mRGB.powerOFF(i); save.Power[i]=RELAY_Value_[i];}
#endif
for_i(0,sizeof(RELAY_Pin_)) if (RELAY_Value_Save_[i] != RELAY_Value_[i]) {SyncInd(1);
CM("Синхроним реле "); CM(i); CM(" = "); CMn(RELAY_Value_[i]);} saveRelay=1; return;}}}}
#endif

#if defined RelayEnable
if (strstr(ReciveTopic,"Command/Relay")!=NULL) { // если есть команда для Relay(x), то переключаем, отсылаем статус реле
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"Relay"); itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {if(!save.MASTER_ESP && RELAY_Pin_[i]==nPIN) {CM("Пустой PIN "); CM(i); CMn(" пропускаем"); return;}
SyncInd(1); RELAY_Value_[i] = atoi(ReceiveValue);
#if defined Vibro_Enable
if(!Vibro.VibroSensor) {SCENE=220; SwitchScene();} //переключение реле
#endif
#if defined RGB_LED_Enable
if(RELAY_Pin_[i] == RGBPIN) {RELAY_Value_[i] ? RGB.powerON() : RGB.powerOFF(); save.Power=RELAY_Value_[i];}
#endif
#if defined RGB_MODULE_LED_Enable
if(RELAY_Pin_[i] == RGBPIN0) {RELAY_Value_[i] ? mRGB.powerON(0) : mRGB.powerOFF(0); save.Power[i]=RELAY_Value_[i];}
if(RELAY_Pin_[i] == RGBPIN1) {RELAY_Value_[i] ? mRGB.powerON(1) : mRGB.powerOFF(1); save.Power[i]=RELAY_Value_[i];}
if(RELAY_Pin_[i] == RGBPIN2) {RELAY_Value_[i] ? mRGB.powerON(2) : mRGB.powerOFF(2); save.Power[i]=RELAY_Value_[i];}
if(RELAY_Pin_[i] == RGBPIN3) {RELAY_Value_[i] ? mRGB.powerON(3) : mRGB.powerOFF(3); save.Power[i]=RELAY_Value_[i];}
if(RELAY_Pin_[i] == RGBPIN4) {RELAY_Value_[i] ? mRGB.powerON(4) : mRGB.powerOFF(4); save.Power[i]=RELAY_Value_[i];}
#endif
#if defined Cold_Warm_LED_Enable
if(RELAY_Pin_[i] == CWPIN) {if(!RELAY_Value_[i]) {standByShot=0; standByQuick=0;} if(RELAY_Value_[i]==2) CWLED.pc_2mode=1; CWLED.switchLED=1;}
#endif
CM("<-из- MQTT: ПК Реле: "); CM(i); CM(" = "); CMn(ReceiveValue); saveRelay=1; return;}}}
#endif

if (save.MASTER_ESP) {// прием сцен мастером

if (strstr(ReciveTopic,"Status/IR")!=NULL) { // если есть слово Status/IR - управление от ИК сенсора
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/IR");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); if(save.autoMode) {standByTimeStart=millis(); if(!standBy && save.standByTime) {CMn("ИК вкл standBy"); standBy=1; standByQuick=0; 
standByShot=0;}} return;}}}

if (strstr(ReciveTopic,"Status/SCENE")!=NULL) { // если есть слово Status/SCENE - управление от кнопок
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/SCENE");
if(!strcmp(ReciveTopic,compareStr)) {char *strtokIndx;
strtokIndx = strtok(ReceiveValue," "); SCENE=atoi(strtokIndx);
#if defined MasterSceneLivingRoom
if (strstr(ReciveTopic,"LivingRoomButton1")!=NULL) SCENE+=10;
#endif
while (strtokIndx != NULL) {strtokIndx = strtok(NULL," "); if(strtokIndx != NULL) {
if(!strcmp(strtokIndx,"Shot")) shotPress=1; if(!strcmp(strtokIndx,"Long")) longPress=1; if(!strcmp(strtokIndx,"Double")) doublePress=1;
if(!shotPress && !longPress && !doublePress) CM("не распознана");}} SyncInd(1); CM("Синхроним SCENE: "); CM(SCENE); if(shotPress) CM(" shot");
if(doublePress) CM(" double"); if(longPress) CM(" lond"); CMn(); SwitchScene(); return;}}}

if (strstr(ReciveTopic,"Status/MotionSensor")!=NULL) { // если есть слово Status/MotionSensor - где-то есть движ
for_t(0,29) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/MotionSensor");
if(!strcmp(ReciveTopic,compareStr)) {if(atoi(ReceiveValue)) {SyncInd(1); CMn("<-из- MQTT: Общее движение: 1");}
if (atoi(ReceiveValue) && save.autoMode) {Motion=1; Comm.status("Motion","1"); standByTimeStart=millis(); motionStart=millis();
if(save.autoMode && !standByQuick && !standBy) {if(!standByShot && save.standByShotTime) {standByShot=1; CMn("standByShot=1");}}} return;}}}}

#if not defined GlobalHouseSwitch
if (!save.MASTER_ESP) {// прием модуль SLAVE
if (strstr(ReciveTopic,"Status/StandBy")!=NULL) { // если есть слово Status/StandBy - установить StandBy режим
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/StandBy");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); standBy = atoi(ReceiveValue); 
CM("<-из- MQTT: Синхроним StandBy режим"); CM(" = "); CMn(standBy);
if(standBy) {standByShot=0; standByQuick=0; CMn("Отключаем StandByShot/StandByQuick");} return;}}}

if(!standByQuick && !standBy) {
if (strstr(ReciveTopic,"Status/StandByShot")!=NULL) { // если есть слово Status/StandByShot - установить StandByShot режим
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/StandByShot");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); standByShot = atoi(ReceiveValue); 
CM("<-из- MQTT: Синхроним StandByShot режим"); CM(" = "); CMn(standByShot); return;}}}}

if (strstr(ReciveTopic,"Status/StandByQuick")!=NULL) { // если есть слово Status/StandByQuick - установить StandByQuick режим
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/StandByQuick");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); standByQuick = atoi(ReceiveValue);
CM("<-из- MQTT: Синхроним StandByQuick режим"); CM(" = "); CMn(standByQuick);
if(standByQuick) {standBy=0; standByShot=0; CMn("Отключаем StandBy/StandByShot");} return;}}}

if (strstr(ReciveTopic,"Status/AutoMode")!=NULL) { // если есть слово Status/AutoMode - установить AutoMode режим
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/AutoMode");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); if(save.autoMode != atoi(ReceiveValue)) {if(atoi(ReceiveValue)) save.autoMode=1; else save.autoMode=0;
if(!save.autoMode) {standBy=0; standByShot=0; CMn("Отключаем StandBy режимы"); Motion=0; MotionSensor=0; MQTTStatus("Motion",0); MQTTStatus("MotionSensor",0);}
CM("<-из- MQTT: Синхроним Авто режим"); CM(" = "); CMn(save.autoMode); saveChange(1); MQTTStatus("AutoMode",save.autoMode);} return;}}}

if (!Comm.masterSyncOk) {if (strstr(ReciveTopic,"Status/SyncStatus")!=NULL) { // если есть слово Status/SyncStatus - синхронизация с MASTER подтверждена
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/SyncStatus");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); strcpy(topic,save.controlTopic[t]); 
strcat(topic," - syncronized"); Comm.status("Controlled topic",t,topic,"plus"); Comm.SyncTopic[t]=1;
Comm.status("ESP Module SLAVE","Synchronization complete"); Comm.masterSyncOk=1;} return;}}}
}
#endif

if(resiveCommand("Status")) {SyncInd(1); CMn("<-из- MQTT: Запрошен статус"); SendStatus(2); return;}

if(resiveCommand("AllStat")) {SyncInd(1); CMn("<-из- MQTT: Запрошен полный статус"); SendStatus(1); return;}

#if defined Vibro_Enable
if (resiveCommand("VibroSensor")) {SyncInd(1); save.VibroDetectEnable = atoi(ReceiveValue); Vibro.VibroDetectEnable=save.VibroDetectEnable; CM("<-из- MQTT: Реагировать на сенсор: "); 
CMn(save.VibroDetectEnable); Comm.status("Vibro Detect",save.VibroDetectEnable); saveChange(1); if(!save.VibroDetectEnable) Comm.status("VibroValue",0); return;}

if (resiveCommand("VibroLevel")) {SyncInd(1); save.vibroLevel = atoi(ReceiveValue); Vibro.vibroLevel=save.vibroLevel; CM("<-из- MQTT: Порог сработки: "); 
CMn(save.vibroLevel); Comm.status("Vibro Level",save.vibroLevel); saveChange(1); return;}

if (resiveCommand("VibroWarnTime")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.vibroWarnTime=255; else
save.vibroWarnTime = atoi(ReceiveValue); Vibro.vibroWarnTime=save.vibroWarnTime; CM("<-из- MQTT: Время отображения сработки: ");
CM(save.vibroWarnTime); CMn(" сек."); Comm.status("Vibro Warn Time",save.vibroWarnTime,"sec"); saveChange(1); return;}

if (resiveCommand("VibroTimePlus")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.vibroTimePlus=255; else 
save.vibroTimePlus = atoi(ReceiveValue); Vibro.vibroTimePlus=save.vibroTimePlus; CM("<-из- MQTT: Добавляем вибро на ");
CM(save.vibroTimePlus); CMn(" мин."); Comm.status("Vibro Time Plus",save.vibroTimePlus,"min"); saveChange(1); return;}

if (resiveCommand("VibroEventCount")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.vibroCount=255; else
save.vibroCount = atoi(ReceiveValue); Vibro.vibroCountSave=save.vibroCount; CM("<-из- MQTT: Кол-во сработок для активации: ");
CMn(save.vibroCount); Comm.status("Vibro Event Count",save.vibroCount); saveChange(1); return;}

if (resiveCommand("TimeCountReset")) {SyncInd(1); save.vibroCountReset = atoi(ReceiveValue); Vibro.vibroCountReset=save.vibroCountReset; CM("<-из- MQTT: Считать по-новой после: ");
CM(save.vibroCountReset); CMn(" сек."); Comm.status("Vibro time count Reset",save.vibroCountReset,"sec"); saveChange(1); return;}

if (resiveCommand("TimeVibroIgnore")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.timeIgnoreVibroEvent=255; else 
save.timeIgnoreVibroEvent = atoi(ReceiveValue); Vibro.timeIgnoreVibroEvent=save.timeIgnoreVibroEvent; CM("<-из- MQTT: Игнорим после сработки: ");
CM(save.timeIgnoreVibroEvent); CMn(" сек."); Comm.status("Vibro ignore time after Event",save.timeIgnoreVibroEvent,"sec"); saveChange(1); return;}

if (resiveCommand("TimeStep")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.timeStep=255; else 
save.timeStep = atoi(ReceiveValue); Vibro.timeStep=save.timeStep; CM("<-из- MQTT: Время шага: ");
CM(save.timeStep); CMn(" Мсек."); Comm.status("Time step",save.timeStep,"Msec"); saveChange(1); return;}

if (resiveCommand("TimeWait")) {SyncInd(1); save.timeWait = atoi(ReceiveValue); Vibro.timeWait=save.timeWait; CM("<-из- MQTT: Время между шагами: ");
CM(save.timeWait); CMn(" Мсек."); Comm.status("Time between steps",save.timeWait,"Msec"); saveChange(1); return;}

if (resiveCommand("MinSteps")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.minSteps=255; else 
save.minSteps = atoi(ReceiveValue); Vibro.minSteps=save.minSteps; CM("<-из- MQTT: Минимум шагов: ");
CMn(save.minSteps); Comm.status("Minimum steps",save.minSteps); saveChange(1); return;}

if (resiveCommand("MaxSteps")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.maxSteps=255; else 
save.maxSteps = atoi(ReceiveValue); Vibro.maxSteps=save.maxSteps; CM("<-из- MQTT: Максимум шагов: ");
CMn(save.maxSteps); Comm.status("Maximum steps",save.maxSteps); saveChange(1); return;}

if (resiveCommand("MinNext")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.minNext=255; else 
save.minNext = atoi(ReceiveValue); Vibro.minNext=save.minNext; CM("<-из- MQTT: Мин до след шагов: ");
CM(save.minNext); CMn(" сек."); Comm.status("MinTime next steps",save.minNext,"sec"); saveChange(1); return;}

if (resiveCommand("MaxNext")) {SyncInd(1); if(atoi(ReceiveValue)>255) save.maxNext=255; else 
save.maxNext = atoi(ReceiveValue); Vibro.maxNext=save.maxNext; CM("<-из- MQTT: Макс до след шагов: ");
CM(save.maxNext); CMn(" сек."); Comm.status("MaxTime next steps",save.maxNext,"sec"); saveChange(1); return;}
#endif

if (strstr(ReciveTopic,"Status/Status")!=NULL) { // если есть слово Status/Status - запрос статуса - отослать статус
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/Status");
if(!strcmp(ReciveTopic,compareStr)) {SyncInd(1); CMn("<-из- MQTT: Запрос статуса"); SendStatus(2); return;}}}

if (resiveCommand("AutoMode")) {SyncInd(1); boolean resVal=atoi(ReceiveValue);
#if defined EEPROM_Enable
save.autoMode = resVal;
#endif
CM("<-из- MQTT: ПК Авто режим: "); CMn(resVal); Comm.status("AutoMode",resVal); if(!resVal) standBy=0; standByShot=0; standByQuick=0; saveChange(1); return;}

if (resiveCommand("StandByTime")) {SyncInd(1); save.standByTime=atoi(ReceiveValue);
CM("<-из- MQTT: ПК Время StandBy режима: "); CM(ReceiveValue); CMn(" сек.");
Comm.status("StandByTime",ReceiveValue,"sec"); saveChange(1); return;}

if (resiveCommand("StandByShotTime")) {SyncInd(1); uint32_t resVal=atoi(ReceiveValue); if(resVal>255) resVal=255;
#if defined EEPROM_Enable
save.standByShotTime = resVal;
#endif
CM("<-из- MQTT: ПК Время StandByShot режима: "); CM(resVal); CMn(" сек.");
Comm.status("StandByShotTime",resVal,"sec"); saveChange(1); return;}

if (resiveCommand("StandByQuickTime")) {SyncInd(1); uint32_t resVal=atoi(ReceiveValue); if(resVal>255) resVal=255;
#if defined EEPROM_Enable
save.standByQuickTime = resVal;
#endif
CM("<-из- MQTT: ПК Время StandByQuick режима: "); CM(resVal); CMn(" сек.");
Comm.status("StandByQuickTime",resVal,"sec"); saveChange(1); return;}

#if defined ButtonEnable
if (resiveCommand("ButtonDelay")) {SyncInd(1); double koeff=atof(ReceiveValue); if(koeff < 0.8) koeff=0.8; if(koeff > 4) koeff=4; 
#if defined EEPROM_Enable
save.pressSpeed = koeff; // коэффициент задержки (0.8 - 4.0)
#endif
dtostrf(koeff,1,2,value); CM("<-из- MQTT: ПК Задержка кнопки: "); CM(value); CM(" : ");
dtostrf(500*koeff,1,0,value); CM(value); CMn("мсек."); Comm.status("Button delay",koeff);
#if defined EEPROM_Enable
saveChange(1);
#endif
return;}
#endif

#if defined kitchenVent_Enable || defined MasterBathRoom
if (resiveCommand("VentTime")) {SyncInd(1); int16_t resVal = atoi(ReceiveValue);
#if defined EEPROM_Enable
save.ventAutoTime=resVal;
#endif
CM("<-из- MQTT: ПК Время автоотключения вытяжки: "); CM(resVal); CMn(" сек.");
Comm.status("Vent Auto Off Time",resVal,"sec"); saveChange(1); return;}
#endif

#if defined BadRoomRGBRule_Enable // для спальни откл светодиоды, если вкл белый свет | откл белый свет, если вкл светодиоды
if (RELAY_Value_[0] && !RELAY_Value_Save_[0]) {RELAY_Value_[1] = 0; Comm.status("Relay1",RELAY_Value_[1]); saveRelay=1;}
if (RELAY_Value_[1] && !RELAY_Value_Save_[1]) {RELAY_Value_[0] = 0; Comm.status("Relay1",RELAY_Value_[0]); saveRelay=1;}
#endif

#if defined MotionSens_Enable
if (resiveCommand("MotionIgnore")) {SyncInd(1); save.MotionIgnore = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Не реагировать после откл: "); CM(save.MotionIgnore); CMn(" сек.");
Comm.status("Motion Ignore",save.MotionIgnore,"sec"); saveChange(1); return;}

if (resiveCommand("MotionMemory")) {SyncInd(1); save.MotionOnMemory = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Считать сенсор сработавшим: "); CM(save.MotionOnMemory); CMn(" сек.");
Comm.status("MotionOn Memory",save.MotionOnMemory,"sec"); saveChange(1); return;}

if (resiveCommand("MotionEnable")) {SyncInd(1); save.MotionDetectEnable = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Реагировать на движение = "); CMn(save.MotionDetectEnable);
Comm.status("Motion Detect",save.MotionDetectEnable); saveChange(1); if(!save.MotionDetectEnable) {standByShot=0; Comm.status("StandByShot",standByShot);
if(save.MotionDetectEnable) Comm.status("Motion Detect",save.MotionDetectEnable); if(!save.MotionDetectEnable) standBy=0; standByShot=0; standByQuick=0;
if (save.MASTER_ESP) {Motion=0; Comm.status("Motion",Motion); Comm.status("BrightMode","0");}} MotionSensor=0; Comm.status("MotionSensor",MotionSensor); return;}

#else
if (save.MASTER_ESP) {
if (resiveCommand("MotionIgnore")) {SyncInd(1); save.MotionIgnore = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Не реагировать после откл: "); CM(save.MotionIgnore); CMn(" сек.");
Comm.status("Motion Ignore",save.MotionIgnore,"sec"); saveChange(1); return;}

if (resiveCommand("MotionMemory")) {SyncInd(1); save.MotionOnMemory = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Считать сенсор сработавшим: "); CM(save.MotionOnMemory); CMn(" сек.");
Comm.status("MotionOn Memory",save.MotionOnMemory,"sec"); saveChange(1); return;}

if (resiveCommand("MotionEnable")) {SyncInd(1); save.MotionDetectEnable = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Реагировать на движение = "); CMn(save.MotionDetectEnable);
Comm.status("Motion Detect",save.MotionDetectEnable); saveChange(1); if(!save.MotionDetectEnable) {standByShot=0; Comm.status("StandByShot",standByShot);
if(save.MotionDetectEnable) Comm.status("Motion Detect",save.MotionDetectEnable);
if (save.MASTER_ESP) {Motion=0; Comm.status("Motion",Motion); Comm.status("BrightMode","0");}} 
#if defined MotionSens_Enable
MotionSensor=0; Comm.status("MotionSensor",MotionSensor); return;
#endif
}}
#endif

#if defined MotionSens_Enable && defined PresenceSens_Enable
if (resiveCommand("PresenceIgnore")) {SyncInd(1); save.PresenceIgnore = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Не реагировать после откл: "); CM(save.PresenceIgnore); CMn(" сек.");
Comm.status("Presence Ignore",save.PresenceIgnore,"sec"); saveChange(1); return;}

if (resiveCommand("PresenceMemory")) {SyncInd(1); save.PresenceOnMemory = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Считать сенсор сработавшим: "); CM(save.PresenceOnMemory); CMn(" сек.");
Comm.status("PresenceOn Memory",save.PresenceOnMemory,"sec"); saveChange(1); return;}

if (resiveCommand("PresenceEnable")) {SyncInd(1); save.PresenceDetectEnable = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Реагировать на присутствие = "); CMn(save.PresenceDetectEnable);
Comm.status("Presence Detect",save.PresenceDetectEnable); saveChange(1); return;}
#endif

#if defined MasterSceneKitchen // MASTER возле мойки на кухне
if (resiveCommand("MotionWashEnable")) {SyncInd(1); save.MotionWashEnable = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Реагировать на движение = "); CMn(save.MotionWashEnable);
if(save.MotionWashEnable) Comm.status("Wash Motion Detect",save.MotionWashEnable);
MotionSensor=0; saveChange(1); Comm.status("MotionSensor",MotionSensor); return;}

if (resiveCommand("MotionWashTime")) {SyncInd(1); atoi(ReceiveValue)>255 ? save.MotionWashTime=255 : save.MotionWashTime = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Свет возле мойки на: "); CM(save.MotionWashTime); CMn(" сек.");
Comm.status("Wash light",save.MotionWashTime," sec"); saveChange(1); return;}
#endif

#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled// Датчики температуры
if (resiveCommand("DecimalTemp")) {SyncInd(1); save.DecimalTemp = atoi(ReceiveValue);
CM("<-из- MQTT: Температура до десятых >10<: "); CMn(save.DecimalTemp);
save.DecimalTemp ? Comm.status("Temperature decimal point >10<","Yes") : Comm.status("Temperature decimal point >10<","No"); saveChange(1); return;}

if (resiveCommand("ThresholdTemp")) {SyncInd(1); save.thresholdTemp = atoi(ReceiveValue);
CM("<-из- MQTT: Порог температуры: "); CM(save.thresholdTemp); CMn(" °C");
Comm.status("Threshold temperature",save.thresholdTemp,"°C"); saveChange(1); return;}

if (resiveCommand("ThresholdHUM")) {SyncInd(1); save.thresholdHUM = atoi(ReceiveValue);
CM("<-из- MQTT: Порог влажности: "); CM(save.thresholdHUM); CMn(" %");
Comm.status("Threshold humidity",save.thresholdHUM,"%"); saveChange(1); return;}

if (resiveCommand("HysteresisTemp"))  {SyncInd(1); save.hysteresisTemp = atoi(ReceiveValue);
CM("<-из- MQTT: Гистерезис температуры: "); CM(save.hysteresisTemp); CMn(" °C");
Comm.status("Hysteresis temperature",save.hysteresisTemp,"°C"); saveChange(1); return;}

if (resiveCommand("HysteresisHUM"))  {SyncInd(1); save.hysteresisHUM = atoi(ReceiveValue);
CM("<-из- MQTT: Гистерезис влажности: "); CM(save.hysteresisHUM); CMn(" %");
Comm.status("Hysteresis humidity",save.hysteresisHUM,"%"); saveChange(1); return;}
#endif

#if defined RGB_MODULE_LED_Enable
if (strstr(ReciveTopic,"Command/Color")!=NULL) {uint8_t Module; // если есть команда для Color(x), то устанавливаем цвет модуля
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"Color"); Module=i; itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); brightMode=0; mRGB.timeSave = millis(); strcpy(save.SaveModRGB[Module].hexColor,ReceiveValue); mRGB.HEXtoRGB(ReceiveValue,Module); mRGB.saveDelay = 10000; CM("<-из- MQTT: ПК Модуль"); CM(Module); CM(" цвет: "); CMn(ReceiveValue); MQTTStatus4("Color module",Module,ReceiveValue,"Module"); return;}}}

if (resiveCommand("BrightMode")) {SyncInd(1); brightMode=atoi(ReceiveValue); atoi(ReceiveValue) ? mRGB.saveDelay = 3600000 : mRGB.saveDelay = 10000; CM("<-из- MQTT: Яркую подсветку: "); if(atoi(ReceiveValue)) CMn("Включить"); else CMn("Выключить"); return;}

if (strstr(ReciveTopic,"Status/BrightMode")!=NULL) { // если есть слово Status/BrightMode - синхронизация - включить яркую подстветку
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/BrightMode");
if(!strcmp(ReciveTopic,compareStr)) 
{SyncInd(1); CM("<-из- MQTT: Яркую подсветку: "); if(atoi(ReceiveValue)) CMn("Включить"); else CMn("Выключить");
brightMode=atoi(ReceiveValue); if(atoi(ReceiveValue)) mRGB.saveDelay = 3600000; else mRGB.saveDelay = 10000; return;}}}

if (strstr(ReciveTopic,"Command/Power")!=NULL) {uint8_t Module; // если есть команда для Power(x), то вкл/откл модуль
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"Power"); Module=i; itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); mRGB.timeSave = millis(); if(atoi(ReceiveValue)) {CM("<-из- MQTT: Включить модуль"); CMn(Module); mRGB.powerON(Module);} else {mRGB.powerOFF(Module); CM("<-из- MQTT: Выключить модуль"); CMn(Module);} return;}}}

if (resiveCommand("Gamma")) {SyncInd(1); mRGB.timeSave = millis(); save.GammaCorrection=atoi(ReceiveValue);
save.GammaCorrection ? MQTTStatus("Gamma Correction","ON") : MQTTStatus("Gamma Correction","OFF");
CM("<-из- MQTT: Гамма коррекция: "); if(save.GammaCorrection) CMn("Включена"); else CMn("Выключена"); return;}

if (resiveCommand("Fade")) {SyncInd(1); mRGB.timeSave = millis(); save.FadeDelay = atoi(ReceiveValue);
MQTTStatus3("Fade delay",save.FadeDelay,"ms"); CM("<-из- MQTT: Задержка перехода "); CM(save.FadeDelay); CMn(" мс"); return;}

if (strstr(ReciveTopic,"Command/MyColor")!=NULL) {uint8_t Module; // если есть команда для MyColor(x), то устанавливаем любимый цвет модуля
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"MyColor"); Module=i; itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); mRGB.timeSave = millis(); strcpy(save.SaveModRGB[Module].favoriteColor,ReceiveValue);
MQTTStatus4("Favorite color module",Module,save.SaveModRGB[Module].favoriteColor,"Module"); CM("<-из- MQTT: Любимый цвет модуля"); CM(Module); CM(": "); CMn(save.SaveModRGB[Module].favoriteColor); return;}}}

if (strstr(ReciveTopic,"Command/BrColor")!=NULL) {uint8_t Module; // если есть команда для BrColor(x), то устанавливаем яркий цвет модуля
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"BrColor"); Module=i; itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); mRGB.timeSave = millis(); strcpy(save.SaveModRGB[Module].brightColor,ReceiveValue);
MQTTStatus4("Bright color module",Module,save.SaveModRGB[Module].brightColor,"Module"); CM("<-из- MQTT: Яркий цвет модуля"); CM(Module); CM(": "); CMn(save.SaveModRGB[Module].brightColor); return;}}}

if (strstr(ReciveTopic,"Command/Mode")!=NULL) {uint8_t Module; // если есть команда для Mode(x), то устанавливаем режим загрузки модуля (0-восстановить, 1-откл, 2-любимый)
for_i(0,sizeof(RELAY_Pin_)) {strcpy(compareStr,"Mode"); Module=i; itoa(i, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); mRGB.timeSave = millis(); save.StartMode[Module] = atoi(ReceiveValue);
char stat[70]; if (save.StartMode[Module] == 0) MQTTStatus4("StartMode module",Module,"Restore state","Module"); else if (save.StartMode[Module] == 1) MQTTStatus4("StartMode module",Module,"Turn OFF","Module");
else if (save.StartMode[Module] == 2) MQTTStatus4("StartMode module",Module,"Favorite Color","Module"); CM("<-из- MQTT: При запуске модуля"); CM(Module); CM(": "); if (save.StartMode[Module] == 0) CMn("восстановить состояние");
if (save.StartMode[Module] == 1) CMn("выключить"); if (save.StartMode[Module] == 2) CMn("любимый цвет"); return;}}}
#endif

#if defined RGB_LED_Enable
if (resiveCommand("Color")) {SyncInd(1); brightMode=0; RGB.timeSave = millis(); strcpy(save.hexColor,ReceiveValue); RGB.HEXtoRGB(ReceiveValue); RGB.saveDelay = 10000; CM("<-из- MQTT: ПК Установить цвет: "); CMn(ReceiveValue); MQTTStatus("Color",ReceiveValue); return;}

if (resiveCommand("BrightMode")) {SyncInd(1); brightMode=atoi(ReceiveValue); atoi(ReceiveValue) ? RGB.saveDelay = 3600000 : RGB.saveDelay = 10000; CM("<-из- MQTT: Яркую подсветку: "); if(atoi(ReceiveValue)) CMn("Включить"); else CMn("Выключить"); return;}

if (strstr(ReciveTopic,"Status/BrightMode")!=NULL) { // если есть слово Status/BrightMode - синхронизация - включить яркую подстветку
for_t(0,ctrlNumTopic) {strcpy(compareStr,save.controlTopic[t]); strcat(compareStr,"/Status/BrightMode");
if(!strcmp(ReciveTopic,compareStr)) 
{SyncInd(1); CM("<-из- MQTT: Яркую подсветку: "); if(atoi(ReceiveValue)) CMn("Включить"); else CMn("Выключить");
brightMode=atoi(ReceiveValue); if(atoi(ReceiveValue)) RGB.saveDelay = 3600000; else RGB.saveDelay = 10000; return;}}}

if (resiveCommand("Power")) {SyncInd(1); RGB.timeSave = millis(); if(atoi(ReceiveValue)) {CMn("<-из- MQTT: Включить подсветку"); RGB.powerON();} else {RGB.powerOFF(); CMn("<-из- MQTT: Выключить подсветку");} return;}

if (resiveCommand("Gamma")) {SyncInd(1); RGB.timeSave = millis(); save.GammaCorrection=atoi(ReceiveValue);
save.GammaCorrection ? MQTTStatus("Gamma Correction","ON") : MQTTStatus("Gamma Correction","OFF");
CM("<-из- MQTT: Гамма коррекция: "); if(save.GammaCorrection) CMn("Включена"); else CMn("Выключена"); return;}

if (resiveCommand("Fade")) {SyncInd(1); RGB.timeSave = millis(); save.FadeDelay = atoi(ReceiveValue);
MQTTStatus3("Fade delay",save.FadeDelay,"ms"); CM("<-из- MQTT: Задержка перехода "); CM(save.FadeDelay); CMn(" мс"); return;}

if (resiveCommand("MyColor")) {SyncInd(1); RGB.timeSave = millis(); strcpy(save.favoriteColor,ReceiveValue);
MQTTStatus("Favorite color",save.favoriteColor); CM("<-из- MQTT: Любимый цвет: "); CMn(save.favoriteColor); return;}

if (resiveCommand("BrColor")) {SyncInd(1); RGB.timeSave = millis(); strcpy(save.brightColor,ReceiveValue);
MQTTStatus("Bright color",save.brightColor); CM("<-из- MQTT: Цвет яркой подсветки: "); CMn(save.brightColor); return;}

if (resiveCommand("Mode")) {SyncInd(1); RGB.timeSave = millis(); save.StartMode = atoi(ReceiveValue);
char stat[70]; if (save.StartMode == 0) MQTTStatus("StartMode","Restore state"); else if (save.StartMode == 1) MQTTStatus("StartMode","Turn OFF");
else if (save.StartMode == 2) MQTTStatus("StartMode","Favorite Color"); CM("<-из- MQTT: При запуске "); if (save.StartMode == 0) CMn("восстановить состояние");
if (save.StartMode == 1) CMn("выключить"); if (save.StartMode == 2) CMn("любимый цвет"); return;}
#endif

#if defined Cold_Warm_LED_Enable
if(resiveCommand("ColdWarm")) {SyncInd(1); save.ColdWarm=atoi(ReceiveValue); if(save.ColdWarm>100) save.ColdWarm=100;
MQTTStatus("ColdWarm",save.ColdWarm); CWLED.deltaCalc(); saveChange(1); return;}

if(resiveCommand("Light")) {SyncInd(1); save.currentLight=atoi(ReceiveValue);
CM("<-из- MQTT: Normal Cold: "); CM(save.currentLight); MQTTStatus3("Normal Light value",save.currentLight,"%"); saveChange(1); return;}

if(resiveCommand("NightLight")) {SyncInd(1); save.nightLight=atoi(ReceiveValue);
CM("<-из- MQTT: Night Light: "); CM(save.nightLight); MQTTStatus3("Night Light value",save.nightLight,"%"); saveChange(1); return;}

if(resiveCommand("Fade")) {SyncInd(1); save.fadeDelay=atoi(ReceiveValue);
CM("<-из- MQTT: Fade Delay: "); CM(save.fadeDelay); MQTTStatus3("Fade Delay",save.fadeDelay,"ms"); saveChange(1); return;}
#endif

#if defined PZEM004T_Enable
if(resiveCommand("ResEnergy")) {SyncInd(1); Comm.status("Reset PZEM004T","Reset Energy kWh"); CMn("<-из- MQTT: ПК Сброс счетчика kWh"); pzem.resetEnergy(); return;}
#endif

if(resiveCommand("Reset")) {SyncInd(1); Comm.status("Restart ESP","ESP restarting"); CMn("<-из- MQTT: ПК Перезагрузка контроллера"); delay(50); ESP.restart(); return;}

#if defined EEPROM_Enable
if (resiveCommand("CommandToTopic0")) {SyncInd(1); save.CommandToTopic0 = atoi(ReceiveValue);
CM("<-из- MQTT: ПК Дублировать команды в 0 топик: "); if(save.CommandToTopic0) {CMn("Да"); Comm.status("Send Command to Topic0","Yes");}
else {CMn("Нет"); Comm.status("Send Command to Topic0","No");} saveChange(1); return;}

if (resiveCommand("Master")) {SyncInd(1); save.MASTER_ESP = atoi(ReceiveValue); CM("<-из- MQTT: ПК ESP Модуль: "); if(save.MASTER_ESP) CMn("MASTER"); else CMn("SLAVE");
CMn(save.MASTER_ESP); if (save.MASTER_ESP) Comm.status("ESP module","MASTER"); else Comm.status("ESP module","SLAVE"); saveChange(1); return;}

if (strstr(ReciveTopic,"Command/Topic")!=NULL) { // если есть команда для Command/Topic - подписываемся или сбрасываем
for_t(0,ctrlNumTopic) {strcpy(compareStr,"Topic"); itoa(t, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); CM("<-из- MQTT: ПК Контролировать топик"); CM(t); CM(": "); CMn(ReceiveValue);
boolean check=0;
if (length) {for_i(0,10) if(strcmp("",save.controlTopic[i])) check=1; if(!check) Comm.status("Controlled topic","Control topics");
strcpy(save.controlTopic[t],ReceiveValue); strcpy(value,ReceiveValue); Comm.SyncTopic[t]=0; Comm.masterSyncOk=0; strcpy(topic,save.controlTopic[t]); strcat(topic," - not syncronized"); standBy=0; standByShot=0; standByQuick=0;
Comm.status("Controlled topic",t,topic,"plus"); strcpy(topic,save.controlTopic[t]); strcat(topic,"/Status/#"); mqttClient.subscribe(topic,0);
CM("Подписываемся на: "); CMn(save.controlTopic[t]);} 
else {Comm.status("Controlled topic",t,"Not assigned","Plus"); CM("Отписываемся от: "); CMn(save.controlTopic[t]); strcpy(save.controlTopic[t],"");
check=0; for_i(0,ctrlNumTopic) if(strcmp("",save.controlTopic[i])) check=1; if(!check) {CMn("Нет контролируемых топиков");
Comm.status("Controlled topic","No monitored topics"); strcpy(topic,save.controlTopic[t]); mqttClient.unsubscribe(topic);}}
saveChange(1); return;}}}

#if defined GlobalHouseSwitch || defined MasterBedRoom
if (resiveCommand("LEDControl")) {SyncInd(1); CM("<-из- MQTT: Управлять LED квартиры: "); CMn(ReceiveValue);
Comm.status("LED control",ReceiveValue); save.LEDControl=atoi(ReceiveValue); saveChange(1); return;}

if (strstr(ReciveTopic,"Command/LEDTopic")!=NULL) { // если есть команда для Command/LEDTopic - подписываемся или сбрасываем
for_t(0,10) {strcpy(compareStr,"LEDTopic"); itoa(t, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); CM("<-из- MQTT: LED топик"); CM(t); CM(": "); CMn(ReceiveValue);
boolean check=0;
if (length) {for_i(0,10) if(strcmp("",save.LEDTopic[i])) check=1; if(!check) Comm.status("LED topics","Control LED topics");
strcpy(save.LEDTopic[t],ReceiveValue); strcpy(value,ReceiveValue); Comm.SyncLEDTopic[t]=0; Comm.LEDSyncOk=0; strcpy(topic,save.LEDTopic[t]); strcat(topic," - not syncronized");
Comm.status("LED topic",t,topic,"plus"); if (strcmp(save.LEDTopic[t],"")) {CM("Подписываемся на: "); CMn(save.LEDTopic[t]); {
for_i(0,5) {strcpy(topic,save.LEDTopic[t]); strcat(topic,"/Status/Relay"); 
char RelayNUM[2]; itoa(i,RelayNUM,10); strcat(topic,RelayNUM); mqttClient.subscribe(topic,0);}
strcpy(topic,save.LEDTopic[t]); strcat(topic,"/Status/IP"); mqttClient.subscribe(topic,0);}}
} else {Comm.status("LED topic",t,"Not assigned","Plus");
check=0; for_i(0,10) if(strcmp("",save.LEDTopic[i])) check=1; if(!check) {CMn("Нет LED топиков");
Comm.status("LED topics","Not control");}
CM("Отписываемся от: "); CMn(save.LEDTopic[t]); strcpy(save.LEDTopic[t],"");
strcpy(topic,save.LEDTopic[t]); mqttClient.unsubscribe(topic);}
saveChange(1); return;}}}
#endif

if (strstr(ReciveTopic,"Command/SSID")!=NULL) { // если есть команда для Command/Topic - подписываемся или сбрасываем
for_t(0,5) {strcpy(compareStr,"SSID"); itoa(t, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); CM("<-из- MQTT: Сеть "); CM(save.WIFI_SSID[t]); CM(": ");
if (length) {strcpy(save.WIFI_SSID[t],ReceiveValue); CMn(ReceiveValue); if(strcmp(save.WIFI_PASSWORD[t],"")) wifiMulti.addAP(save.WIFI_SSID[t],save.WIFI_PASSWORD[t]);} else {CMn("удаляем"); strcpy(save.WIFI_SSID[t],""); strcpy(save.WIFI_PASSWORD[t],"");}
if(strcmp(save.WIFI_SSID[t],"")) strcpy(ReceiveValue,save.WIFI_SSID[t]); else {strcpy(ReceiveValue,"Not assigned"); Comm.status("WiFi SSID ",t,ReceiveValue,"plus"); saveChange(1); return;} strcat(ReceiveValue," , password ");
if(strcmp(save.WIFI_PASSWORD[t],"")) {char pass[15] = {""}; for_i(0,2) pass[i]=save.WIFI_PASSWORD[t][i]; strcat(pass,"**** - ****");
uint16_t p=2; while(p<40 && save.WIFI_PASSWORD[t][p+2]!='\0') p++; for_i(13,15) {pass[i]=save.WIFI_PASSWORD[t][p]; p++;} pass[15]='\0';
strcat(ReceiveValue,pass);} else strcat(ReceiveValue," not assigned");
Comm.status("WiFi SSID ",t,ReceiveValue,"plus"); saveChange(1); return;}}}

if (strstr(ReciveTopic,"Command/PASS")!=NULL) { // если есть команда для Command/Topic - подписываемся или сбрасываем
for_t(0,5) {strcpy(compareStr,"PASS"); itoa(t, value,10); strcat(compareStr, value);
if(resiveCommand(compareStr)) {SyncInd(1); CM("<-из- MQTT: Пароль "); CM(save.WIFI_SSID[t]); CM(": ");
if (length) {strcpy(save.WIFI_PASSWORD[t],ReceiveValue); CMn(ReceiveValue); if(strcmp(save.WIFI_SSID[t],"")) wifiMulti.addAP(save.WIFI_SSID[t],save.WIFI_PASSWORD[t]);} else {CMn("удаляем"); strcpy(save.WIFI_PASSWORD[t],"");}
if(strcmp(save.WIFI_SSID[t],"")) strcpy(ReceiveValue,save.WIFI_SSID[t]); else strcpy(ReceiveValue,"Not assigned"); strcat(ReceiveValue," , password ");
if(strcmp(save.WIFI_PASSWORD[t],"")) {char pass[15] = {""}; for_i(0,2) pass[i]=save.WIFI_PASSWORD[t][i]; strcat(pass,"**** - ****");
uint16_t p=2; while(p<40 && save.WIFI_PASSWORD[t][p+2]!='\0') p++; for_i(13,15) {pass[i]=save.WIFI_PASSWORD[t][p]; p++;} pass[15]='\0';
strcat(ReceiveValue,pass);} else strcat(ReceiveValue," not assigned");
Comm.status("WiFi SSID ",t,ReceiveValue,"plus"); saveChange(1); return;}}}

if (resiveCommand("Default")) {SyncInd(1); CM("<-из- MQTT: ПК Сброс параметров");
Comm.status("ESP Default reset","Loading default setting");
#if defined ESP_EEPROM_Enable
EEPROM.begin(4096);
delay(10);
#endif
int16_t addr = 4095;
EEPROM.put(addr, '0');
#if defined ESP_EEPROM_Enable
EEPROM.end();
#endif
CMn("Записали команду очистки"); CMn("Перезагрузка ESP"); SyncInd(1); delay(10); ESP.restart(); return;}

#if defined HX711_Enable
if(resiveCommand("Tare")) {SyncInd(1); CMn("<-из- MQTT: ПК Сброс веса"); status("Tare reset","Ok"); scale.tare(); return;}
#endif

strcpy(compareStr,ESPName); strcat(compareStr,"/Command");
if (strstr(ReciveTopic,compareStr)!=NULL) {CMn("Команда не верна или не нужна"); Comm.status("Command","Wrong or not required"); return;}

#endif // EEPROM_Enable END
return; //без этой херни вечный перезагруз
}
#endif // MQTT_SendEnable END

void MotionCountDown() {if(!Motion) return; returnSec(1); uint8_t MotionOnMemory = 3;
static uint32_t sec; static uint8_t saveVal, roundVal; static boolean min; boolean ctrlTopic=0;
#if defined EEPROM_Enable
MotionOnMemory=save.MotionOnMemory;
#endif
#if defined MotionSens_Enable && defined PresenceSens_Enable
if (Motion) {if(Presen.Presence) motionStart=millis();}
#endif
if (millis() - motionStart < MotionOnMemory*1000) {
sec = (MotionOnMemory*1000 - (millis() - motionStart)); 
if(sec>=60000) {min=1; (sec/1000)%60>29 ? roundVal=sec/60000+1 : roundVal=sec/60000;} else {roundVal=sec/1000; min=0;} if(saveVal!=roundVal) {
CM("Выкл. Motion через: "); CM(roundVal); if(min) CMn(" мин."); else CMn(" сек."); saveVal=roundVal;} return;} 
#if defined MotionSens_Enable && defined PresenceSens_Enable
if(!Presen.Presence) {Motion=0; CMn("Выкл. Motion по таймеру."); if(save.MASTER_ESP) MQTTStatus("Motion",Motion); timeMotionIgnore=millis();}
#else
Motion=0; CMn("Выкл. Motion по таймеру."); if(save.MASTER_ESP) MQTTStatus("Motion",Motion); timeMotionIgnore=millis();
#endif
}

#if defined EEPROM_Enable
void SaveData() {if(!saveChange) return;
dataToEEPROM.SaveData();
#if defined MQTT_SendEnable && defined EEPROM_Enable
if(MQTTOk) {char sendTopic[50], sendValue[50], value[7];
ultoa(sizeof(save),value,10); strcpy(sendValue,value); strcat(sendValue," bytes to adress ");
itoa(dataToEEPROM.startAdress,value,10); strcat(sendValue,value); strcat(sendValue," , "); itoa(save.saveCount,value,10); strcat(sendValue,value);
strcat(sendValue," times"); MQTTStatus("Save EEPROM",sendValue);}
#endif
saveChange=0;}
#endif

#if defined ButtonEnable
void EventButton() {SCENE=Button.scan(); if(SCENE) {char outValue[20]; itoa(SCENE,outValue,10);
if(shotPress) strcat(outValue," Shot"); if(doublePress) strcat(outValue," Double"); if(longPress) strcat(outValue," Long");
SwitchScene(); MQTTStatus("SCENE",outValue);}}
#endif

#if defined IRSens_Enable
void EventIR() {SCENE=IRSens.scan(); if(SCENE) {char outValue[20]; itoa(SCENE,outValue,10);
if(shotPress) strcat(outValue," Shot"); if(doublePress) strcat(outValue," Double"); if(longPress) strcat(outValue," Long");
SwitchScene(); MQTTStatus("SCENE",31);}}
#endif

void setup() {
#if defined DebagEnable
Serial.begin(115200); delay(50); CMn("\n");
#endif
char txtSize[10]; int32_t size = ESP.getFlashChipSize(); if(size < 1024) strcpy(txtSize," байт"); else if(size < 1048576) {size/=1024; strcpy(txtSize," Kбайт");}
else if(size < 1073741824) {size/=1024; size/=1024; strcpy(txtSize," Mбайт");}
CM("Память чипа: "); CM(size); CMn(txtSize); char str[10];
CM("Прошивка занимает: "); float Size=ESP.getSketchSize(); if(Size<1024) {CM(Size); CMn(" байт");} else if(Size<1024*1024) {dtostrf(Size/1024, 0, 0, str); CM(str); CMn(" Kбайт");} else {dtostrf(Size/1024/1024, 0, 1, str); CM(str); CMn(" Мбайт");}
CM("Firmware version: "); CMn(FirmwareVersion);
CM("Место для OTA прошивки: "); Size=ESP.getFreeSketchSpace();
if(Size<1024) {CM(Size); CMn(" байт");} else if(Size<1024*1024) {dtostrf(Size/1024, 0, 0, str); CM(str); CMn(" Kбайт");} else {dtostrf(Size/1024/1024, 0, 1, str); CM(str); CMn(" Мбайт");}
CM("Прошивка по воздуху: "); if(ESP.getFreeSketchSpace()>(ESP.getSketchSize()*1.1)) {OTApossible=1;
CMn("Доступна");} else CMn("Невозможна");
#if defined EEPROM_Enable
CMn("Сохранение настроек в EEPROM: Да");
#else
CMn("Сохранение настроек в EEPROM: Нет");
#endif

#if defined EEPROM_Enable
#if not defined clearMemory
dataToEEPROM.ReadData();
#else
CMn("Запись EEPROM по умолчинию");
saveChange=1;
#endif
#endif

#if defined ledIndikator_Enable
Led.status();
#endif

#if defined ButtonEnable
Button.status();
#endif

#if defined GlobalHouseSwitch
for_t(0, 30) for_i(0,sizeof(RELAY_Pin_)) RELAY_State_[t][i]=0;
#endif

#if defined RelayEnable
CM("Пин"); if(sizeof(RELAY_Pin_)>1) CM("ы"); CM(" реле: ");
for_i(0,sizeof(RELAY_Pin_)) {
{if(RELAY_Pin_[i]!=nPIN && RELAY_Pin_[i]!=RGBPIN && RELAY_Pin_[i]!=RGBPIN0 && RELAY_Pin_[i]!=RGBPIN1 && RELAY_Pin_[i]!=RGBPIN2
&& RELAY_Pin_[i]!=RGBPIN3 && RELAY_Pin_[i]!=RGBPIN4 && RELAY_Pin_[i]!=CWPIN) {pinMode(RELAY_Pin_[i], OUTPUT); writeRelay(RELAY_Pin_[i], 0); CM(RELAY_Pin_[i]);}
if(RELAY_Pin_[i]==nPIN) CM("No"); if(RELAY_Pin_[i]==RGBPIN) CM("RGB"); if(RELAY_Pin_[i]==RGBPIN0) CM("RGB Module0");
if(RELAY_Pin_[i]==RGBPIN1) CM("RGB Module1"); if(RELAY_Pin_[i]==RGBPIN2) CM("RGB Module2"); if(RELAY_Pin_[i]==RGBPIN3) CM("RGB Module3");
if(RELAY_Pin_[i]==RGBPIN4) CM("RGB Module4"); if(RELAY_Pin_[i]==CWPIN) CM("CWLED");
#if defined RGB_LED_Enable
if(RELAY_Pin_[i]==RGBPIN) RGB.Relay_PIN=i;
#endif
#if defined Cold_Warm_LED_Enable
if(RELAY_Pin_[i]==CWPIN) CWLED.Relay_PIN=i;
#endif
if (i<sizeof(RELAY_Pin_)-1) CM(","); CM(" ");}} CMn("");
#if defined MasterBathRoom
RELAY_Value_Save_[3]=1;
saveRelay=1; // установить на Relay3 (зеркало в ванне) неинвертированный 0
#endif
#endif

#if defined Cold_Warm_LED_Enable
CM("Пины холодного канала: "); CM(CWLED.Led_Pin_[0]); CM(", теплого канала: "); CMn(CWLED.Led_Pin_[1]);
analogWriteFreq(250); // 250Гц ШИМ
#endif

#if defined MQTT_SendEnable
#if defined EEPROM_Enable
Comm.MASTER_ESP=save.MASTER_ESP;
#endif

#if not defined EEPROM_Enable
CMn("Нет контролируемых топиков");
#endif

#endif

#if defined Vibro_Enable
CM("Пин сенсора вибро: "); CMn(Vibro.VibroSens_PIN);
#endif

#if defined VL6180X_Enable || defined BH1750_Enable || defined BME280_Enable || defined MAX44009_Enabled || defined AM2320_Enabled
CM("Шина I2C, Sensor PINs SDA: "); CM(SDA); CM(", SCL: "); CMn(SCL);
#endif

#if defined AM2301A_Enabled
CM("Пин сенсора AM2301A: "); CMn(DHTPIN);
#endif

#if defined BME280_Enable || defined AM2301A_Enabled || defined AM2320_Enabled
CM("Температура до десятых >10<: "); if(save.DecimalTemp) CMn("Да"); else CMn("Нет");
CM("<-из- MQTT: Порог температуры: "); CM(save.thresholdTemp); CMn(" °C");
CM("<-из- MQTT: Порог влажности: "); CM(save.thresholdHUM); CMn(" %");
#endif

#if defined S8_CO2_Enable
CM("CO2 Sensor PINs: Uart_Rx - "); CM(Uart_Rx); CM(", Uart_Tx - "); CMn(Uart_Tx);
#endif

#if defined PZEM004T_Enable
CM("PZEM004T Sensor PINs: Uart_Rx - "); CM(Uart_Rx); CM(", Uart_Tx - "); CMn(Uart_Tx);
#endif

#if defined RGB_LED_Enable
RGB.Status();
#endif

#if defined RGB_MODULE_LED_Enable
mRGB.Status();
#endif

InitializationOk = 1; Serial.println("Инициализация завершена");
}

void loopspeed() {static uint32_t loops; loops++; returnSec(1); CM("Loops in sec: "); CMn(loops); loops=0;}

void loop() { //loopspeed();
#if defined EEPROM_Enable
SaveData();
#endif
#if defined RelayEnable && not defined GlobalHouseSwitch
SaveRelay();
#endif
#if defined ButtonEnable
EventButton();
#endif
#if defined IRSens_Enable
EventIR();
#endif
#if defined MotionSens_Enable
Move.loop(); MotionCountDown();
#else
if(save.MASTER_ESP) MotionCountDown();
#endif
#if defined MotionSens_Enable && defined PresenceSens_Enable
Presen.loop();
#endif
CountDown.loop();
#if defined RGB_LED_Enable
RGB.loop();
#endif
#if defined RGB_MODULE_LED_Enable
mRGB.loop();
#endif
#if defined Vibro_Enable
Vibro.loop();
#endif
#if defined Cold_Warm_LED_Enable
CWLED.loop();
#endif
#if defined ledIndikator_Enable
#if defined ButtonEnable
Led.ProgramInd = Button.programInd;
#endif
boolean noConnectLED=0;
#if defined OTAEnable || defined MQTT_SendEnable
if(!WiFiOk) noConnectLED=1;
#if defined MQTT_SendEnable
if(!MQTTOk || !Comm.masterSyncOk) noConnectLED=1;
#endif
#endif
Led.loop(); Led.NoWifiInd=noConnectLED; Led.StandByInd=standBy; Led.StandByShotInd=standByShot; Led.StandByQuickInd=standByQuick; Led.ventStandByInd=ventStandBy; Led.NoAutoModeInd=!save.autoMode;
#endif
#if defined OTAEnable || defined MQTT_SendEnable
Comm.loop(); 
#if defined MQTT_SendEnable
if(!MQTTOk) return; SendStatus(0);
#endif
#endif
#if defined BH1750_Enable || defined VL6180X_Enable || defined BME280_Enable || defined HX711_Enable || defined AM2301A_Enabled || defined MAX44009_Enabled || defined S8_CO2_Enable || defined AM2320_Enabled || defined PZEM004T_Enable
sensLoop();
#endif
}
