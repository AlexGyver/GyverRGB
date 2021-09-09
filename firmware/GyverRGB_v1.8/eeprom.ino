// --------------- РАБОТА С EEPROM --------------
void readSettings() {
  modeNum = eeprom_read_byte((uint8_t*)presetNum);
  for (byte i = 0; i < setAmount[modeNum]; i++) {
    presetSettings[i] = eeprom_read_word((uint16_t*)(presetNum * 10 + PRESET_START + i * 2));
  }
}
void writeSettings() {
  EEPROM_UPD_BYTE(presetNum, modeNum);
  for (byte i = 0; i < setAmount[modeNum]; i++) {
    EEPROM_UPD_WORD((presetNum * 10 + PRESET_START + i * 2), presetSettings[i]);
  }
}
