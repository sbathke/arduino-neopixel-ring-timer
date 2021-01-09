#include <Adafruit_NeoPixel.h>
#include "RingLight.h"

#define NUM_LEDS 16
#define DEFAULT_PIN 8
#define BLINK_DURATION 200;
#define OPERATION_TIME 100;

Adafruit_NeoPixel strip;

uint8_t blinkMode = 0;
long _blinkEndTime = 0;
long _counterEndTime = 0;
long _nextOperationTime = 0;

RingLight::RingLight() 
: RingLight(DEFAULT_PIN, 30) 
{}

RingLight::RingLight(uint8_t pin) 
: RingLight(pin, 30) 
{}

RingLight::RingLight(uint8_t pin, uint8_t brightness) {
  setUp(pin, brightness);
}

void RingLight::off() {
  fill(strip.Color(0, 0, 0));
}

void RingLight::fill(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void RingLight::startCountDown(uint16_t timeInSec) {
  off();
  _counterEndTime = millis() + timeInSec * 1000;
  fill(strip.Color(255, 0, 0));
}

void RingLight::stopCountDown() { 
  _counterEndTime = 0;
  _blinkEndTime = 0;
  
  off();
}

void RingLight::blink(uint32_t c) {
  if (0 == _blinkEndTime || millis() >= _blinkEndTime) {
    Serial.println("blink");
    _blinkEndTime = millis() + BLINK_DURATION;
    blinkMode = ~blinkMode;
  }
  
  if (0 == blinkMode) {
    Serial.println("on");
    off();
  } else {
    Serial.println("off");
    fill(c);
  }
}

void RingLight::setColorClockwise(uint32_t c, uint8_t numberOfLeds) {
  for(uint16_t i=0; i< numberOfLeds; i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}

void RingLight::drawLedRing() {
  if (0 <= _counterEndTime) {  /* draw count down */
    if (millis() >= _counterEndTime) { /* start blinking, if count down has finished */
      blink(strip.Color(255, 0, 0));
      return;
    }
    Serial.println("drawCountDown");
    float numberLedsToLight = millis() * NUM_LEDS / _counterEndTime; /* draw count down */
    if (0 <= numberLedsToLight) {
      setColorClockwise(strip.Color(0, 0, 0), numberLedsToLight);
    }
  }
}

void RingLight::operate() { 
  if (millis() <= _nextOperationTime) {
  	return;
  }
  drawLedRing();
  _nextOperationTime = millis() + OPERATION_TIME;
}

void RingLight::setUp(uint8_t pin, uint8_t brightness) {
  strip = Adafruit_NeoPixel(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}
