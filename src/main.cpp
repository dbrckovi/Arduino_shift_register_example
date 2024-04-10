#include <Arduino.h>

/*
For this to work, connect shift register (SNx4HC595) like this
 - VCC to +5V
 - GND to GND
 - OE pin to GND
 - everything else like defined in global variables
 - output pins each to LED -> 1k resistor -> GND
*/

// #define SRCLR 2       //CLEAR        - clears memory when going LOW -> HIGH
#define SER 4   // DATA         - value is copied to first output pin when SRCLK goes LOW -> HIGH
#define RCLK 5  // OUTPUT CLOCK - data is copied to output pins when RCLK goes LOW -> HIGH
#define SRCLK 6 // INPUT CLOCK  - data from SER pin is copied to first output when SRCLK goes LOW -> HIGH

void Show(uint8_t value);
void ShowDigit(byte value);

void setup()
{
  // pinMode(SRCLR, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  // digitalWrite(SRCLR, HIGH);
  digitalWrite(SER, LOW);
  digitalWrite(RCLK, LOW);
  digitalWrite(SRCLK, LOW);

  Serial.begin(115200);
}

void loop()
{
  for (byte digit = 0; digit <= 9; digit++)
  {
    ShowDigit(digit);
    delay(300);
  }
}

void Show(uint8_t value)
{
  shiftOut(SER, SRCLK, HIGH, value);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
  Serial.println(value);
}

void ShowDigit(byte digit)
{
  uint8_t outValue = 0;

  /*

   777
  6   1
  6   1
  6   1
   222
  5   3
  5   3
  5   3
   444 

  Segment representation by bit numbers
  */

  switch (digit)
  {
  case 0:
    outValue = 0b11111010;
    break;
  case 1:
    outValue = 0b00001010;
    break;
  case 2:
    outValue = 0b10110110;
    break;
  case 3:
    outValue = 0b10011110;
    break;
  case 4:
    outValue = 0b01001110;
    break;
  case 5:
    outValue = 0b11011100;
    break;
  case 6:
    outValue = 0b11111100;
    break;
  case 7:
    outValue = 0b10001010;
    break;
  case 8:
    outValue = 0b11111111;
    break;
  case 9:
    outValue = 0b11011111;
    break;
  }

  Show(outValue);
}