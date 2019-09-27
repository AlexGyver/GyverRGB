#if (USE_BT == 1)
#define PARSE_AMOUNT 8    // максимальное количество значений в массиве, который хотим получить
#define header '$'        // стартовый символ
#define divider ','       // разделительный символ
#define ending ';'        // завершающий символ
int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
String request = "1234567891011121314151617181920";
boolean getStarted;
byte index;
String string_convert = "";

void sendSettings() {
  request = "";
  request += String("GS ");
  request += String(presetNum + 1);
  request += String(" ");
  request += String(modeNum + 1);
  request += String(" "); // +1 т.к. счёт в тункабл начинает с 1
  for (byte i = 0; i < 5; i++) {
    request += String(presetSettings[i]);
    request += String(" ");
  }
  request += ONflag;
  btSerial.print(request);
}

void bluetoothTick() {
  parsing();               // функция парсинга
  if (recievedFlag) {     // если получены данные
    recievedFlag = false;
    /*for (byte i = 0; i < 7; i++) {
      Serial.print(intData[i]);
      Serial.print(" ");
      } Serial.println(" ");*/
    switch (intData[0]) {
      case 0:   // запрос онлайна
        request = "OK ";
        request += String(batPerc);
        btSerial.print(request);
        break;
      case 1:   // запрос состояния (настройки, пресет)
        sendSettings();
        btnControl = false;
        break;
      case 2:   // применить настройки
        for (byte i = 0; i < 6; i++) {
          presetSettings[i] = intData[i + 1];
        }
        presetSettings[setAmount[modeNum] - 1] = intData[6]; // белый
        settingsChanged = true;
        
        if (intData[7] != 10) invSet = intData[7];
        else invSet = setAmount[modeNum] - 1; // ой костыли бл*ть
        navPos = 2;
        invFlag = true;
        drawSettings();
        changeFlag = true;
        btnControl = false;
        break;
      case 3:   // смена пресета
        changePresetTo(intData[1]);
        sendSettings();
        btnControl = false;
        break;
      case 4:   // смена режима
        modeNum = intData[1];
        changeMode();
        sendSettings();
        btnControl = false;
        break;
      case 5:   // вкл/выкл
        if (intData[1]) LEDon();
        else LEDoff();
        btnControl = false;
        break;
    }
  }
}

void parsing() {
  if (btSerial.available() > 0) {
    char incomingByte = btSerial.read();      // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != divider && incomingByte != ending) {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        intData[index] = string_convert.toInt();  // преобразуем строку в int и кладём в массив
        string_convert = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == header) {             // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ending) {             // если таки приняли ; - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}
#else
void bluetoothTick() {}
#endif
