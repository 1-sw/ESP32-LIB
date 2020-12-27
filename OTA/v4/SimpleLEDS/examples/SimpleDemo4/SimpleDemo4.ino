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
    simple_leds.test_all_by_random(leds);
}
