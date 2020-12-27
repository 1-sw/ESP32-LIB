#include "Arduino.h"
#include "FastLED.h"
#include "SimpleLEDS.h"
#include <WiFi.h>
#include <Update.h>

#define PIN 33
#define COUNT_OF_LEDS 64


SimpleLEDS::SimpleLEDS(CRGB arg_leds[COUNT_OF_LEDS])
{
    pinMode(PIN, OUTPUT);
}
void SimpleLEDS::restart(CRGB arg_leds[COUNT_OF_LEDS])
{
    FastLED.addLeds<NEOPIXEL, PIN>(arg_leds, COUNT_OF_LEDS);
}

void SimpleLEDS::test_all_by_random(CRGB arg_leds[COUNT_OF_LEDS])
{
    for(uint8_t led = 0; led < COUNT_OF_LEDS; led++ )
    {
        arg_leds[ led ] = CHSV(rand()%255,rand()%255,rand()%255);
        FastLED.delay(50);
        arg_leds[ led ] = CHSV(0,0,0);
    }
}
void SimpleLEDS::clear_all_slow(CRGB arg_leds[COUNT_OF_LEDS])
{
    for(uint8_t led = 0; led < COUNT_OF_LEDS; led++ )
    {
        FastLED.delay(10);
        arg_leds[ led ] = CHSV(0,0,0);
    }
}

void SimpleLEDS::clear_all(CRGB arg_leds[COUNT_OF_LEDS])
{
    for(uint8_t led = 0; led < COUNT_OF_LEDS; led++ )
    {
        FastLED.delay(0);
        arg_leds[ led ] = CHSV(0,0,0);
    }
}

void SimpleLEDS::fill_all_slow
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t R,uint8_t G,uint8_t B
    ){
    for(uint8_t led = 0; led < COUNT_OF_LEDS; led++ )
    {
        FastLED.delay(10);
        arg_leds[ led ] = CHSV(R,G,B);
    }
}

void SimpleLEDS::fill_all
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t R,uint8_t G,uint8_t B
    ){
    for(uint8_t led = 0; led < COUNT_OF_LEDS; led++ )
    {
        FastLED.delay(0);
        arg_leds[ led ] = CHSV(R,G,B);
    }
}

void SimpleLEDS::nervous_blinking
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t R,uint8_t G,uint8_t B
    ){
    SimpleLEDS::fill_all(arg_leds,R,G,B);
    delay(1);
    SimpleLEDS::clear_all(arg_leds);
}

void SimpleLEDS::fast_advanced_blinking
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t FROM_LED, uint8_t TO_LED,
    uint8_t R,uint8_t G,uint8_t B,
    uint8_t r,uint8_t g,uint8_t b
    ){
    for(uint8_t led=FROM_LED; led<TO_LED; led++)
    {
        SimpleLEDS::fill_advanced(arg_leds,FROM_LED,TO_LED,R, G, B);
        SimpleLEDS::fill_advanced(arg_leds,FROM_LED,TO_LED,r,g,b);
    }
}

void SimpleLEDS::show_all_colors
(
    CRGB arg_leds[COUNT_OF_LEDS]
    ){
    int color = 0;
    do
    {
       for(;color < 255; color+=5)
       {
           SimpleLEDS::fill_all(arg_leds,color, color, color);
           FastLED.delay(0);
       }
    } while( color != 255 );
    for(;color >= 0; color-=5)
    {
        SimpleLEDS::fill_all(arg_leds,color, color, color);
        FastLED.delay(0);
    }
}



void SimpleLEDS::fill_advanced
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t START_LED, uint8_t END_LED,
    uint8_t R,uint8_t G,uint8_t B
    ){
    for(;START_LED < END_LED; START_LED++)
    {
        arg_leds[ START_LED ] = CHSV(R, G, B);
        FastLED.delay(0);
    }
}

uint8_t SimpleLEDS::convert_led_index(uint8_t NUM_OF_LED, uint8_t NUM_OF_ROW)
{
    return (NUM_OF_ROW * 8) + (NUM_OF_LED - 8);
}
void SimpleLEDS::DRAW_ONCE_WITH_BLOCKED_AREA
(
    CRGB arg_leds[COUNT_OF_LEDS],
    uint8_t LED_FROM, uint8_t LED_TO,
    uint8_t BLOCK_LED_FROM, uint8_t BLOCK_LED_TO,
    uint8_t R,uint8_t G,uint8_t B
    ){

    SimpleLEDS::WRITEBLE_MODE = true;
    SimpleLEDS::fill_advanced(arg_leds, LED_FROM, LED_TO, R, G, B);


    SimpleLEDS::fill_advanced
    (
        arg_leds,
        BLOCK_LED_FROM,BLOCK_LED_TO,
        0,0,0
    );
    SimpleLEDS::WRITEBLE_MODE = false;
}

void SimpleLEDS::fill_one_led
(
    CRGB arg_leds[COUNT_OF_LEDS],
	
    uint8_t INDEX,uint8_t DELAY_TIME,
    uint8_t R,uint8_t G,uint8_t B
    ){

    arg_leds[INDEX] = CHSV(R, G, B);
    FastLED.delay(DELAY_TIME);
}


void SimpleLEDS::fill_all_active_leds
(
    CRGB arg_all_leds[COUNT_OF_LEDS],
    uint8_t arg_active_leds[],
    uint8_t R,uint8_t G,uint8_t B

){
    uint8_t len = sizeof(arg_active_leds) / sizeof(arg_active_leds[0]);
    for(uint8_t led = 0; led < len; led++)
    {
        SimpleLEDS::fill_one_led(arg_all_leds,arg_active_leds[led],0,R,G,B);
    }
}

	
void SimpleLEDS::make_circle(CRGB arg_leds[COUNT_OF_LEDS],uint8_t R,uint8_t G,uint8_t B)
{
    uint8_t row1[] = {1,2,3,4};
    uint8_t row2[] = {5,6,8,15};
    uint8_t row3[] = {8+8,15+8,8+16,15+16};
    uint8_t row4[] = {8+16,15+16,8+24,15+24};
    uint8_t row5[] = {8+24,15+24,8+32,15+32};
    uint8_t row6[] = {8+32,15+32,8+40,15+40};
    uint8_t row7[] = {57,58,59,60};
    uint8_t row8[] = {61,62,62,62};

    SimpleLEDS::fill_all_active_leds(arg_leds,row1,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row2,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row3,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row4,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row5,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row6,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row7,R,G,B);
    SimpleLEDS::fill_all_active_leds(arg_leds,row8,R,G,B);

}


void SimpleLEDS::SetupOTA(
    const char* SSID,
    const char* PSWD,
    String host,
    int port,
    String bin,
    WiFiClient client,                                                 
    long contentLength,                                          
    bool isValidContentType
    ){
      Serial.begin(115200);
      delay(10);
      Serial.println("Connecting to " + String(SSID));
      WiFi.begin(SSID, PSWD);
      while (WiFi.status() != WL_CONNECTED)
      {
          delay(500);
      }                               
}








String SimpleLEDS::getHeaderValue(String header, String headerName)
{                                                                     
    return header.substring(strlen(headerName.c_str()));              
}        


void SimpleLEDS::execOTA(    
    const char* SSID,
    const char* PSWD,
    String host,
    int port,
    String bin,
    WiFiClient client,                                                 
    long contentLength,                                          
    bool isValidContentType
  ){                                                          //Вся логика                                                                         //              Часть 1
  Serial.println("Connecting to: " + String(host));                       //Выводим сообщение о попытке подключиться
  if (client.connect(host.c_str(), port))                                 //Проверяем, подключается ли плата к S3 хранилищу
  {                                                                       //
    Serial.println("Fetching Bin: " + String(bin));                       //Выводим сообщение о том, что был достигнут файл с прошивкой
    client.print(String("GET ") + bin + " HTTP/1.1\r\n" +                 //Получаем содержимое файла с прошивкой
                 "Host: " + host + "\r\n" +                               //Гет запросом по ссылке сохраненной выше
                 "Cache-Control: no-cache\r\n" +                          //
                 "Connection: close\r\n\r\n");                            //
    unsigned long timeout = millis();                                     //Извлекаем время работы платы
    while (client.available() == 0)                                       //Пока клиент не активен
    {                                                                     //
      if (millis() - timeout > 5000)                                      //Проверим сколько времени прошло
      {                                                                   //
          Serial.println("Client Timeout !");                             //Оповестим о том, что время вышло 
          client.stop();                                                  //Остановим соединение 
          return;                                                         //
      }                                                                   //
    }                                                                     //Пока клиент активен
    while (client.available())                                            //(Тут обработка возможных вариантов HTTP-ответов)
    {                                                                     //
      String line = client.readStringUntil('\n');                         //Читаем http ответ по строчно
      line.trim();                                                        //переходим на следующую строку в случае \n
      if (!line.length())                                                 //Если (line.length() = 0(false) + not )=== true , то
      {                                                                   //
        break;                                                            //выйти из цикла
      }                                                                   //
      if (line.startsWith("HTTP/1.1"))                                    //Обработка пустого ответа:
      {                                                                   //
        if (line.indexOf("200") < 0)                                      //
        {                                                                 //
          Serial.println("Got a non 200 status code from server. Exiting  OTA Update.");
          break;                                                          //
        }                                                                 //
      }                                                                   //
      if (line.startsWith("Content-Length: "))                            //
      {                                                                   //
        contentLength = atol((getHeaderValue(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }                                                                   //
                                                                          //
      if (line.startsWith("Content-Type: "))                              //В ответе идет описание содержимого
      {                                                                   //
        String contentType = getHeaderValue(line, "Content-Type: ");      //Достаем значение заголовка с помощью ф-ции выше
        Serial.println("Got " + contentType + " payload.");               //
        if (contentType == "application/octet-stream")                    //Если тип контента, когда это файл некоторого расширения
        {                                                                 //
          isValidContentType = true;                                      //контент корректный (прошивка)
        }                                                                 //
      }                                                                   //
    }                                                                     //
  } else {                                                                //
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
  }                                                                       //
  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));
                                                                          //
  if (contentLength && isValidContentType)                                //не 0 и контент - прошивка
  {                                                                       //
    bool canBegin = Update.begin(contentLength);                          //запишем результат проверки на возможность обновления
    if (canBegin)                                                         //если можно, начинаем и оповещаем:
    {                                                                     //
      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
      size_t written = Update.writeStream(client);                        //уже записано
      if (written == contentLength)                                       //елсли то, что записали = размеру полученного контента,то
      {                                                                   //
        Serial.println("Written : " + String(written) + " successfully"); //оповещаем об успешной записи
      } else {                                                            //иначе, записано всего:
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
      }                                                                   //
                                                                          //
      if (Update.end())                                                   //закончили обновление
      {                                                                   //
        Serial.println("OTA done!");                                      //проверка: успешно или нет
        if (Update.isFinished())                                          //
        {                                                                 //
          Serial.println("Update successfully completed. Rebooting.");    //
          ESP.restart();                                                  //перезапуск с новой прошивкой
        } else {                                                          //
          Serial.println("Update not finished? Something went wrong!");   //
        }                                                                 //
      } else {                                                            //
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
      }                                                                   //
    } else {                                                              //
      Serial.println("Not enough space to begin OTA");                    //места нет
      client.flush();                                                     //
    }                                                                     //
  } else {                                                                //
    Serial.println("There was no content in the response");               //прошивки нет
    client.flush();                                                       //
  }                                                                       //
}   