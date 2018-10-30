#include <stdint.h>
#include "BarcProtocol.h"

spiHandle_t   * _spiHandlePtr;

void BARC_Init(spiHandle_t * spiHandlePtr)
{
  _spiHandlePtr = spiHandlePtr;
  
  _spiHandlePtr->Init(4000000, MSBFIRST, SPI_MODE0);
  
  _spiHandlePtr->InitCS();
}

void BARC_Write(uint8_t writeAddress, uint8_t * data, uint8_t dataLength)
{
  BARC_ReadWrite(0x00, writeAddress, 0, 0, data, dataLength);
}

void BARC_Read(uint8_t readAddress, uint8_t * data, uint8_t dataLength)
{
  uint16_t i = 0;
  
  _spiHandlePtr->AssertCS();
  _spiHandlePtr->TransferByte(readAddress << 1);

  for(; i < dataLength; i++)
  {
    data[i] = _spiHandlePtr->TransferByte(0xFF);
  }

  _spiHandlePtr->DeAssertCS();
}

void BARC_ReadWrite(uint8_t readAddress, uint8_t writeAddress, uint8_t * readData, uint8_t readDataLength, uint8_t * writeData, uint8_t writeDataLength)
{
  uint16_t i = 0;

  if(readDataLength > writeDataLength) return;
  
  _spiHandlePtr->AssertCS();
  _spiHandlePtr->TransferByte((readAddress << 1) | 1);
  _spiHandlePtr->TransferByte((writeAddress << 1));

  for(; i < writeDataLength; i++)
  {
    if(i < readDataLength)
    {
      readData[i] = _spiHandlePtr->TransferByte(writeData[i]);
    }
    else
    {
      _spiHandlePtr->TransferByte(writeData[i]);
    }
  }
  
  _spiHandlePtr->DeAssertCS();
}
