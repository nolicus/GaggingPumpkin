#ifdef __cplusplus
extern "C" {
#endif

#ifndef _BARCPROTOCOL_H_
#define _BARCPROTOCOL_H_

#include "HardwareAPI.h"

#define BARC_MAX_READ_LENGTH  (15)
#define BARC_MAX_WRITE_LENGTH (13)
#define BARC_MAX_RW_LENGTH    ((BARC_MAX_READ_LENGTH > BARC_MAX_WRITE_LENGTH) ? BARC_MAX_READ_LENGTH : BARC_MAX_WRITE_LENGTH)

#define BARC_DUMMY_READ_ADDR  (0x7F)

void BARC_Init(spiHandle_t * spiHandlePtr);
void BARC_Write(uint8_t writeAddress, uint8_t * data, uint8_t dataLength);
void BARC_Read(uint8_t readAddress, uint8_t * data, uint8_t dataLength);
void BARC_ReadWrite(uint8_t readAddress, uint8_t writeAddress, uint8_t * readData, uint8_t readDataLength, uint8_t * writeData, uint8_t writeDataLength);

#endif  // _BARCPROTOCOL_H_

#ifdef __cplusplus
}
#endif
