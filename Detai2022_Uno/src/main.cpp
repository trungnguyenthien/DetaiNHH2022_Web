#include <Arduino.h>
#include "Module3461BS_1.h"
#include "Esp8266_HTTPS.h"
#include "MyUtils.h"

Esp8266_HTTPS client = Esp8266_HTTPS();
Module3461BS_1 led = Module3461BS_1(D2, D3, D4);

char *pathToPostCurrentNum()
{
  char *path = new char[500];
  snprintf(path, 500, "/number/post.php?number=%d", number());
  return path;
}

void setup()
{
  Serial.begin(115200);
  led.setup();
  client.setup("Trung Thao", "rongcon1988");
}

void loop()
{
  if (skip())
  {
    led.displayNumber(number());
    return;
  }

  led.displayNumber(number(true));
  client.get(false, "http://dauden.cloud", pathToPostCurrentNum());

  delay(3000);
}
