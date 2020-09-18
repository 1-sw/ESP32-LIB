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
}



void loop()
{
// ПРОСТЫЕ МЕТОДЫ
///*[1]*/simple_leds.show_all_colors(leds);
///*[2]*/simple_leds.test_all_by_random(leds);
///*[4]*/simple_leds.fill_all_slow(leds,111,111,111);
///*[3]*/simple_leds.clear_all_slow(leds);
///*[5]*/simple_leds.fill_all(leds,222,222,222);
///*[6]*/simple_leds.clear_all(leds);


// МЕТОДЫ С РАСШИРЕННЫМ ФУНКЦИОНАЛОМ
///*[1]*/simple_leds.fill_advanced(leds,8,40,123,123,123);
///*[2]*/simple_leds.fill_one_led(leds,0,0,255,255,255);
///*[3]*/simple_leds.convert_led_index(5,5);
///*[4]*/simple_leds.DRAW_ONCE_WITH_BLOCKED_AREA(leds,0,64,8,16,123,123,123);
///*[5]*/simple_leds.fast_advanced_blinking(leds,0,64,321,321,321,123,123,123);
///*[6]*/simple_leds.nervous_blinking(leds,255,255,255);

// МЕТОДЫ ДЛЯ КОНФИГУРИРОВАНИЯ ФАСТ-ЛЕД БИБЛИОТЕКИ
///*[1]*/simple_leds.simple_leds.restart(leds);
///*[2]*/simple_leds.simple_leds.clear_all(leds);
///*[3]*/SimpleLEDS simple_leds(leds);
}
