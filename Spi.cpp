#include <Arduino.h>
#include <SPI.h>
#include "Spi.h"

SPISettings _spiSettings;

void SPI_Init(uint32_t clockFrequency, uint8_t bitOrder, uint8_t spiMode)
{
#if defined(TEENSYDUINO) 
  _spiSettings = SPISettings(clockFrequency, bitOrder, spiMode);
#else
  _spiSettings = SPISettings(clockFrequency, (BitOrder)bitOrder, spiMode);
#endif
  SPI.begin();
}

uint8_t SPI_TransferByte(uint8_t txByte)
{
  uint8_t response;
  
  SPI.beginTransaction(_spiSettings);
  response = SPI.transfer(txByte);
  SPI.endTransaction();

  return response;
}

void SPI_TransferBytes(uint8_t * txData, uint8_t * rxData, uint32_t dataLength)
{
  SPI.beginTransaction(_spiSettings);

  for(uint32_t i = 0; i < dataLength; i++)
  {
    rxData[i] = SPI.transfer(txData[i]);
  }

  SPI.endTransaction();
}
