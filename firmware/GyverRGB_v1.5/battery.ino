
void backlTick() {
#if (USE_OLED == 1)
  if (LCD_BACKL && backlState && millis() - backlTimer >= (long)BACKL_TOUT * 1000) {
    backlState = false;
    oled.clear();
  }
#endif
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

    if (POWER_CONTROL && voltage < 9000) {
      LEDoff();
    }

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

#if (USE_OLED == 1)
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
#endif
}

byte mVtoPerc(int volts, int volt100, int volt80, int volt60, int volt40, int volt20, int volt0) {
  int capacity;
  if (volts > volt80) capacity = map(volts, volt100, volt80, 100, 80);
  else if ((volts <= volt80) && (volts > volt60) ) capacity = map(volts, volt80, volt60, 80, 60);
  else if ((volts <= volt60) && (volts > volt40) ) capacity = map(volts, volt60, volt40, 60, 40);
  else if ((volts <= volt40) && (volts > volt20) ) capacity = map(volts, volt40, volt20, 40, 20);
  else if (volts <= volt20) capacity = map(volts, volt20, volt0, 20, 0);
  capacity = constrain(capacity, 0, 100);
  return capacity;
}
