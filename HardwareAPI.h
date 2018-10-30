#ifdef __cplusplus
extern "C" {
#endif

#ifndef _HARDWARE_API_H_
#define _HARDWARE_API_H_

#include <stdint.h>
#include <stdbool.h>

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

typedef void    (*voidFunction_t)     (void);
typedef bool    (*boolFunction_t)     (void);
typedef uint8_t (*byteFunction_t)     (void);

typedef void    (*SPI_Init_t)         (uint32_t clockFreq, uint8_t bitOrder, uint8_t spiMode);
typedef uint8_t (*SPI_TransferByte_t) (uint8_t txByte);
typedef void    (*GPIO_Init_t)        (voidFunction_t);
typedef void    (*Serial_Write_t)     (uint8_t);


typedef struct
{
  const SPI_Init_t          Init;
  const SPI_TransferByte_t  TransferByte;
  const voidFunction_t      InitCS;
  const voidFunction_t      AssertCS;
  const voidFunction_t      DeAssertCS;
} spiHandle_t;

typedef struct
{
  const GPIO_Init_t       Init;
  const voidFunction_t    AssertSD;
  const voidFunction_t    DeAssertSD;
  const boolFunction_t    DRAsserted;
} gpioHandle_t;

typedef struct
{
  const voidFunction_t      Init;
  const Serial_Write_t      Write;
  const byteFunction_t      Read;
  const byteFunction_t      Available;
} serialHandle_t;

#endif  // _HARDWARE_API_H_

#ifdef __cplusplus
}
#endif
