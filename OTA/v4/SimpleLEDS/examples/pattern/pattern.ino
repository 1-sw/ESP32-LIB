#include <Arduino.h>
#include <SimpleLEDS.h>

// Тут должно быть ваше количество лед-светодидов
// В моем случае - это матрица 8*8, итого 64
#define COUNT_OF_LEDS 64

// Обьявление глобального массива светодидов.
CRGB leds[COUNT_OF_LEDS];

// Создадим обьект на основе глобального массива
// Через этот обьект мы сможем менять состояние
// лед-ленты / матрицы
SimpleLEDS simple_leds(leds);

void setup()
{
    simple_leds.restart(leds);
    simple_leds.clear_all(leds);
    delay(50);
}


void loop()
{
    // НАЧНИТЕ СОЗДАВАТЬ ВАШУ ДЕМО ПРЯМ ТУТ:
    // ... ... код ... ...
}
