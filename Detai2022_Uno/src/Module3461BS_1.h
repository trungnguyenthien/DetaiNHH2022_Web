#include <Arduino.h>

/// refer: https://github.com/magiccow/_7seg-display-simple/blob/master/_7seg-display-simple.ino
/// Module: https://i.ebayimg.com/images/g/HwkAAOSwCOJh-9gC/s-l500.jpg
class Module3461BS_1
{
public:
  /// @brief  
  /// @param DS = DIO PIN
  /// @param SH_CP = SCLK PIN 
  /// @param ST_CP = RCLK PIN
  Module3461BS_1(unsigned int DS, unsigned int SH_CP, unsigned int ST_CP)
  {
    this->ST_CP = ST_CP;
    this->SH_CP = SH_CP;
    this->DS = DS;
  }

  /// @brief Put this method in setup() function
  void setup()
  {
    // Set Arduino pins as outputs
    pinMode(ST_CP, OUTPUT);
    pinMode(SH_CP, OUTPUT);
    pinMode(DS, OUTPUT);
  }

  /* Displays a number as a 4-digit decimal number on the display
   *   Note this is multiplexed, so you need to keep calling it
   *   or you'll end up with just one digit lit.
   */
  void displayNumber(unsigned int number)
  {
    for (unsigned int i = 0; i < 4; i++)
    {
      setDigit(i, number % 10, false); // display righmost 4 bits (1 digit)
      number = number / 10;            // roll on to the next digit
      delay(1);
    }
  }

private:
  unsigned int ST_CP;
  unsigned int SH_CP;
  unsigned int DS;

  /* Set display digit to a hexadecimal value '0'..'9','A'..'F'
   *
   *    row = row number of digit to light up 0..3 where 3 is most significant (leftmost) display digit
   *    dgit = value 0 to 15
   *    decimalPoint = true/false : whether to light thde decimal point or not
   */
  void setDigit(unsigned int row, unsigned int digit, boolean decimalPoint)
  {
    static int hexDigitValue[] = {
        0xFC, /* Segments to light for 0  */
        0x60, /* Segments to light for 1  */
        0xDA, /* Segments to light for 2  */
        0xF2, /* Segments to light for 3  */
        0x66, /* Segments to light for 4  */
        0xB6, /* Segments to light for 5  */
        0xBE, /* Segments to light for 6  */
        0xE0, /* Segments to light for 7  */
        0xFE, /* Segments to light for 8  */
        0xF6  /* Segments to light for 9  */
    };
    unsigned int rowSelector;
    unsigned int data;

    rowSelector = bit(3 - row) << 4;
    data = ~hexDigitValue[digit & 0xF];
    if (decimalPoint)
      data &= 0xFE;

    // First 8 data bits all the way into the second 74HC595
    shiftOut(DS, SH_CP, LSBFIRST, data);

    // Now shift 4 row bits into the first 74HC595 and latch
    digitalWrite(ST_CP, LOW);
    shiftOut(DS, SH_CP, LSBFIRST, rowSelector);
    digitalWrite(ST_CP, HIGH);
  }
};
