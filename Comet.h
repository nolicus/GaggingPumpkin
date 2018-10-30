#ifdef __cplusplus
extern "C" {
#endif

#ifndef _COMET_H_
#define _COMET_H_

#include "HardwareAPI.h"

/*  Comet Registers */
#define SYS__TR_BG      (0x00)
#define SYS__TR_BI      (0x01)
#define SYS__OTP_CNT0   (0x02)
#define SYS__OTP_CNT1   (0x03)
#define SYS__RST        (0x04)
#define SYS__DRV_STR    (0x05)
#define SYS__PWC0       (0x06)
#define SYS__PWC1       (0x07)
#define SYS__PWC2       (0x08)
#define SYS__FUNC       (0x09)
#define SYS__CLK_CNT    (0x0A)
#define SYS__FLT_CNT_R  (0x0B)
#define SYS__BW_CTL     (0x0C)
#define SYS__FIL_TAP    (0x0D)
#define SYS__RND_BIT    (0x0E)
#define SYS__WAV_CNT    (0x0F)
#define SYS__ADC_CNT    (0x10)
#define SYS__DMD_SFT0   (0x11)
#define SYS__DMD_SFT1   (0x12)
#define SYS__DMD_SFT2   (0x13)
#define SYS__DMD_SFT3   (0x14)
#define SYS__DMD_SFT4   (0x15)
#define SYS__DMD_SFT5   (0x16)
#define SYS__DMD_SFT6   (0x17)
#define SYS__DMD_SFT7   (0x18)
#define SYS__DMD_SFT8   (0x19)
#define SYS__RESERVED0  (0x1A)
#define SYS__RESERVED1  (0x1B)
#define SYS__RESERVED2  (0x1C)
#define SYS__RESERVED3  (0x1D)

#define MEAS__AFE_CNT    (0x1E)
//  ADC_IQ = 0 (Address: 0x1F~0x65)
#define MEAS__ELD_SEL0  (0x1F)
#define MEAS__ELD_SEL1  (0x20)
#define MEAS__ELD_SEL2  (0x21)
#define MEAS__ELD_SEL3  (0x22)
#define MEAS__ELD_SEL4  (0x23)
#define MEAS__ELD_SEL5  (0x24)
#define MEAS__ELD_SEL6  (0x25)
#define MEAS__ELD_SEL7  (0x26)
#define MEAS__ELD_SEL8  (0x27)
#define MEAS__ELD_SEL9  (0x28)
#define MEAS__ELD_SEL10 (0x29)
#define MEAS__ELD_SEL11 (0x2A)
#define MEAS__ELD_SEL12 (0x2B)
#define MEAS__ELD_SEL13 (0x2C)
#define MEAS__ELD_SEL14 (0x2D)
#define MEAS__ELD_SEL15 (0x2E)
#define MEAS__OFT_ADJ_F0  (0x2F)
#define MEAS__OFT_ADJ_F1  (0x30)
#define MEAS__OFT_ADJ_F2  (0x31)
#define MEAS__OFT_ADJ_F3  (0x32)
#define MEAS__OFT_ADJ_F4  (0x33)
#define MEAS__OFT_ADJ_F5  (0x34)
#define MEAS__OFT_ADJ_F6  (0x35)
#define MEAS__OFT_ADJ_F7  (0x36)
#define MEAS__OFT_ADJ_C0  (0x37)
#define MEAS__OFT_ADJ_C1  (0x38)
#define MEAS__OFT_ADJ_C2  (0x39)
#define MEAS__OFT_ADJ_C3  (0x3A)
#define MEAS__OFT_ADJ_C4  (0x3B)
#define MEAS__OFT_ADJ_C5  (0x3C)
#define MEAS__OFT_ADJ_C6  (0x3D)
#define MEAS__OFT_ADJ_C7  (0x3E)
#define MEAS__OFT_ADJ_C8  (0x3F)
#define MEAS__OFT_ADJ_C9  (0X40)
#define MEAS__OFT_ADJ_C10 (0X41)
#define MEAS__OFT_ADJ_C11 (0X42)
#define MEAS__OFT_ADJ_C12 (0X43)
#define MEAS__OFT_ADJ_C13 (0X44)
#define MEAS__OFT_ADJ_C14 (0X45)
#define MEAS__OFT_ADJ_C15 (0X46)
#define MEAS__GAIN_ADJ0   (0X47)
#define MEAS__GAIN_ADJ1   (0X48)
#define MEAS__GAIN_ADJ2   (0X49)
#define MEAS__GAIN_ADJ3   (0X4A)
#define MEAS__GAIN_ADJ4   (0X4B)
#define MEAS__GAIN_ADJ5   (0X4C)
#define MEAS__GAIN_ADJ6   (0X4D)
#define MEAS__GAIN_ADJ7   (0X4E)
#define MEAS__ADC_DATAL0  (0X4F)
#define MEAS__ADC_DATAH0  (0x50)
#define MEAS__ADC_DATAL1  (0x51)
#define MEAS__ADC_DATAH1  (0x52)
#define MEAS__ADC_DATAL2  (0x53)
#define MEAS__ADC_DATAH2  (0x54)
#define MEAS__ADC_DATAL3  (0x55)
#define MEAS__ADC_DATAH3  (0x56)
#define MEAS__ADC_DATAL4  (0x57)
#define MEAS__ADC_DATAH4  (0x58)
#define MEAS__ADC_DATAL5  (0x59)
#define MEAS__ADC_DATAH5  (0x5A)
#define MEAS__ADC_DATAL6  (0x5B)
#define MEAS__ADC_DATAH6  (0x5C)
#define MEAS__ADC_DATAL7  (0x5D)
#define MEAS__ADC_DATAH7  (0x5E)
#define MEAS__ADC_DATAL8  (0x5F)
#define MEAS__ADC_DATAH8  (0x60)
#define MEAS__ADC_DATAL9  (0x61)
#define MEAS__ADC_DATAH9  (0x62)
#define MEAS__ADC_DATAL10 (0x63)
#define MEAS__ADC_DATAH10 (0x64)
#define MEAS__ADC_DATAL11 (0x65)
#define MEAS__ADC_DATAH11 (0x66)
#define MEAS__ADC_DATAL12 (0x67)
#define MEAS__ADC_DATAH12 (0x68)
#define MEAS__ADC_DATAL13 (0x69)
#define MEAS__ADC_DATAH13 (0x6A)
#define MEAS__ADC_DATAL14 (0x6B)
#define MEAS__ADC_DATAH14 (0x6C)
#define MEAS__ADC_DATAL15 (0x6D)
#define MEAS__ADC_DATAH15 (0x6E)
#define MEAS__RESERVED0   (0x6F)

//  ADC_IQ = 1 (Address: 0x1F~0x65)
#define MEAS__OFT_ADJ_F8    (0x1F)
#define MEAS__OFT_ADJ_C16   (0x20)
#define MEAS__GAIN_ADJ8     (0x21)
#define MEAS__ADC_I_DATAL0  (0x22)
#define MEAS__ADC_I_DATAH0  (0x23)
#define MEAS__ADC_I_DATAL1  (0x24)
#define MEAS__ADC_I_DATAH1  (0x25)
#define MEAS__ADC_I_DATAL2  (0x26)
#define MEAS__ADC_I_DATAH2  (0x27)
#define MEAS__ADC_I_DATAL3  (0x28)
#define MEAS__ADC_I_DATAH3  (0x29)
#define MEAS__ADC_I_DATAL4  (0x2A)
#define MEAS__ADC_I_DATAH4  (0x2B)
#define MEAS__ADC_I_DATAL5  (0x2C)
#define MEAS__ADC_I_DATAH5  (0x2D)
#define MEAS__ADC_I_DATAL6  (0x2E)
#define MEAS__ADC_I_DATAH6  (0x2F)
#define MEAS__ADC_I_DATAL7  (0x30)
#define MEAS__ADC_I_DATAH7  (0x31)
#define MEAS__ADC_I_DATAL8  (0x32)
#define MEAS__ADC_I_DATAH8  (0x33)
#define MEAS__ADC_I_DATAL9  (0x34)
#define MEAS__ADC_I_DATAH9  (0x35)
#define MEAS__ADC_I_DATAL10  (0x36)
#define MEAS__ADC_I_DATAH10  (0x37)
#define MEAS__ADC_I_DATAL11  (0x38)
#define MEAS__ADC_I_DATAH11  (0x39)
#define MEAS__ADC_I_DATAL12  (0x3A)
#define MEAS__ADC_I_DATAH12  (0x3B)
#define MEAS__ADC_I_DATAL13  (0x3C)
#define MEAS__ADC_I_DATAH13  (0x3D)
#define MEAS__ADC_I_DATAL14  (0x3E)
#define MEAS__ADC_I_DATAH14  (0x3F)
#define MEAS__ADC_I_DATAL15  (0x40)
#define MEAS__ADC_I_DATAH15  (0x41)
#define MEAS__ADC_I_DATAL16  (0x42)
#define MEAS__ADC_I_DATAH16  (0x43)
#define MEAS__ADC_Q_DATAL0   (0x44)
#define MEAS__ADC_Q_DATAH0   (0x45)
#define MEAS__ADC_Q_DATAL1   (0x46)
#define MEAS__ADC_Q_DATAH1   (0x47)
#define MEAS__ADC_Q_DATAL2   (0x48)
#define MEAS__ADC_Q_DATAH2   (0x49)
#define MEAS__ADC_Q_DATAL3   (0x4A)
#define MEAS__ADC_Q_DATAH3   (0x4B)
#define MEAS__ADC_Q_DATAL4   (0x4C)
#define MEAS__ADC_Q_DATAH4   (0x4D)
#define MEAS__ADC_Q_DATAL5   (0x4E)
#define MEAS__ADC_Q_DATAH5   (0x4F)
#define MEAS__ADC_Q_DATAL6   (0x50)
#define MEAS__ADC_Q_DATAH6   (0x51)
#define MEAS__ADC_Q_DATAL7   (0x52)
#define MEAS__ADC_Q_DATAH7   (0x53)
#define MEAS__ADC_Q_DATAL8   (0x54)
#define MEAS__ADC_Q_DATAH8   (0x55)
#define MEAS__ADC_Q_DATAL9   (0x56)
#define MEAS__ADC_Q_DATAH9   (0x57)
#define MEAS__ADC_Q_DATAL10  (0x58)
#define MEAS__ADC_Q_DATAH10  (0x59)
#define MEAS__ADC_Q_DATAL11  (0x5A)
#define MEAS__ADC_Q_DATAH11  (0x5B)
#define MEAS__ADC_Q_DATAL12  (0x5C)
#define MEAS__ADC_Q_DATAH12  (0x5D)
#define MEAS__ADC_Q_DATAL13  (0x5E)
#define MEAS__ADC_Q_DATAH13  (0x5F)
#define MEAS__ADC_Q_DATAL14  (0x60)
#define MEAS__ADC_Q_DATAH14  (0x61)
#define MEAS__ADC_Q_DATAL15  (0x62)
#define MEAS__ADC_Q_DATAH15  (0x63)
#define MEAS__ADC_Q_DATAL16  (0x64)
#define MEAS__ADC_Q_DATAH16  (0x65)

//  OTP_EX_ADD = 0 (Address: 0x70~0x77)
#define TEST__FLT_CNT0    (0x70)
#define TEST__FLT_CNT1    (0x71)
#define TEST__FLT_CNT2    (0x72)
#define TEST__TR_AFE      (0x73)
#define TEST__CREF_ER     (0x74)
#define TEST__RREF_ER     (0x75)
#define TEST__TM_SEL      (0x76)
#define TEST__TC_MES      (0x77)

// OTP_EX_ADD = 1 (Address: 0x70~0x77)
#define TEST__TRACE0      (0x70)
#define TEST__TRACE1      (0x71)
#define TEST__TRACE2      (0x72)
#define TEST__TRACE3      (0x73)
#define TEST__TRACE4      (0x74)
#define TEST__TRACE5      (0x75)
#define TEST__TRACE6      (0x76)
#define TEST__TRACE7      (0x77)
#define TEST__NM_SEL0     (0x78)
#define TEST__NM_SEL1     (0x79)
#define TEST__NM_SEL2     (0x7A)
#define TEST__MIXED0      (0x7B)
#define TEST__MIXED1      (0x7C)
#define TEST__RESERVED0   (0x7D)
#define TEST__RESERVED1   (0x7E)
#define TEST__RESERVED2   (0x7F)
/*  End Comet Registers */

/*  Comet Types   */
typedef union
{
  uint8_t Array[SYS__DMD_SFT8 + 1];
  struct
  {
    uint8_t TR_BG;
    uint8_t TR_BI;
    uint8_t OTP_CNT0;
    uint8_t OTP_CNT1;
    uint8_t RST;
    uint8_t DRV_STR;
    uint8_t PWC0;
    uint8_t PWC1;
    uint8_t PWC2;
    uint8_t FUNC;
    uint8_t CLK_CNT;
    uint8_t FLT_CNT_R;
    uint8_t BW_CTL;
    uint8_t FIL_TAP;
    uint8_t RND_BIT;
    uint8_t WAV_CNT;
    uint8_t ADC_CNT;
    uint8_t DMD_SFT0;
    uint8_t DMD_SFT1;
    uint8_t DMD_SFT2;
    uint8_t DMD_SFT3;
    uint8_t DMD_SFT4;
    uint8_t DMD_SFT5;
    uint8_t DMD_SFT6;
    uint8_t DMD_SFT7;
    uint8_t DMD_SFT8;
  } Struct;
} sysConfig_t;

typedef union
{
  uint8_t Array[49];
  struct
  {
    uint8_t AFE_CNT;
    uint8_t ELD_SEL0;
    uint8_t ELD_SEL1;
    uint8_t ELD_SEL2;
    uint8_t ELD_SEL3;
    uint8_t ELD_SEL4;
    uint8_t ELD_SEL5;
    uint8_t ELD_SEL6;
    uint8_t ELD_SEL7;
    uint8_t ELD_SEL8;
    uint8_t ELD_SEL9;
    uint8_t ELD_SEL10;
    uint8_t ELD_SEL11;
    uint8_t ELD_SEL12;
    uint8_t ELD_SEL13;
    uint8_t ELD_SEL14;
    uint8_t ELD_SEL15;
    uint8_t OFT_ADJ_F0;
    uint8_t OFT_ADJ_F1;
    uint8_t OFT_ADJ_F2;
    uint8_t OFT_ADJ_F3;
    uint8_t OFT_ADJ_F4;
    uint8_t OFT_ADJ_F5;
    uint8_t OFT_ADJ_F6;
    uint8_t OFT_ADJ_F7;
    uint8_t OFT_ADJ_C0;
    uint8_t OFT_ADJ_C1;
    uint8_t OFT_ADJ_C2;
    uint8_t OFT_ADJ_C3;
    uint8_t OFT_ADJ_C4;
    uint8_t OFT_ADJ_C5;
    uint8_t OFT_ADJ_C6;
    uint8_t OFT_ADJ_C7;
    uint8_t OFT_ADJ_C8;
    uint8_t OFT_ADJ_C9;
    uint8_t OFT_ADJ_C10;
    uint8_t OFT_ADJ_C11;
    uint8_t OFT_ADJ_C12;
    uint8_t OFT_ADJ_C13;
    uint8_t OFT_ADJ_C14;
    uint8_t OFT_ADJ_C15;
    uint8_t GAIN_ADJ0;
    uint8_t GAIN_ADJ1;
    uint8_t GAIN_ADJ2;
    uint8_t GAIN_ADJ3;
    uint8_t GAIN_ADJ4;
    uint8_t GAIN_ADJ5;
    uint8_t GAIN_ADJ6;
    uint8_t GAIN_ADJ7;
  } Struct;
} measConfig_t;

typedef union
{
  uint8_t Array[16];
  struct
  {
    uint8_t ELD_SEL0;
    uint8_t ELD_SEL1;
    uint8_t ELD_SEL2;
    uint8_t ELD_SEL3;
    uint8_t ELD_SEL4;
    uint8_t ELD_SEL5;
    uint8_t ELD_SEL6;
    uint8_t ELD_SEL7;
    uint8_t ELD_SEL8;
    uint8_t ELD_SEL9;
    uint8_t ELD_SEL10;
    uint8_t ELD_SEL11;
    uint8_t ELD_SEL12;
    uint8_t ELD_SEL13;
    uint8_t ELD_SEL14;
    uint8_t ELD_SEL15;
  } Struct;
} electrodeConfig_t;

typedef union
{
  uint16_t Array[16];
  struct
  {
    uint16_t ADC_DATA0;
    uint16_t ADC_DATA1;
    uint16_t ADC_DATA2;
    uint16_t ADC_DATA3;
    uint16_t ADC_DATA4;
    uint16_t ADC_DATA5;
    uint16_t ADC_DATA6;
    uint16_t ADC_DATA7;
    uint16_t ADC_DATA8;
    uint16_t ADC_DATA9;
    uint16_t ADC_DATA10;
    uint16_t ADC_DATA11;
    uint16_t ADC_DATA12;
    uint16_t ADC_DATA13;
    uint16_t ADC_DATA14;
    uint16_t ADC_DATA15;
  } Struct;
} measResult_t;

typedef union
{
  int16_t Array[32];
  struct
  {
    int16_t ADC_I_DATA0;
    int16_t ADC_I_DATA1;
    int16_t ADC_I_DATA2;
    int16_t ADC_I_DATA3;
    int16_t ADC_I_DATA4;
    int16_t ADC_I_DATA5;
    int16_t ADC_I_DATA6;
    int16_t ADC_I_DATA7;
    int16_t ADC_I_DATA8;
    int16_t ADC_I_DATA9;
    int16_t ADC_I_DATA10;
    int16_t ADC_I_DATA11;
    int16_t ADC_I_DATA12;
    int16_t ADC_I_DATA13;
    int16_t ADC_I_DATA14;
    int16_t ADC_I_DATA15;
    int16_t ADC_Q_DATA0;
    int16_t ADC_Q_DATA1;
    int16_t ADC_Q_DATA2;
    int16_t ADC_Q_DATA3;
    int16_t ADC_Q_DATA4;
    int16_t ADC_Q_DATA5;
    int16_t ADC_Q_DATA6;
    int16_t ADC_Q_DATA7;
    int16_t ADC_Q_DATA8;
    int16_t ADC_Q_DATA9;
    int16_t ADC_Q_DATA10;
    int16_t ADC_Q_DATA11;
    int16_t ADC_Q_DATA12;
    int16_t ADC_Q_DATA13;
    int16_t ADC_Q_DATA14;
    int16_t ADC_Q_DATA15;
  } Struct;
} measResultIQ_t;
/*  End Comet Types   */

/*  Comet Methods */
void Comet_Init(spiHandle_t * spiHandlePtr, gpioHandle_t * gpioHandlePtr);
void Comet_SwReset(void);
void Comet_HwReset(void);
uint8_t Comet_ReadRegister(uint8_t address);
void Comet_ReadRegisters(uint8_t address, uint8_t * data, uint8_t count);
void Comet_WriteRegister(uint8_t address, uint8_t data);
void Comet_WriteRegisters(uint8_t address, uint8_t * data, uint8_t count);
void Comet_ReadMeasResults(measResult_t * results);
void Comet_ReadMeasResultsIQ(measResultIQ_t * results);

void Comet_ReadSysConfig(sysConfig_t * sysConfigPtr);
void Comet_WriteSysConfig(sysConfig_t * sysConfigPtr);
void Comet_WriteElectrodeConfig(electrodeConfig_t * elConfig);
void Comet_StartMeasurement(void);
void Comet_StopMeasurement(void);
bool Comet_MeasurementBusy(void);
bool Comet_DataIsReady(void);
/*  End Comet Methods   */

#endif  // _COMET_H_

#ifdef __cplusplus
}
#endif
