#include "init.h"
#include "it_handlers.h"

void LedController(void);

//uint32_t sync[6] = {0, 833, 1666, 2499, 3332, 4165}; калибровка пока не надо
uint32_t TestTickCount = 0;
volatile uint32_t GlobalTickCount = 0;
uint8_t CurLed = 0; 
uint16_t GarlandFreq = 833;
uint16_t LedList[6] = {2500, 2500, 2500, 2500, 2500, 2500};
uint32_t LedTimersEnd[6] = {0, 833, 1666, 2499, 3332, 4165};
_Bool LedStates[6] = {0, 0, 0, 0, 0, 0};
_Bool ledone = 0;
_Bool ledtwo = 0;
_Bool ledthree = 0;
_Bool ledfour = 0;
_Bool ledfive = 0;
_Bool ledsix = 0;
_Bool WorkMode = 0;

int main(void) {
    GPIO_Ini();
    RCC_Ini();
    EXTI_ITR_Ini();
    SysTick_Init();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODE7_0;

    while(1){
        LedController();
    }
}

void LedController(void) {
    if(WorkMode == 0){
        if((GlobalTickCount >= LedTimersEnd[0])) {
        LedStates[0] = !LedStates[0];
        ledone = LedStates[0];
        LedTimersEnd[0] = GlobalTickCount + GarlandFreq;
        } else {
        if (LedStates[0]) {
            GPIOD->BSRR = GPIO_BSRR_BS0;  // Включить (Set)
        } else {
            GPIOD->BSRR = GPIO_BSRR_BR0;  // Выключить (Reset)
        }
        }

        if((GlobalTickCount >= LedTimersEnd[1])) {
                LedStates[1] = !LedStates[1];
                ledtwo = LedStates[1];
                    LedTimersEnd[1] = GlobalTickCount + GarlandFreq;
                } else {
                if (LedStates[1]) {
                    GPIOD->BSRR = GPIO_BSRR_BS1;  // Включить (Set)
                } else {
                    GPIOD->BSRR = GPIO_BSRR_BR1;  // Выключить (Reset)
                }
            }

        if((GlobalTickCount >= LedTimersEnd[2])) {
            LedStates[2] = !LedStates[2];
            ledthree = LedStates[2];
            LedTimersEnd[2] = GlobalTickCount + GarlandFreq;
            } else {
            if (LedStates[2]) {
                GPIOD->BSRR = GPIO_BSRR_BS2;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR2;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[3])) {
            LedStates[3] = !LedStates[3];
            ledfour = LedStates[3];
            LedTimersEnd[3] = GlobalTickCount + GarlandFreq;
            } else {
            if (LedStates[3]) {
                GPIOD->BSRR = GPIO_BSRR_BS3;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR3;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[4])) {
            LedStates[4] = !LedStates[4];
            ledfive = LedStates[4];
            LedTimersEnd[4] = GlobalTickCount + GarlandFreq;
            } else {
            if (LedStates[4]) {
                GPIOD->BSRR = GPIO_BSRR_BS4;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR4;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[5])) {
            LedStates[5] = !LedStates[5];
            ledsix = LedStates[5];
            LedTimersEnd[5] = GlobalTickCount + GarlandFreq;
            } else {
            if (LedStates[5]) {
                GPIOD->BSRR = GPIO_BSRR_BS5;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR5;  // Выключить (Reset)
            }
        }
        }
    else {
        if((GlobalTickCount >= LedTimersEnd[0])) {
            LedStates[0] = !LedStates[0];
            ledone = LedStates[0];
            LedTimersEnd[0] = GlobalTickCount + LedList[0];
            } else {
            if (LedStates[0]) {
                GPIOD->BSRR = GPIO_BSRR_BS0;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR0;  // Выключить (Reset)
            }
            }

        if((GlobalTickCount >= LedTimersEnd[1])) {
                LedStates[1] = !LedStates[1];
                ledtwo = LedStates[1];
                    LedTimersEnd[1] = GlobalTickCount + LedList[1];
                } else {
                if (LedStates[1]) {
                    GPIOD->BSRR = GPIO_BSRR_BS1;  // Включить (Set)
                } else {
                    GPIOD->BSRR = GPIO_BSRR_BR1;  // Выключить (Reset)
                }
            }

        if((GlobalTickCount >= LedTimersEnd[2])) {
            LedStates[2] = !LedStates[2];
            ledthree = LedStates[2];
            LedTimersEnd[2] = GlobalTickCount + LedList[2];
            } else {
            if (LedStates[2]) {
                GPIOD->BSRR = GPIO_BSRR_BS2;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR2;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[3])) {
            LedStates[3] = !LedStates[3];
            ledfour = LedStates[3];
            LedTimersEnd[3] = GlobalTickCount + LedList[3];
            } else {
            if (LedStates[3]) {
                GPIOD->BSRR = GPIO_BSRR_BS3;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR3;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[4])) {
            LedStates[4] = !LedStates[4];
            ledfive = LedStates[4];
            LedTimersEnd[4] = GlobalTickCount + LedList[4];
            } else {
            if (LedStates[4]) {
                GPIOD->BSRR = GPIO_BSRR_BS4;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR4;  // Выключить (Reset)
            }
        }

        if((GlobalTickCount >= LedTimersEnd[5])) {
            LedStates[5] = !LedStates[5];
            ledsix = LedStates[5];
            LedTimersEnd[5] = GlobalTickCount + LedList[5];
            } else {
            if (LedStates[5]) {
                GPIOD->BSRR = GPIO_BSRR_BS5;  // Включить (Set)
            } else {
                GPIOD->BSRR = GPIO_BSRR_BR5;  // Выключить (Reset)
            }
        }
    }
}
