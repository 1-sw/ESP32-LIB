#include <SimpleLEDS.h>


//DEFAULTS
#define COUNT_OF_LEDS 64
long contentLength = 0;                                  
bool isValidContentType = true;
CRGB leds[COUNT_OF_LEDS];
SimpleLEDS simple_leds(leds);
WiFiClient client;  



//CONFIG
const char* SSIDS  = "SOME_SSID";
const char* PSWD   = "SOME_PSWD";
String host        = "host.host.host";
int port           = 8080;
String bin         = "/path_to_file";  



void setup() 
{
  //PREPARE FOR UPDATING + CONNECTING TO WIFI
  simple_leds.SetupOTA(PSWD,SSIDS,host,port,bin,client,contentLength,isValidContentType);
  //START OVER THE AIR UPDATE
  simple_leds.execOTA(PSWD,SSIDS,host,port,bin,client,contentLength,isValidContentType); 
}




void loop()
{

}
