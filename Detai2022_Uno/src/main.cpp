#include <Arduino.h>
#include "Module3461BS_1.h"
#include <Wire.h>

Module3461BS_1 led = Module3461BS_1(D2, D3, D4);

void setup()
{
  led.setup();
}

void loop()
{
  static int count = 0;
  count = (count + 1) % 10000; 
  led.displayNumber(count);
}
