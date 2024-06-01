#include <Arduino.h>

/*
Example for two shift registers (SNx4HC595) connected in 'series' to form two digit 7-segment display
 - VCC to +5V
 - GND to GND
 - everything else like defined in global variables
 - output pins each to LED -> 1k resistor -> GND
*/

#define SRCLR 2 //CLEAR        - clears memory when going LOW -> HIGH
#define SER 4   // DATA         - value is copied to first output pin when SRCLK goes LOW -> HIGH
#define RCLK 5  // OUTPUT CLOCK - data is copied to output pins when RCLK goes LOW -> HIGH
#define SRCLK 7 // INPUT CLOCK  - data from SER pin is copied to first output when SRCLK goes LOW -> HIGH
#define OE 6    // OUTPUT ENABLE - output is enabled when low

void Show(uint8_t value);
void ShowDigit(byte value);
void Clear();
void EnableOutput(int intensity);
void DisableOutput();

void setup()
{
  pinMode(SRCLR, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(OE, OUTPUT);

  digitalWrite(SRCLR, HIGH);
  digitalWrite(SER, LOW);
  digitalWrite(RCLK, LOW);
  digitalWrite(SRCLK, LOW);
  digitalWrite(OE, LOW);

  Serial.begin(115200);
}

void loop()
{
  Clear();

  for (byte number = 0; number <= 99; number++)
  {
    byte first = number / 10;
    byte second = number % 10;
  
    DisableOutput();
    ShowDigit(first);
    ShowDigit(second);
    EnableOutput(map(number, 99, 0, 0, 255));
    delay (50);
  }
}

void Show(uint8_t value)
{
  shiftOut(SER, SRCLK, HIGH, value);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
  Serial.println(value);
}

void Clear()
{
  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
}

void ShowDigit(byte digit)
{
  uint8_t outValue = 0;

  /*
   666
  5   7
  5   7
  5   7
   333
  2   4
  2   4
  2   4
   111 

  Segment representation by bit numbers LSB = 0
  */

  switch (digit)
  {
  case 0:
    outValue = 0b11110110;
    break;
  case 1:
    outValue = 0b10010000;
    break;
  case 2:
    outValue = 0b11001110;
    break;
  case 3:
    outValue = 0b11011010;
    break;
  case 4:
    outValue = 0b10111000;
    break;
  case 5:
    outValue = 0b01111010;
    break;
  case 6:
    outValue = 0b01111111;
    break;
  case 7:
    outValue = 0b11010000;
    break;
  case 8:
    outValue = 0b11111110;
    break;
  case 9:
    outValue = 0b11111011;
    break;
  }

  Show(outValue);
}

void EnableOutput(int intensity)
{
    //digitalWrite(OE, LOW);
    analogWrite(OE, intensity);
}

void DisableOutput()
{
    digitalWrite(OE, HIGH);
}