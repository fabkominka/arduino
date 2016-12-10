#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 5
#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  fadeTo(strip.Color(255, 0, 0), 30, 10);
  fadeTo(strip.Color(0, 255, 0), 30, 10);
  fadeTo(strip.Color(0, 0, 255), 30, 10);
  fadeTo(strip.Color(0, 0, 0), 30, 10);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void fadeTo(uint32_t targetColor, uint8_t steps, uint8_t wait) {
  uint32_t currentColor = strip.getPixelColor(0);

  int16_t redDiff = red(targetColor) - red(currentColor);
  int16_t greenDiff = green(targetColor) - green(currentColor);
  int16_t blueDiff = blue(targetColor) - blue(currentColor);

  for (int16_t i = 0 ; i < steps; i++) {
    uint8_t redValue = red(currentColor) + (redDiff * i / steps);
    uint8_t greenValue = green(currentColor) + (greenDiff * i / steps);
    uint8_t blueValue = blue(currentColor) + (blueDiff * i / steps);

    colorWipe(strip.Color(redValue, greenValue, blueValue), wait);
  }
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
