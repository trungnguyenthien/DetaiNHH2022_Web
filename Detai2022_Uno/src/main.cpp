#include <Arduino.h>
#include "Module3461BS_1.h"
#include "Esp8266_HTTPS.h"
#include "MyUtils.h"

Esp8266_HTTPS client = Esp8266_HTTPS();
Module3461BS_1 led = Module3461BS_1(D2, D3, D4);

int t = 0;
int currentNum = 0;

void setup()
{
  currentNum = random(20, 30);
  Serial.begin(115200);
  led.setup();
  // client.setup("Trung Thao", "rongcon1988");
}

void loop()
{
  t += 1;
  t = t % 1000;
  if (t != 1)
  {
    led.displayNumber(currentNum);
    return;
  }

  currentNum += 1;
  led.displayNumber(currentNum);

  // char path[500];
  // snprintf(path, 500, "/number/post.php?number=%d", currentNum);
  // client.get(false, "http://dauden.cloud", path);
}
