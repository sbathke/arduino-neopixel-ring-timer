#ifndef RingLight_h
#define RingLight_h

#include <Arduino.h>

class RingLight
{
  public:
  	RingLight();
  	RingLight(uint8_t pin);
    RingLight(uint8_t pin, uint8_t brightness);
    void startCountDown(uint16_t time);
    void run();
    void stop();
    void blink();
    void blink(uint32_t c, uint16_t howLongInMillis);
    void off();
    void fill(uint32_t c);  
  private:
  	void setUp(uint8_t pin, uint8_t brightness);
    void setColorClockwise(uint32_t c, uint8_t numberOfLeds); 
};

#endif
