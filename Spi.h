#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SPI_H_
#define _SPI_H_

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

void SPI_Init(uint32_t clockFrequency, uint8_t bitOrder, uint8_t spiMode);
uint8_t SPI_TransferByte(uint8_t txByte);
void SPI_TransferBytes(uint8_t * txData, uint8_t * rxData, uint32_t dataLength);

#endif  // _SPI_H_

#ifdef __cplusplus
}
#endif
