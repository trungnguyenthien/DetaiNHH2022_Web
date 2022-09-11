#include <Arduino.h>
#include "Module3461BS_1.h"
#include "Esp8266_HTTPS.h"
#include "MyUtils.h"

Esp8266_HTTPS client = Esp8266_HTTPS();
Module3461BS_1 led = Module3461BS_1(D2, D3, D4);

String pathToPostCurrentNum()
{
  String path = "/number/post.php?number=";
  return path + number();
}

void setup()
{
  Serial.begin(115200);
  led.setup();
  client.setup("NTRUNG.A71", "77889900");
  // client.setup("HAI TEE COFFEE (Free)", "");
}

void loop()
{
  if (skip())
  {
    led.displayNumber(number());
    return;
  }

  led.displayNumber(number(true)); 

  String path = pathToPostCurrentNum();
  client.get(false, "http://dauden.cloud", path);
}
