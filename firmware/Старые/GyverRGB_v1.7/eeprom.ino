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
