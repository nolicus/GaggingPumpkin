#include <Arduino.h>
#include <stdbool.h>
#include "Gpio.h"

#define CS_PIN  (10)
#define SD_PIN  (15)
#define DR_PIN  (9)
#define DBG_PIN (16)

#define MICROCHIP_2CH_THUMB_PIN (1)
#define MICROCHIP_2CH_GRIP_PIN (2)

void Gpio_Init(void (*dataReadyISR)(void) )
{
  pinMode(SD_PIN, OUTPUT);
  pinMode(DBG_PIN, OUTPUT);
  pinMode(DR_PIN, INPUT);
  pinMode(MICROCHIP_2CH_GRIP_PIN, INPUT);
  pinMode(MICROCHIP_2CH_THUMB_PIN, INPUT);
  Gpio_DeAssertSD();

  attachInterrupt(digitalPinToInterrupt(DR_PIN), dataReadyISR, CHANGE);
}

void Gpio_InitCS()
{
  pinMode(CS_PIN, OUTPUT);
  Gpio_DeAssertCS();
}

void Gpio_AssertCS()
{
  digitalWrite(CS_PIN, LOW);
}

void Gpio_DeAssertCS()
{
  digitalWrite(CS_PIN, HIGH);
}

void Gpio_AssertSD()
{
  digitalWrite(SD_PIN, LOW);
  delay(10);
}

void Gpio_DeAssertSD()
{
  digitalWrite(SD_PIN, HIGH);
  delay(10);
}

bool Gpio_DRAsserted()
{
  return digitalRead(DR_PIN) == HIGH;
}

bool Gpio_2ChThumbAsserted()
{
  return digitalRead(MICROCHIP_2CH_THUMB_PIN) == LOW;
}

bool Gpio_2ChGripAsserted()
{
  return digitalRead(MICROCHIP_2CH_GRIP_PIN) == LOW;
}

void Gpio_AssertDbg()
{
  digitalWrite(DBG_PIN, HIGH);
}
void Gpio_DeAssertDbg()
{
  digitalWrite(DBG_PIN, LOW);
}
