#define PIN 6
#define NUM_LEDS 8
#include "Adafruit_NeoPixel.h"
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#include "IRLremote.h"
#define pinIR 2
CHashIR IRLremote;

#include "GyverHacks.h"
GTimer myTimer;

byte i;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Startup"));
  if (!IRLremote.begin(pinIR))
    Serial.println(F("You did not choose a valid pin."));

  strip.begin();
  strip.setBrightness(50);

  myTimer.setInterval(5);
}

void loop() {
  if (myTimer.isReady()) {
    if (++i >= NUM_LEDS) i = 0;
    strip.clear();
    strip.setPixelColor(i, 0xffffff);
    if (!IRLremote.receiving()) {
      strip.show();
    }
  }

  if (IRLremote.available())  {
    auto data = IRLremote.read();
    Serial.println(data.command, HEX);
  }
}
