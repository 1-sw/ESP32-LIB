#ifndef SimpleLEDS_h
#define SimpleLEDS_h
#include "Arduino.h"
#include "FastLED.h"
#include <WiFi.h>
#include <Update.h>
#define PIN 33
#define COUNT_OF_LEDS 64



class SimpleLEDS
{
public:

    bool WRITEBLE_MODE;
    int active_leds[];
	int BANNED_LEDS[];
	
    SimpleLEDS(CRGB arg_leds[COUNT_OF_LEDS]);
    void restart(CRGB arg_leds[COUNT_OF_LEDS]);
    void test_all_by_random(CRGB arg_leds[COUNT_OF_LEDS]);
    void clear_all_slow(CRGB arg_leds[COUNT_OF_LEDS]);
    void clear_all(CRGB arg_leds[COUNT_OF_LEDS]);
    void fill_all_slow
	(
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t R,uint8_t G,uint8_t B
    );
    void fill_all
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t R,uint8_t G,uint8_t B
    );
	void show_all_colors(CRGB arg_leds[COUNT_OF_LEDS]);
    void nervous_blinking
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t R,uint8_t G,uint8_t B
    );
    void fill_advanced
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t START_LED, uint8_t END_LED,
        uint8_t R,uint8_t G,uint8_t B
    );
    void fill_one_led
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t INDEX,uint8_t DELAY_TIME,
        uint8_t R,uint8_t G,uint8_t B
    );
    uint8_t convert_led_index
    (
        uint8_t NUM_OF_LED, uint8_t NUM_OF_ROW
    );
    void DRAW_ONCE_WITH_BLOCKED_AREA
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t FROM, uint8_t TO,
        uint8_t BLOCK_FROM, uint8_t BLOCK_TO,
        uint8_t R,uint8_t G,uint8_t B
    );
    void fast_advanced_blinking
    (
        CRGB arg_leds[COUNT_OF_LEDS],
        uint8_t FROM_LED, uint8_t TO_LED,
        uint8_t R,uint8_t G,uint8_t B,
        uint8_t r,uint8_t g,uint8_t b
    );
    void fill_all_active_leds
    (
        CRGB arg_all_leds[COUNT_OF_LEDS],uint8_t arg_active_leds[],
        uint8_t R,uint8_t G,uint8_t B
    );
    void make_circle(CRGB arg_leds[COUNT_OF_LEDS],uint8_t R,uint8_t G,uint8_t B);
	void fill_chunk_advanced
	(
		CRGB arg_leds[COUNT_OF_LEDS],
		uint8_t LED_FROM, uint8_t LED_TO,
		uint8_t R,uint8_t G,uint8_t B
	);

    ///////////////////////NEW!!!
    void SetupOTA
    (    
        const char* SSID,
        const char* PSWD,
        String host,
        int port,
        String bin
    );
    String getHeaderValue(String header, String headerName);    
    void execOTA(    
        const char* SSID,
        const char* PSWD,
        String host,
        int port,
        String bin
    );
    ///////////////////////
};

#endif
