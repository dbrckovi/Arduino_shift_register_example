#include <Arduino.h>

#define SRCLR 2
#define SER 4
#define RCLK 5
#define SRCLK 6  

uint8_t value;

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
  delay(5);
  value++;
}

void Show()
{
  digitalWrite(RCLK, LOW);
  delay(10);
  digitalWrite(RCLK, HIGH); 
}