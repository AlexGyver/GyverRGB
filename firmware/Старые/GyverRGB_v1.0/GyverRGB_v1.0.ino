/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLED/
  Исходники на GitHub: https://github.com/AlexGyver/GyverLED/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

/*
  GyverLED - контроллер RGB светодиодной ленты с кучей возможностей:
  - 10 настраиваемых пресетов
  - 11 настраиваемых режимов свечения
  - Все настройки хранятся в EEPROM и не сбрасываются
  - Вывод на OLED дисплей
  - Управление с энкодера и ИК пульта (краткое руководство в файле Описание.txt)
  - Четыре варианта частоты ШИМ
  - Режим ограничения тока (расчёт на основе яркости)
  - Измерение напряжения питания и вывод в % или вольтах
  - Режим поддержания яркости по мере разрядки АКБ
*/

// ================ НАСТРОЙКИ ================
// ------ Дисплей ------
#define LCD_BACKL 1         // автоотключение подсветки дисплея (1 - разрешить) 
#define BACKL_TOUT 60       // таймаут неактивности отключения дисплея, секунды
#define CONTRAST 150        // контрастность (яркость) дисплея 0-255
#define ROTATE_DISP 0       // 0 или 1 - повернуть дисплей на 180 градусов
#define I2C_ADDRESS 0x3C    // адрес дисплея
// примерно на 200 строке можно поменять шрифт дисплея

// ------ Драйвер ------
#define HIGH_FREQUENCY 2    // 0 - 490 Гц, 1 - 7.8 кГц, 2 - 31.4 кГц, 3 - ручная настройка
#define PWM_FREQUENCY 15000 // частота ШИМ на настройке №3, Герц
#define DRIVER_DIRECTION 0  // 0 - обычный (мосфеты), 1 - реверс (LED amplifier)

// ------ Лента ------
#define MAX_CURRENT 0       // макс. ток в мА, при значении 0 фича не активируется
#define NUM_LEDS 60         // кол-во светодиодов для расчёта ограничения тока (только для диодов 5050!!!)
#define SMOOTH_K 0.25       // коэффициент плавности огня

// ------ Bluetooth ------
#define USE_BT 0            // 1 - использовать Bluetooth, 0 - нет

// ------ ИК пульт ------
#define USE_IR 1            // 1 - использовать ИК пульт, 0 - нет
#define IR_STEP 10          // шаг изменения настроек с пульта

// ------ Энкодер ------
#define USE_ENC 1           // 1 - использовать энкодер, 0 - нет
#define ENC_REVERSE 1       // 1 - инвертировать направление энкодера
#define ENC_TYPE 1          // 0 или 1 - тип энкодера

// ------ Напряжение ------
#define VOLTMETER 0         // 0 или 1 - вкл/выкл вольтметр (делитель напряжения в пин А0)
#define CHARGE_VAL 1        // вывод напряжения: 0 - в процентах, 1 - в вольтах
#define CONSTANT_BRIGHT 0   // 0 или 1 - вкл/выкл поддержание яркости при разрядке АКБ (только для диодов 5050!!!) (в схеме должен стоять делитель)
#define VREF 5.1            // напряжение на пине 5V
#define R1 10010            // точное значение 10 кОм
#define R2 4700             // точное значение 4.7 кОм

// --------- Цвет ---------
#define LUT_R 1.0           // коэффициент LUT матрицы красного цвета (0.0 - 1.0)
#define LUT_G 1.0           // коэффициент LUT матрицы зелёного цвета (0.0 - 1.0)
#define LUT_B 1.0           // коэффициент LUT матрицы синего цвета (0.0 - 1.0)

// ================ ДЛЯ РАЗРАБОТЧИКОВ ================
// ----------- ПИНЫ -----------
// пин вольтметра
#define VOLT_PIN A0

// драйвер
#define PIN_R 9
#define PIN_G 10
#define PIN_B 3

// энкодер
#define CLK 4
#define DT 5
#define SW 6

// ИК приёмник
#define pinIR 2

// BT
#define BT_RX 7
#define BT_TX 8

// ----- КНОПКИ ПУЛЬТА WAVGAT -----
#define BUTT_UP     0xF39EEBAD
#define BUTT_DOWN   0xC089F6AD
#define BUTT_LEFT   0xE25410AD
#define BUTT_RIGHT  0x14CE54AD
#define BUTT_OK     0x297C76AD
#define BUTT_1      0x4E5BA3AD
#define BUTT_2      0xE51CA6AD
#define BUTT_3      0xE207E1AD
#define BUTT_4      0x517068AD
#define BUTT_5      0x1B92DDAD
#define BUTT_6      0xAC2A56AD
#define BUTT_7      0x5484B6AD
#define BUTT_8      0xD22353AD
#define BUTT_9      0xDF3F4BAD
#define BUTT_0      0xF08A26AD
#define BUTT_STAR   0x68E456AD
#define BUTT_HASH   0x151CD6AD

// ----- КНОПКИ ПУЛЬТА KEYES -----
/*
  #define BUTT_UP     0xE51CA6AD
  #define BUTT_DOWN   0xD22353AD
  #define BUTT_LEFT   0x517068AD
  #define BUTT_RIGHT  0xAC2A56AD
  #define BUTT_OK     0x1B92DDAD
  #define BUTT_1      0x68E456AD
  #define BUTT_2      0xF08A26AD
  #define BUTT_3      0x151CD6AD
  #define BUTT_4      0x18319BAD
  #define BUTT_5      0xF39EEBAD
  #define BUTT_6      0x4AABDFAD
  #define BUTT_7      0xE25410AD
  #define BUTT_8      0x297C76AD
  #define BUTT_9      0x14CE54AD
  #define BUTT_0      0xC089F6AD
  #define BUTT_STAR   0xAF3F1BAD
  #define BUTT_HASH   0x38379AD
*/

// EEPROM
#define EEPR_TIME 30000
#define EEPR_RESET 1023
#define RESET_VAL 65
#define PRESET_ADDR 200

// Библиотеки
#include <SoftwareSerial.h>
SoftwareSerial btSerial(BT_TX, BT_RX); // RX, TX

#include <GyverRGB.h>
GRGB strip(PIN_R, PIN_G, PIN_B);  // куда подключены цвета (R, G, B)

#include <GyverEncoder.h>
Encoder enc(CLK, DT, SW);

#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
SSD1306AsciiWire oled;

#include <IRLremote.h>
CHashIR IRLremote;

#include <avr/eeprom.h>

// Переменные
int presetSettings[5];    // текущие настройки пресета
const byte setAmount[] = {4, 3, 2, 2, 2, 3, 3, 4, 4, 4, 2};         // количество настроек в режиме
const byte startFrom[] = {0, 4, 7, 9, 11, 13, 16, 19, 23, 27, 31}; // начало индекса в списке лейблов
const char *labels[] = {      // список названий лейблов
  "BR", "R", "G", "B",
  "HUE", "SAT", "VAL",
  "BR", "COL",
  "BR", "COL",
  "BR", "TEMP",
  "BR", "SPD", "STP",
  "BR", "SPD", "MIN",
  "BR", "COL", "SPD", "MIN",
  "HUE", "SAT", "VAL", "SPD",
  "HUE", "SAT", "VAL", "SPD",
  "BR", "SPD",
};

const char *modeNames[] = {    // список названий режимов
  "RGB", "HSV", "Color", "ColorSet", "Kelvin", "ColorW",
  "Fire", "FireM", "Strobe", "StrobeR", "Police",
};
const int maxVals[] = {
  255, 255, 255, 255,
  255, 255, 255,
  255, 1530,
  255, 15,
  255, 10000,
  255, 1000, 500,
  255, 1000, 255,
  255, 255, 1000, 255,
  255, 255, 255, 1000,
  255, 255, 255, 1000,
  255, 1000,
};
const char *colorNames[] = {
  "WHITE",
  "SILVER",
  "GRAY",
  "BLACK",
  "RED",
  "MAROON",
  "YELLOW",
  "OLIVE",
  "LIME",
  "GREEN",
  "AQUA",
  "TEAL",
  "BLUE",
  "NAVY",
  "PINK",
  "PURPLE",
};
const uint32_t colorVals[] = {
  0xFFFFFF, 0xC0C0C0, 0x808080, 0x000000, 0xFF0000, 0x800000,
  0xFFFF00, 0x808000, 0x00FF00, 0x008000, 0x00FFFF, 0x008080,
  0x0000FF, 0x000080, 0xFF00FF, 0x800080,
};

uint32_t eeprTimer;
uint32_t effTimer;
uint16_t effPeriod;
boolean eeprFlag;
int16_t presetNum;   // номер пресета
int16_t modeNum = 0;     // номер режима
int8_t navPos = 0;      // позиция навигации
int invSet = 0;
boolean invFlag;
boolean changeFlag;
boolean settingsChanged;
boolean ONflag = true;
uint32_t IRdata;
boolean toggleFlag;
float dividerCoef = (float)((R1 + R2) / R2);
int voltage;
byte batPerc;
uint32_t voltmeterTimer;
boolean backlState = true;
uint32_t backlTimer;

void setup() {
  //Serial.begin(9600);
  if (USE_BT) btSerial.begin(9600);
  if (USE_IR) IRLremote.begin(pinIR);
  randomSeed(analogRead(1));
  voltmeterTimer = millis() - 3000;

  // выставляем режим и частоту ШИМ
  if (HIGH_FREQUENCY == 1) {
    TCCR1B |= _BV(WGM12);
    TCCR1B = TCCR1B & 0b11111000 | 0x02;
    TCCR2A |= _BV(WGM20) | _BV(WGM21);
    TCCR2B = TCCR2B & 0b11111000 | 0x02;
  } else if (HIGH_FREQUENCY == 2) {
    TCCR1B &= ~_BV(WGM12);
    TCCR1B = TCCR1B & 0b11111000 | 0x01;
    TCCR2A |= _BV(WGM20);
    TCCR2B = TCCR2B & 0b11111000 | 0x01;
  } else if (HIGH_FREQUENCY == 3) {
    strip.highFrequency(PWM_FREQUENCY);
  }

  if (MAX_CURRENT > 0) strip.setMaxCurrent(NUM_LEDS, 12000, MAX_CURRENT);
  if (DRIVER_DIRECTION) strip.setDirection(REVERSE);
  if (LUT_R != 1.0 || LUT_G != 0 || LUT_B != 0) strip.setLUT(LUT_R, LUT_G, LUT_B);

  if (ENC_TYPE) enc.setType(TYPE2);
  if (ENC_REVERSE) enc.setDirection(REVERSE);

  // работаем с EEPROM
  if (eeprom_read_byte((uint8_t*)EEPR_RESET) != RESET_VAL) {    // первый запуск
    eeprom_write_byte((uint8_t*)EEPR_RESET, RESET_VAL);         // запомнили
    for (byte i = 0; i < 10; i++) eeprom_write_byte(i, 0);
    for (byte i = 10; i < 200; i += 2) {
      eeprom_write_word(i, 0);
      if (i % 10 == 0) eeprom_write_word(i, 255);
    }
    eeprom_write_byte(PRESET_ADDR, 0);
    writeSettings();
  }
  presetNum = eeprom_read_byte((uint8_t*)PRESET_ADDR);
  readSettings();
  delay(100);

  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  oled.setContrast(CONTRAST);

  if (ROTATE_DISP) {
    oled.ssd1306WriteCmd(SSD1306_SEGREMAP);
    oled.ssd1306WriteCmd(SSD1306_COMSCANINC);
  }
  oled.clear();

  // шрифт дисплея, выбирай любой
  oled.setFont(Adafruit5x7);
  //Adafruit5x7
  //font5x7
  //Iain5x7
  //lcd5x7
  //Stang5x7
  //System5x7
  //SystemFont5x7

  settingsChanged = true;
  drawInfo();
  drawSettings();
}

void loop() {
  backlTick();      // выключение дисплея
  controlTick();    // отработка управления
  effectsTick();    // вывод режимов
  voltmeterTick();  // измерение напряжения
  if (USE_BT) bluetoothTick();  // парсинг блютус
}

void backlTick() {
  if (LCD_BACKL && backlState && millis() - backlTimer >= (long)BACKL_TOUT * 1000) {
    backlState = false;
    oled.clear();
  }
}
void backlOn() {
  backlState = true;
  backlTimer = millis();
  drawInfo();
  drawSettings();
}

void voltmeterTick() {
#if (VOLTMETER == 1 || CONSTANT_BRIGHT == 1)
  if (millis() - voltmeterTimer >= 3000) {
    voltmeterTimer = millis();

    // расчёт напряжения в мВ
    for (byte i = 0; i < 10; i++) {
      analogRead(VOLT_PIN);   // отсев первых 10 измерений
    }
    int averVoltage = 0;
    for (byte i = 0; i < 10; i++) {
      averVoltage += analogRead(VOLT_PIN);
    }
    averVoltage /= 10;
    voltage = (float)averVoltage * VREF / 1.023 * dividerCoef;

#if (CONSTANT_BRIGHT == 1)
    // поддержание яркости
    strip.constantBrightTick(9500, voltage);
#endif

#if (VOLTMETER == 1)
    drawBattery();
#endif
  }
#endif
}

void drawBattery() {
  // перевод в проценты для трёх банок лития
  batPerc = mVtoPerc(voltage, 12600, 11850, 11550, 11250, 11100, 8400);
  if (CHARGE_VAL) {
    float thisVoltage = (float)voltage / 1000;
    oled.setCursor(90, 0);
    oled.print("   ");
    oled.setCursor(90, 0);
    oled.print(thisVoltage, 1);
    oled.print("V");
  } else {
    oled.setCursor(110, 0);
    oled.print("   ");
    oled.setCursor(110, 0);
    oled.print(batPerc);
    oled.print("%");
  }
}

byte mVtoPerc(int volts, int volt100, int volt80, int volt60, int volt40, int volt20, int volt0) {
  int capacity;
  Serial.println(volts);
  if (volts > volt80) capacity = map(volts, volt100, volt80, 100, 80);
  else if ((volts <= volt80) && (volts > volt60) ) capacity = map(volts, volt80, volt60, 80, 60);
  else if ((volts <= volt60) && (volts > volt40) ) capacity = map(volts, volt60, volt40, 60, 40);
  else if ((volts <= volt40) && (volts > volt20) ) capacity = map(volts, volt40, volt20, 40, 20);
  else if (volts <= volt20) capacity = map(volts, volt20, volt0, 20, 0);
  capacity = constrain(capacity, 0, 100);
  return capacity;
}
