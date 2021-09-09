![PROJECT_PHOTO](https://github.com/AlexGyver/GyverRGB/blob/master/proj_img.jpg)
# Контроллер для RGB светодиодных лент на Arduino
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Многофункциональный контроллер для RGB светодиодов, с кучей режимов и органов управления
Страница проекта на сайте: https://alexgyver.ru/GyverRGB/  
   
#### Особенности:
- Управление 4-х пиновой RGB светодиодной лентой (R G B +12)
- Частота ШИМ 8 или 31 кГц (настраивается)
- 10 настраиваемых пресетов, в каждом настраивается режим и настройки выбранного режима
- 11 режимов работы: 5 статичных и 6 динамичных
- Управление с энкодера, ИК пульта или bluetooth (приложение GyverRGB)
- Вывод меню на OLED дисплей
- Мониторинг напряжения аккумулятора и вывод на дисплей в процентах/Вольтах
- Полную информацию смотри в документации

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки для Arduino
- **schemes** - схемы подключения компонентов
- **docs** - документация
- **utility** - вспомогательные программы и прошивки

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/GyverRGB/blob/master/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/GyverRGB/blob/master/schemes/scheme2.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
Первые ссылки - в основном магазин Great Wall, вторые - WAVGAT. Покупая в одном магазине, вы экономите на доставке!
Мосфеты и резисторы можно купить в любом магазине электронных компонентов (ChipDip итд)
- Arduino NANO 328p https://ali.ski/v47nz5  https://ali.ski/uKLTxu
- Лента Али RGB 120 https://ali.ski/sZYUse  https://ali.ski/QCakdN
- Лента Giant4 https://giant4.ru/5050-120.html

Управление
- Bluetooth HC-06 DIP https://ali.ski/TiJ7J  https://ali.ski/GdIZlM
- Энкодер https://ali.ski/mimIQ  https://ali.ski/7Dq9v
- ИК пульт https://ali.ski/y7ifZ  https://ali.ski/CBL0BY
- ИК приёмники отдельные https://ali.ski/7l8um  https://ali.ski/EhTsq
- Дисплей https://ali.ski/BjGHEP  https://ali.ski/SnNe9

Драйвер
- LED amplifier https://ali.ski/M336P  https://ali.ski/4MB-u5  https://ali.ski/GEz-7T
- MOSFET IRF3205 (10 шт) https://ali.ski/BY7Hg  https://ali.ski/icUjJZ
- Резисторы (100R и 10k) https://ali.ski/DIk1pS  https://ali.ski/L2Cik4

Прочее
- Макетная плата https://ali.ski/d9D7M
- Трубы http://energoplast.ru/

Питание
- БП 12V (1.5A на каждые 100 диодов) https://ali.ski/iBEE7f  https://ali.ski/FtBcl
- Гнездо 5.5x2.1 https://ali.ski/zouaE  https://ali.ski/Xa9DM
- Гнездо на плату https://ali.ski/n9Ncpx  https://ali.ski/XXMPh3
- Выключатель 16мм https://ali.ski/ZXK9GL  https://ali.ski/NVyxV

Автономное питание
- Аккумуляторы https://ali.ski/4zw95s  https://ali.ski/vzROL6
- Батарейный отсек https://ali.ski/DggxO  https://ali.ski/-4xY62  https://ali.ski/If4-Z
- BMS 3S баланс https://ali.ski/2RgKJ  https://ali.ski/0vX3L
- Вольтметр - резисторы 10k и 4.7k https://ali.ski/DIk1pS  https://ali.ski/L2Cik4

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    // ------ Дисплей ------
    LCD_BACKL 1         // автоотключение подсветки дисплея (1 - разрешить) 
    BACKL_TOUT 60       // таймаут неактивности отключения дисплея, секунды
    CONTRAST 150        // контрастность (яркость) дисплея 0-255
    ROTATE_DISP 1       // 0 или 1 - повернуть дисплей на 180 градусов
    I2C_ADDRESS 0x3C    // адрес дисплея
    // примерно на 200 строке можно поменять шрифт дисплея

    // ------ Драйвер ------
    HIGH_FREQUENCY 2    // 0 - 490 Гц, 1 - 7.8 кГц, 2 - 31.4 кГц, 3 - ручная настройка
    PWM_FREQUENCY 15000 // частота ШИМ на настройке №3, Герц
    DRIVER_DIRECTION 0  // 0 - обычный (мосфеты), 1 - реверс (LED amplifier)

    // ------ Лента ------
    MAX_CURRENT 0       // макс. ток в мА, при значении 0 фича не активируется
    NUM_LEDS 60         // кол-во светодиодов для расчёта ограничения тока (только для диодов 5050!!!)
    SMOOTH_K 0.25       // коэффициент плавности огня

    // ------ Bluetooth ------
    USE_BT 0            // 1 - использовать Bluetooth, 0 - нет

    // ------ ИК пульт ------
    USE_IR 1            // 1 - использовать ИК пульт, 0 - нет
    IR_STEP 10          // шаг изменения настроек с пульта

    // ------ Энкодер ------
    USE_ENC 1           // 1 - использовать энкодер, 0 - нет
    ENC_REVERSE 1       // 1 - инвертировать направление энкодера
    ENC_TYPE 1          // 0 или 1 - тип энкодера

    // ------ Напряжение ------
    VOLTMETER 0         // 0 или 1 - вкл/выкл вольтметр (делитель напряжения в пин А0)
    CHARGE_VAL 1        // вывод напряжения: 0 - в процентах, 1 - в вольтах
    CONSTANT_BRIGHT 0   // 0 или 1 - вкл/выкл поддержание яркости при разрядке АКБ (только для диодов 5050!!!) (в схеме должен стоять делитель)
    VREF 5.1            // напряжение на пине 5V
    R1 10010            // точное значение 10 кОм
    R2 4700             // точное значение 4.7 кОм
	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)