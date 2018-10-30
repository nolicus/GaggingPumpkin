#include <stdint.h>
#include "BarcProtocol.h"
#include "Comet.h"

gpioHandle_t * _gpioHandlePtr;

bool _dataIsReady = false;

void dataReadyISR(void);

/*  Public Comet Methods  */
void Comet_Init(spiHandle_t * spiHandlePtr, gpioHandle_t * gpioHandlePtr)
{
  _gpioHandlePtr = gpioHandlePtr;

  _gpioHandlePtr->Init(dataReadyISR);
  
  BARC_Init(spiHandlePtr);
  Comet_SwReset();
}

void Comet_HwReset()
{
  _gpioHandlePtr->AssertSD();
  _gpioHandlePtr->DeAssertSD();
}

void Comet_SwReset()
{
  uint8_t data = 0x01;
  BARC_Write(SYS__RST, &data, 1);
}

uint8_t Comet_ReadRegister(uint8_t address)
{
  uint8_t data;
  BARC_Read(address, &data, 1);
  return data;
}

void Comet_ReadRegisters(uint8_t address, uint8_t * data, uint8_t count)
{
  BARC_Read(address, data, count);
}

void Comet_WriteRegister(uint8_t address, uint8_t data)
{
  BARC_Write(address, &data, 1);
}

void Comet_WriteRegisters(uint8_t address, uint8_t * data, uint8_t count)
{
  BARC_Write(address, data, count);
}

void Comet_ReadSysConfig(sysConfig_t * sysConfigPtr)
{
  BARC_Read(0x00, sysConfigPtr->Array, SYS__DMD_SFT8 + 1);
}

void Comet_WriteSysConfig(sysConfig_t * sysConfigPtr)
{
  BARC_Write(0x00, sysConfigPtr->Array, SYS__DMD_SFT8 + 1);
}

void Comet_WriteElectrodeConfig(electrodeConfig_t * elConfig)
{
  BARC_Write(MEAS__ELD_SEL0, elConfig->Array, 16);
}

void Comet_ReadMeasResults(measResult_t * results)
{
  BARC_Read(MEAS__ADC_DATAL0, (uint8_t*)results->Array, 32);
}

void Comet_ReadMeasResultsIQ(measResultIQ_t * results)
{
  uint8_t afeCnt = 0;
  
  BARC_Read(MEAS__AFE_CNT, &afeCnt, 1);
  afeCnt |= 0x20;
  BARC_Write(MEAS__AFE_CNT, &afeCnt, 1);
  
  BARC_Read(MEAS__ADC_I_DATAL0, (uint8_t*)results->Array, 64);
}
/*******************************************************************/

void Comet_StartMeasurement(void)
{
  uint8_t data = 0x03;
  BARC_Write(MEAS__AFE_CNT, &data, 1);
}

void Comet_StopMeasurement(void)
{
  uint8_t data = 0x02;
  BARC_Write(MEAS__AFE_CNT, &data, 1);
}

bool Comet_MeasurementBusy(void)
{
  uint8_t data;
  BARC_Read(MEAS__AFE_CNT, &data, 1);

  return (data & 0x04) != 0;
}

bool Comet_DataIsReady()
{
  return _dataIsReady;
}
/*  End Public Comet Methods  */


/*  Private Comet Methods   */
void dataReadyISR()
{
  _dataIsReady = _gpioHandlePtr->DRAsserted();
}
/*  End Private Comet Methods   */
