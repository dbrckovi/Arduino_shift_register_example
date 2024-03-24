#include <Arduino.h>

#define SRCLR 2
#define SER 4
#define RCLK 5
#define SRCLK 6  

uint8_t value = 1;
bool going_up = true;

void Show();

void setup() 
{
  pinMode(SRCLR, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SRCLR, HIGH);
  digitalWrite(SER, LOW);
  digitalWrite(RCLK, LOW);
  digitalWrite(SRCLK, LOW);
}

void loop() 
{
  shiftOut(SER, SRCLK, HIGH, value);
  Show();
  if (going_up) value*=2;
  else value/=2;

  if (value == 128 || value == 1) going_up = !going_up;
}

void Show()
{
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH); 
}