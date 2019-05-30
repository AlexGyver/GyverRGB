#define NUM_LEDS 8
#include "FastLED.h"
#define PIN 6
CRGB leds[NUM_LEDS];

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

  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);

  myTimer.setInterval(5);
}

void loop() {
  if (myTimer.isReady()) {
    if (++i >= NUM_LEDS) i = 0;
    FastLED.clear();
    leds[i] = CRGB::White;
    if (!IRLremote.receiving()) {
      FastLED.show();
    }
  }

  if (IRLremote.available())  {
    auto data = IRLremote.read();
    Serial.println(data.command, HEX);
  }
}
