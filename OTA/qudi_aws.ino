#include <WiFi.h>
#include <Update.h>

//- - - - - - - - - - - - - - - - - - - - - - - - -CONFIG
WiFiClient client;
long contentLength      = 0;
bool isValidContentType = false;
const char* SSID        = "YOUR-SSID";
const char* PSWD        = "YOUR-SSID-PSWD";
String host             = "bucket-name.s3.ap-south-1.amazonaws.com";
int port                = 80;
String bin              = "/sketch-name.ino.bin";

//- - - - - - - - - - - - - - - - - - - - - - - - -CODE

String getHeaderValue(String header, String headerName)
{
    return header.substring(strlen(headerName.c_str()));
}


void execOTA()
{
  Serial.println("Connecting to: " + String(host));
  if (client.connect(host.c_str(), port))
  {
    Serial.println("Fetching Bin: " + String(bin));
    client.print(String("GET ") + bin + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Cache-Control: no-cache\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
          Serial.println("Client Timeout !");
          client.stop();
          return;
      }
    }
    while (client.available())
    {
      String line = client.readStringUntil('\n');
      line.trim();
      if (!line.length())
      {
        break;
      }
      if (line.startsWith("HTTP/1.1")) 
      {
        if (line.indexOf("200") < 0)
        {
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          break;
        }
      }
      if (line.startsWith("Content-Length: "))
      {
        contentLength = atol((getHeaderValue(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      if (line.startsWith("Content-Type: "))
      {
        String contentType = getHeaderValue(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream")
        {
          isValidContentType = true;
        }
      }
    }
  } else {
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
  }

  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  if (contentLength && isValidContentType)
  {
    bool canBegin = Update.begin(contentLength);
    if (canBegin)
    {
      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
      size_t written = Update.writeStream(client);
      if (written == contentLength)
      {
        Serial.println("Written : " + String(written) + " successfully");
      } else {
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
      }

      if (Update.end())
      {
        Serial.println("OTA done!");
        if (Update.isFinished())
        {
          Serial.println("Update successfully completed. Rebooting.");
          ESP.restart();
        } else {
          Serial.println("Update not finished? Something went wrong!");
        }
      } else {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
      }
    } else {
      Serial.println("Not enough space to begin OTA");
      client.flush();
    }
  } else {
    Serial.println("There was no content in the response");
    client.flush();
  }
}

void setup()
{

  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to " + String(SSID));
  WiFi.begin(SSID, PSWD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Connected to " + String(SSID));
  execOTA();
}

void loop()
{

}
