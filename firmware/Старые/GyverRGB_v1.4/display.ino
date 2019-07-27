// вывод на дисплей

void drawInfo() {   // первая строка (пресет и режим)
#if (USE_OLED == 1)
  oled.clear();
  oled.home();
  oled.print("<");
  if (navPos == 0) oled.setInvertMode(true);
  oled.print("#");
  oled.print(presetNum);
  if (navPos == 0) oled.setInvertMode(false);
  oled.print("> <");
  if (navPos == 1) oled.setInvertMode(true);
  oled.print(modeNames[modeNum]);
  if (navPos == 1) oled.setInvertMode(false);
  oled.print(">");
#endif
#if (VOLTMETER == 1)
  drawBattery();
#endif
}

void drawSettings() { // остальные строки (названия и значения настроек)
#if (USE_OLED == 1)
  byte thisSpace = 128 / setAmount[modeNum];
  for (byte i = 0; i < setAmount[modeNum]; i++) {
    oled.setCursor(i * thisSpace, 2);
    oled.print(labels[startFrom[modeNum] + i]);

    oled.setCursor(i * thisSpace, 3);
    if (invFlag && invSet == i) {
      for (byte j = 0; j < thisSpace / 5; j++) oled.print(" ");
      oled.setInvertMode(true);
    }
    oled.setCursor(i * thisSpace, 3);
    if (modeNum == 3 && i == 1) {
      oled.print(colorNames[presetSettings[i]]);
    } else {
      oled.print(presetSettings[i]);
    }
    if (invFlag && invSet == i) oled.setInvertMode(false);
  }
#endif
}
