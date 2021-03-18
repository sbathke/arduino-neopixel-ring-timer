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
  
    void off();
    void fill(uint32_t c);
    void setColorClockwise(uint32_t c, uint8_t numberOfLeds);
    void setUp(uint8_t pin, uint8_t brightness);
  private:
    void blink(uint32_t c);
    void drawLedRing();  
};

#endif
