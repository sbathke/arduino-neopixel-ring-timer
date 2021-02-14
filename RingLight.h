#ifndef RingLight_h
#define RingLight_h

#include <Arduino.h>

class RingLight
{
  public:
    RingLight();
    RingLight(uint8_t pin);
    RingLight(uint8_t pin, uint8_t brightness);
    void startCountDown(uint16_t timeInSec);
    void stopCountDown(); 
    void operate();
  private:
    void blink(uint32_t c);
    void setColorClockwise(uint32_t c, uint8_t numberOfLeds);
    void drawLedRing();  
    void setUp(uint8_t pin, uint8_t brightness);
    void off();
    void fill(uint32_t c);
};

#endif
