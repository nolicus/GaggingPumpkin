#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GPIO_H_
#define _GPIO_H_

void Gpio_Init(void (*functionPtr)(void));
void Gpio_InitCS(void);
void Gpio_AssertCS(void);
void Gpio_DeAssertCS(void);
void Gpio_AssertSD(void);
void Gpio_DeAssertSD(void);
bool Gpio_DRAsserted(void);
bool Gpio_2ChThumbAsserted(void);
bool Gpio_2ChGripAsserted(void);

void Gpio_AssertDbg(void);
void Gpio_DeAssertDbg(void);
#endif  // _GPIO_H_

#ifdef __cplusplus
}
#endif
