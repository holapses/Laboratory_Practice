#include <init.h>
#include <it_handlers.h>

void LedController(void);



uint32_t GlobalTickCount;
uint8_t CurLed = 0; 
uint16_t LedList[6] = {0, 0, 0, 0, 0, 0};
uint32_t LedTimersEnd[6] = {0, 0, 0, 0, 0, 0};
_Bool LedStates[6] = {0, 0, 0, 0, 0, 0};
_Bool WorkMode = 0;

int main(void) {
    GPIO_Ini();
    RCC_Ini();
    EXTI_ITR_Ini();
    SysTick_Init();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODE7_0;

    while(1){
        GPIOB->BSRR |= GPIO_BSRR_BR7;
    }
}

void LedController(void) {
    if(GlobalTickCount >= LedTimersEnd[0]) {
        LedStates[0] = !LedStates[0];
        LedTimersEnd[0] = GlobalTickCount + LedList[0];
    } else {
        if(!LedStates[0]) GPIOD->BSRR |= GPIO_BSRR_BR0;
        else GPIOD->BSRR |= GPIO_BSRR_BS0;
    }

    if(GlobalTickCount >= LedTimersEnd[1]) {
        LedStates[1] = !LedStates[1];
        LedTimersEnd[1] = GlobalTickCount + LedList[1];
    } else {
        if(!LedStates[1]) GPIOD->BSRR |= GPIO_BSRR_BR1;
        else GPIOD->BSRR |= GPIO_BSRR_BS1;
    }

    if(GlobalTickCount >= LedTimersEnd[2]) {
        LedStates[2] = !LedStates[2];
        LedTimersEnd[2] = GlobalTickCount + LedList[2];
    } else {
        if(!LedStates[2]) GPIOD->BSRR |= GPIO_BSRR_BR2;
        else GPIOD->BSRR |= GPIO_BSRR_BS2;
    }

    if(GlobalTickCount >= LedTimersEnd[3]) {
        LedStates[3] = !LedStates[3];
        LedTimersEnd[3] = GlobalTickCount + LedList[3];
    } else {
        if(!LedStates[3]) GPIOD->BSRR |= GPIO_BSRR_BR3;
        else GPIOD->BSRR |= GPIO_BSRR_BS3;
    }

    if(GlobalTickCount >= LedTimersEnd[4]) {
        LedStates[4] = !LedStates[4];
        LedTimersEnd[4] = GlobalTickCount + LedList[4];
    } else {
        if(!LedStates[4]) GPIOD->BSRR |= GPIO_BSRR_BR4;
        else GPIOD->BSRR |= GPIO_BSRR_BS4;
    }

    if(GlobalTickCount >= LedTimersEnd[5]) {
        LedStates[5] = !LedStates[5];
        LedTimersEnd[5] = GlobalTickCount + LedList[5];
    } else {
        if(!LedStates[5]) GPIOD->BSRR |= GPIO_BSRR_BR5;
        else GPIOD->BSRR |= GPIO_BSRR_BS5;
    }

}
