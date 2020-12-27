/**
 * Sven's RingLight Example.
 * Displays a countdown and blinks at the end.
 */

#include "RingLight.h"

#define RING_LED_PIN 8

extern RingLight ringLight;

void setup() {
  ringLight = RingLight(RING_LED_PIN);
  //RingLight ringLight(RING_LED_PIN);
  ringLight.stop();
  ringLight.startCountDown(10);
}
 
void loop() {
  ringLight.run();
}
