#include "stm32f429xx.h"
#define SET_BIT(REG, BIT)       ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(BIT))
#define MODIFY_REG(REG, MASK, VALUE) \
    ((REG) = ((REG) & ~(MASK)) | ((VALUE) & (MASK)))

void RCC_Ini(void);
void GPIO_Ini(void);
void EXTI_ITR_Ini(void);
void SysTick_Init(void);