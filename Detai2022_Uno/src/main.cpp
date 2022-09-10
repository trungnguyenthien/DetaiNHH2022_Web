#include <Arduino.h>
#include "Module3461BS_1.h"
#include "Esp8266_HTTPS.h"

Esp8266_HTTPS client = Esp8266_HTTPS();
Module3461BS_1 led = Module3461BS_1(D2, D3, D4);

void setup()
{
  Serial.begin(115200);
  // led.setup();
  client.setup("Trung Thao", "rongcon1988");
}

void loop()
{
  // static int count = 0;
  // count = (count + 1) % 10000;
  // led.displayNumber(count);

  client.sendGet("https://raw.githubusercontent.com","/trungnguyenthien/DetaiNHH2022_Web/main/Detai2022_Uno/platformio.ini");
  delay(1000);
}
