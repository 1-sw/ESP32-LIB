#include <WiFi.h>
#include <Update.h>


/////////////////////////////////////////////////////////////////////////
WiFiClient client;                                                     //обьект для вифи
long contentLength      = 0;                                           //переменная для длинны строки
bool isValidContentType = false;                                       //переменная для условий
const char* SSID        = "YOUR-SSID";                                 //айди  (?)
const char* PSWD        = "YOUR-SSID-PSWD";                            //пароль(?)
String host             = "bucket-name.s3.ap-south-1.amazonaws.com";   //ссылка к файлу
int port                = 80;                                          //порт по которому стучать
String bin              = "/sketch-name.ino.bin";                      //путь-имя прошивки
/////////////////////////////////////////////////////////////////////////



//Функция для извлечения значения заголовков, см. в docs
/////////////////////////////////////////////////////////////////////////
String getHeaderValue(String header, String headerName)                //
{                                                                      //
    return header.substring(strlen(headerName.c_str()));               //
}                                                                      //
/////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
void execOTA()                                                            //Вся логика
{                                                                         //              Часть 1
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
}                                                                         //
////////////////////////////////////////////////////////////////////////////

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
