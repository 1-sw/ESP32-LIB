#include <Arduino.h>
#include <SimpleLEDS.h>
#define COUNT_OF_LEDS 64


CRGB leds[COUNT_OF_LEDS];


SimpleLEDS simple_leds(leds);

void setup()
{
    uint8_t ROOT = NULL;
    simple_leds.restart(leds);
    simple_leds.clear_all(leds);
}


void loop()
{
  srand(time(NULL));
  uint8_t R = rand()%255;
  uint8_t G = rand()%255;
  uint8_t B = rand()%255;
  simple_leds.make_circle(leds,R,G,B);
}
