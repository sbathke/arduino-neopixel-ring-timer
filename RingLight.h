#ifndef RingLight_h
#define RingLight_h

#include <Arduino.h>

class RingLight
{
  public:
  	RingLight();
  	RingLight(uint8_t pin);
    RingLight(uint8_t pin, uint8_t brightness);
    void RingLight::startCountDown(uint16_t timeInSec);
    void RingLight::stopCountDown(); 
    void RingLight::operate();
    void RingLight::setUp(uint8_t pin, uint8_t brightness);
  private:
  	void RingLight::blink(uint32_t c);
    void RingLight::setColorClockwise(uint32_t c, uint8_t numberOfLeds);
    void RingLight::drawLedRing();
};

#endif
