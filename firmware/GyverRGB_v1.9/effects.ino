// эффекты

byte thisBrightness;
int thisColor;
boolean strobeFlag;
float k = 0.25;
int val, rndVal;
byte fireBright;
uint32_t prevTime;
byte policeState = 0;
bool flashState = false;

void effectsTick() {
  if (ONflag) {
    if (modeNum == 11) {
      if (!digitalRead(FLASH_PIN)) {
        setW(presetSettings[4]);
        strip.setBrightness(255);
        delay(presetSettings[3]);
      }
      strip.setBrightness(0);
      setW(0);
      strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
      return;
    }
    if (btnControl) {
      if (btnColorChanged) {
        btnColorChanged = false;
        strip.setHEX(HEXcolors[btnColor]);
        strip.setBrightness(thisBright);
      }
    } else {
      if (modeNum < 5) {              // статичные режимы
        if (settingsChanged) {        // по флагу
          settingsChanged = false;
          switch (modeNum) {
            case 0:   // RGB
              strip.setRGB(presetSettings[1], presetSettings[2], presetSettings[3]);
              thisBrightness = presetSettings[0];
              setW(presetSettings[4]);
              break;
            case 1:   // HSV
              strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
              thisBrightness = 255;
              setW(presetSettings[3]);
              break;
            case 2:   // Color
              strip.colorWheel(presetSettings[1]);
              thisBrightness = presetSettings[0];
              setW(presetSettings[2]);
              break;
            case 3:   // ColorSet
              strip.setHEX(colorVals[presetSettings[1]]);
              thisBrightness = presetSettings[0];
              setW(presetSettings[2]);
              break;
            case 4:   // Kelvin
              strip.setKelvin(presetSettings[1]);
              thisBrightness = presetSettings[0];
              setW(presetSettings[2]);
              break;
          }
          strip.setBrightness(thisBrightness);
        }
      } else {                                    // динамичные режимы
        if (millis() - effTimer >= effPeriod) {   // по таймеру
          effTimer = millis();
          switch (modeNum) {
            case 5:   // ColorWheel
              effPeriod = presetSettings[1];
              thisColor += presetSettings[2];
              if (thisColor > 1530) thisColor = 0;
              strip.colorWheel(thisColor);
              strip.setBrightness(presetSettings[0]);
              setW(presetSettings[3]);
              break;
            case 6:   // Fire
              effPeriod = 40;
              fireTick();
              setW(0);
              break;
            case 7:   // FireManual
              effPeriod = 40;
              setW(presetSettings[0]);
              fireM_tick();
              break;
            case 8:   // Strobe
              effPeriod = presetSettings[3];
              strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
              strobeFlag = !strobeFlag;
              strip.setBrightness(255 * strobeFlag);
              setW(presetSettings[4]);
              break;
            case 9:   // RndStrobe
              effPeriod = random(presetSettings[3]);
              strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
              strobeFlag = !strobeFlag;
              strip.setBrightness(255 * strobeFlag);
              setW(presetSettings[4]);
              break;
            case 10:   // Police
              if (++policeState >= 8) policeState = 0;
              switch (policeState) {
                case 0: strip.setRGB(0, 0, 0);
                  break;
                case 1: strip.setRGB(255, 0, 0);
                  break;
                case 2: strip.setRGB(0, 0, 0);
                  break;
                case 3: strip.setRGB(255, 0, 0);
                  break;
                case 4: strip.setRGB(0, 0, 0);
                  break;
                case 5: strip.setRGB(0, 0, 255);
                  break;
                case 6: strip.setRGB(0, 0, 0);
                  break;
                case 7: strip.setRGB(0, 0, 255);
                  break;
              }
              setW(0);
              effPeriod = presetSettings[1];
              strip.setBrightness(presetSettings[0]);
              break;
          }
        }
      }
    }
  }
}

void setW(byte val) {
  analogWrite(PIN_W, (float)thisBrightness / 255 * val);
}

void fireTick() {
  if (millis() - prevTime > presetSettings[1]) {
    rndVal = random(2, 13) * 10;
    prevTime = millis();
  }
  val = val * (1 - SMOOTH_K) + rndVal * SMOOTH_K;
  strip.colorWheel(val);
  thisBrightness = map(val, 20, 120, presetSettings[2], presetSettings[0]);
  strip.setBrightness(thisBrightness);
}

void fireM_tick() {
  if (millis() - prevTime > presetSettings[2]) {
    rndVal = random(0, 13) * 10;
    prevTime = millis();
  }
  val = val * (1 - SMOOTH_K) + rndVal * SMOOTH_K;
  thisBrightness = map(val, 0, 120, presetSettings[3], presetSettings[0]);
  strip.colorWheel(presetSettings[1] * 6);
  strip.setBrightness(thisBrightness);
}
