// эффекты

byte thisBrightness;
int thisColor;
boolean strobeFlag;
float k = 0.25;
int val, rndVal;
byte fireBright;
uint32_t prevTime;
byte policeState = 0;

void effectsTick() {
  if (ONflag) {
    if (modeNum < 5) {              // статичные режимы
      if (settingsChanged) {        // по флагу
        settingsChanged = false;
        switch (modeNum) {
          case 0:   // RGB
            strip.setRGB(presetSettings[1], presetSettings[2], presetSettings[3]);
            thisBrightness = presetSettings[0];
            break;
          case 1:   // HSV
            strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
            thisBrightness = 255;
            break;
          case 2:   // Color
            strip.colorWheel(presetSettings[1]);
            thisBrightness = presetSettings[0];
            break;
          case 3:   // ColorSet
            strip.setHEX(colorVals[presetSettings[1]]);
            thisBrightness = presetSettings[0];
            break;
          case 4:   // Kelvin
            strip.setKelvin(presetSettings[1]);
            thisBrightness = presetSettings[0];
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
            break;
          case 6:   // Fire
            effPeriod = 40;
            fireTick();
            break;
          case 7:   // FireManual
            effPeriod = 40;
            fireM_tick();
            break;
          case 8:   // Strobe
            effPeriod = presetSettings[3];
            strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
            strobeFlag = !strobeFlag;
            strip.setBrightness(255 * strobeFlag);
            break;
          case 9:   // RndStrobe
            effPeriod = random(presetSettings[3]);
            strip.setHSV(presetSettings[0], presetSettings[1], presetSettings[2]);
            strobeFlag = !strobeFlag;
            strip.setBrightness(255 * strobeFlag);
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
            effPeriod = presetSettings[1];
            strip.setBrightness(presetSettings[0]);
            break;
        }
      }
    }
  }
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
