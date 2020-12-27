
#ifndef QudiOTA_h
#define QudiOTA_h
#include "Arduino.h"
#include "Update.h"
#include "WiFi.h"   


class QudiOTA
{
    public:
        WiFiClient client;
        long contentLength;
        bool isValidContentType;
        const char* SSID;
        const char* PSWD;
        String host;
        int port;
        String bin;
    void init();
}

#endif