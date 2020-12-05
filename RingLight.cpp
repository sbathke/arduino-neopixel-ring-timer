#include <Adafruit_NeoPixel.h>
#include "RingLight.h"

#define NUM_LEDS 16
#define DEFAULT_PIN 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip;
long _counterStartTime = -1;

RingLight::RingLight() 
: RingLight(DEFAULT_PIN, 30) 
{}

RingLight::RingLight(uint8_t pin) 
: RingLight(pin, 30) 
{}

RingLight::RingLight(uint8_t pin, uint8_t brightness) {
  setUp(pin, brightness);
}

void RingLight::setUp(uint8_t pin, uint8_t brightness) {
  strip = Adafruit_NeoPixel(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}

void RingLight::startCountDown(uint16_t timeInSec) {
  _counterStartTime = millis() + timeInSec * 1000;

  fill(strip.Color(255, 255, 255));
}

void RingLight::run() { 
  if (_counterStartTime <= 0) {
    return;
  }
  if (_counterStartTime <= millis()) {
    blink(strip.Color(255, 0, 0), 5000);
    stop();
    return;
  }

  float numberLedsToLight = millis() * NUM_LEDS / _counterStartTime;
  if (numberLedsToLight > 0) {
    setColorClockwise(strip.Color(0, 0, 0), numberLedsToLight);
  }
}

void RingLight::stop() { 
  _counterStartTime = -1;
  fill(strip.Color(0, 0, 0));
}

void RingLight::blink() {
  blink(strip.Color(255, 0, 0), 5000);
}

// Fill the dots one after the other with a color
void RingLight::blink(uint32_t c, uint16_t howLongInMillis) {
  uint8_t duration = 100; // 50 ms between the blinking
  long currentTime = millis();
  long endTime = currentTime + howLongInMillis;
  while ((currentTime = millis()) <= endTime) {
    fill(c);
    delay(duration);
    off();
    delay(duration);
  }
}

/*
 * resets the color ring to display no color
 */
void RingLight::off() {
  fill(strip.Color(0, 0, 0));
}

// Fill the dots with a color
void RingLight::fill(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}

 
// Fill the dots
void RingLight::setColorClockwise(uint32_t c, uint8_t numberOfLeds) {
  for(uint16_t i=0; i< numberOfLeds; i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}