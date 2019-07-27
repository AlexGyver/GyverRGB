// управление
boolean brightDirection = false;

void changeNav() {
  if (++navPos >= 3) navPos = 0;
  if (navPos == 2) {
    invFlag = true;
    invSet = 0;
  }
  else invFlag = false;
  drawInfo();
  drawSettings();
}

void changePreset() {
  settingsChanged = true;
  invSet = 0;
  readSettings();    // читаем новые настройки
  drawInfo();
  drawSettings();
}

void changeMode() {
  changeFlag = true;
  settingsChanged = true;
  invSet = 0;
  drawInfo();
  drawSettings();
}

// умный инкрементатор для настроек
void incr(int* val, int incr, int limit) {
  *val += incr;
  if (*val > limit) *val = limit;
  if (*val < 0) *val = 0;
}

// сменить режим на
void changePresetTo(byte preset) {
  if (changeFlag) {
    writeSettings(); // сохраняем текущие настройки
    changeFlag = false;
  }
  presetNum = preset;
  changePreset();
}

// включить систему
void LEDon() {
  ONflag = true;
  settingsChanged = true;
  btnColorChanged = true;
}

// выключить систему
void LEDoff() {
  ONflag = false;
  strip.setBrightness(0);
  digitalWrite(PIN_R, 0);
  digitalWrite(PIN_G, 0);
  digitalWrite(PIN_B, 0);
}

void controlTick() {
  // ------------------ КНОПКА -------------------
#if (USE_BTN == 1)
  btn.tick();
  if (btn.isSingle()) {
    if (!firstStartBtn) {
      firstStartBtn = true;
      btnColorChanged = true;
      btnControl = true;
    } else {
      if (ONflag) LEDoff();
      else LEDon();
    }
  }
  if (btn.isDouble()) {
#if (BTN_MODE == 0)
    if (++presetNum >= 10) presetNum = 0;
    changePreset();
#else
    btnControl = true;
    if (++btnColor >= 12) btnColor = 0;
    btnColorChanged = true;
    eeprFlag = true;
    eeprTimer = millis();
#endif
  }
  if (btn.isHolded()) {
    brightDirection = !brightDirection;
  }
  if (btn.isStep()) {
    if (brightDirection) {
      thisBright += 5;
    } else {
      thisBright -= 5;
    }
    thisBright = constrain(thisBright, 0, 255);
    strip.setBrightness(thisBright);
    eeprFlag = true;
    eeprTimer = millis();
  }
#endif
  // ----------------- ИК ПУЛЬТ ------------------
#if (USE_IR == 1)
  if (IRLremote.available()) {
    backlTimer = millis();      // сбросить таймаут дисплея
    if (!backlState) backlOn();
    auto data = IRLremote.read();
    IRdata = data.command;
    if (IRdata != 292984781) {
      switch (IRdata) {
        case BUTT_OK: changeNav();
          break;
        case BUTT_LEFT:
        case BUTT_RIGHT:
          eeprTimer = millis();
          eeprFlag = true;
          switch (navPos) {
            case 0:   // выбор пресета
              if (changeFlag) {
                writeSettings(); // сохраняем текущие настройки
                changeFlag = false;
              }
              if (IRdata == BUTT_RIGHT) {
                incr(&presetNum, 1, 9);    // presetNum +1 огранич 9
              } else if (IRdata == BUTT_LEFT) {
                incr(&presetNum, -1, 9);   // presetNum -1 огранич 0
              }
              changePreset();
              break;
            case 1:   // выбор режима
              if (IRdata == BUTT_RIGHT) {
                incr(&modeNum, 1, 10);    // modeNum +1 огранич 10
              } else if (IRdata == BUTT_LEFT) {
                incr(&modeNum, -1, 10);    // modeNum -1 огранич 0
              }
              changeMode();
              break;
            case 2:   // настройки
              changeFlag = true;
              settingsChanged = true;
              if (IRdata == BUTT_RIGHT) {
                incr(&invSet, 1, setAmount[modeNum] - 1);    // invSet +1 огранич setAmount[modeNum]
              } else if (IRdata == BUTT_LEFT) {
                incr(&invSet, -1, setAmount[modeNum] - 1);    // invSet -1 огранич 0
              }
              break;
          }
          drawSettings();
          break;
        case BUTT_UP:
        case BUTT_DOWN:
          settingsChanged = true;
          eeprTimer = millis();
          eeprFlag = true;
          if (IRdata == BUTT_UP) {
            if (modeNum == 4 && invSet == 1) {
              incr(&presetSettings[invSet], 100, 10000);  // для режима kelvin
            } else if (modeNum == 3 && invSet == 1) {
              incr(&presetSettings[invSet], 1, maxVals[startFrom[modeNum] + invSet]);
            } else {
              incr(&presetSettings[invSet], IR_STEP, maxVals[startFrom[modeNum] + invSet]);
            }
          } else if (IRdata == BUTT_DOWN) {
            if (modeNum == 4 && invSet == 1) {
              incr(&presetSettings[invSet], -100, 10000);   // для режима kelvin
            } else if (modeNum == 3 && invSet == 1) {
              incr(&presetSettings[invSet], -1, maxVals[startFrom[modeNum] + invSet]);
            } else {
              incr(&presetSettings[invSet], -IR_STEP, maxVals[startFrom[modeNum] + invSet]);
            }
          }
          drawSettings();
          break;
        case BUTT_HASH:
          LEDoff();
          break;
        case BUTT_STAR:
          LEDon();
          break;
        case BUTT_0: changePresetTo(0);
          break;
        case BUTT_1: changePresetTo(1);
          break;
        case BUTT_2: changePresetTo(2);
          break;
        case BUTT_3: changePresetTo(3);
          break;
        case BUTT_4: changePresetTo(4);
          break;
        case BUTT_5: changePresetTo(5);
          break;
        case BUTT_6: changePresetTo(6);
          break;
        case BUTT_7: changePresetTo(7);
          break;
        case BUTT_8: changePresetTo(8);
          break;
        case BUTT_9: changePresetTo(9);
          break;
      }
    }
  }
#endif

#if (USE_ENC == 1)
  // ------------------ ЭНКОДЕР ------------------
  enc.tick();       // опрос энкодера

  if (enc.isClick()) {
    if (backlState) {
      backlTimer = millis();      // сбросить таймаут дисплея
      changeNav();
    } else {
      backlOn();      // включить дисплей
    }
  }
  if (enc.isHolded()) {
    if (backlState) {
      backlTimer = millis();      // сбросить таймаут дисплея
      toggleFlag = !toggleFlag;
      if (toggleFlag) LEDoff();
      else LEDon();
    } else {
      backlOn();      // включить дисплей
    }
  }

  if (enc.isTurn()) {     // если был совершён поворот
    //Serial.println(invSet);
    if (backlState) {
      backlTimer = millis();      // сбросить таймаут дисплея
      eeprTimer = millis();
      eeprFlag = true;
      switch (navPos) {
        case 0:   // выбор пресета
          if (changeFlag) {
            writeSettings(); // сохраняем текущие настройки
            changeFlag = false;
          }
          if (enc.isRight())
            incr(&presetNum, 1, 9);    // presetNum +1 огранич 9
          if (enc.isLeft())
            incr(&presetNum, -1, 9);   // presetNum -1 огранич 0
          changePreset();
          break;
        case 1:   // выбор режима
          if (enc.isRight())
            incr(&modeNum, 1, 10);    // modeNum +1 огранич 10
          if (enc.isLeft())
            incr(&modeNum, -1, 10);    // modeNum -1 огранич 0
          changeMode();
          break;
        case 2:   // настройки
          changeFlag = true;
          settingsChanged = true;

          if (enc.isRight()) {      // энк вправо - меняем величину+
            if (modeNum == 4 && invSet == 1) {
              incr(&presetSettings[invSet], 100, 10000);    // для режима кельвин
            } else {
              incr(&presetSettings[invSet], 1, maxVals[startFrom[modeNum] + invSet]);
            }
          }

          if (enc.isLeft()) {      // энк влево - меняем величину-
            if (modeNum == 4 && invSet == 1) {
              incr(&presetSettings[invSet], -100, maxVals[startFrom[modeNum] + invSet]);
            } else {
              incr(&presetSettings[invSet], -1, maxVals[startFrom[modeNum] + invSet]);
            }
          }

          if (enc.isFastR() && !(modeNum == 4 && invSet == 1)) {    // энк быстро - меняем величину
            incr(&presetSettings[invSet], 10, maxVals[startFrom[modeNum] + invSet]);
          }

          if (enc.isFastL() && !(modeNum == 4 && invSet == 1)) {    // энк быстро - меняем величину
            incr(&presetSettings[invSet], -10, maxVals[startFrom[modeNum] + invSet]);
          }

          if (enc.isRightH()) {   // энк удерживаем и крутим - меняем выбор настройки
            incr(&invSet, 1, setAmount[modeNum] - 1);    // invSet +1 огранич setAmount[modeNum]
          }

          if (enc.isLeftH()) {   // энк удерживаем и крутим - меняем выбор настройки
            incr(&invSet, -1, setAmount[modeNum] - 1);    // invSet -1 огранич 0
          }

          drawSettings();
          break;
      }
    } else {
      backlOn();      // включить дисплей
    }
  }
#endif

  // запись в еепром по таймеру и изменению
  if (eeprFlag && millis() - eeprTimer > EEPR_TIME) {
    eeprFlag = false;
    if (btnControl) {
      btnColorChanged = false;
      eeprom_update_byte(201, btnColor);
      eeprom_update_word(202, thisBright);
    } else {
      eeprom_update_byte(PRESET_ADDR, presetNum);
      writeSettings();
    }
  }
}

// --------------- РАБОТА С EEPROM --------------
void readSettings() {
  modeNum = eeprom_read_byte((uint8_t*)presetNum);
  for (byte i = 0; i < setAmount[modeNum]; i++) {
    presetSettings[i] = eeprom_read_word((uint16_t*)(presetNum * 10 + 10 + i * 2));
  }
}
void writeSettings() {
  eeprom_update_byte(presetNum, modeNum);
  for (byte i = 0; i < setAmount[modeNum]; i++) {
    eeprom_update_word((presetNum * 10 + 10 + i * 2), presetSettings[i]);
  }
}

void eeprom_update_byte(int addr, byte value) {
  byte buf = eeprom_read_byte((uint8_t*)addr);
  if (value != buf) eeprom_write_byte((uint8_t*)addr, value);
}
void eeprom_update_word(int addr, int value) {
  int buf = eeprom_read_word((uint16_t*)addr);
  if (value != buf) eeprom_write_word((uint16_t*)addr, value);
}
