#include <FastLED.h>

#define NUM_LEDS 120  // Set this to match the number of LEDs in your strip
#define DATA_PIN 6
#define SERIAL_RATE 115200

CRGB leds[NUM_LEDS];
uint8_t prefix[] = {'A', 'd', 'a'};

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(SERIAL_RATE);
  Serial.print("Ada\n");  // Announce that the controller is ready
}

void loop() {
  for (int i = 0; i < sizeof(prefix); ++i) {
  waitLoop:
    while (!Serial.available());
    if (prefix[i] == Serial.read()) continue;
    i = 0;
    goto waitLoop;
  }

  while (!Serial.available());
  uint8_t hi = Serial.read();
  while (!Serial.available());
  uint8_t lo = Serial.read();
  while (!Serial.available());
  uint8_t chk = Serial.read();

  if (chk == (hi ^ lo ^ 0x55)) {
    Serial.readBytes((char*)leds, NUM_LEDS * 3);
    FastLED.show();
  }
}
