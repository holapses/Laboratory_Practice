#include <init.h>
#include <it_handlers.h>

void LedController(void);
void LedFreq(uint8_t Led);

uint16_t GlobalTickCount;
uint8_t CurLed = 0;
float LedList[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float LedTimersEnd[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
_Bool LedStates[6] = {0, 0, 0, 0, 0, 0};
_Bool WorkMode = 0;

int main(void) {
    GPIO_Ini();
    RCC_Ini();
    ITR_Ini();
    SysTick_Init();

    while(1){
    }
}

void LedController(void) {
    if(GlobalTickCount >= LedTimersEnd[0]) {
        if(!LedStates[0]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR0);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);
    } else {
        LedStates[0] = !LedStates[0];
        LedTimersEnd[0] = GlobalTickCount + ((1.0 / (2.0 * LedList[0])) * 1000);
    }

    if(GlobalTickCount >= LedTimersEnd[1]) {
        if(!LedStates[1]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR1);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS1);
    } else {
        LedStates[1] = !LedStates[1];
        LedTimersEnd[1] = GlobalTickCount + ((1.0 / (2.0 * LedList[1])) * 1000);
    }

    if(GlobalTickCount >= LedTimersEnd[2]) {
        if(!LedStates[2]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR2);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS2);
    } else {
        LedStates[2] = !LedStates[2];
        LedTimersEnd[2] = GlobalTickCount + ((1.0 / (2.0 * LedList[2])) * 1000);
    }

    if(GlobalTickCount >= LedTimersEnd[3]) {
        if(!LedStates[3]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR3);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS3);
    } else {
        LedStates[3] = !LedStates[3];
        LedTimersEnd[3] = GlobalTickCount + ((1.0 / (2.0 * LedList[3])) * 1000);
    }

    if(GlobalTickCount >= LedTimersEnd[4]) {
        if(!LedStates[4]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR4);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS4);
    } else {
        LedStates[4] = !LedStates[4];
        LedTimersEnd[4] = GlobalTickCount + ((1.0 / (2.0 * LedList[4])) * 1000);
    }

    if(GlobalTickCount >= LedTimersEnd[5]) {
        if(!LedStates[5]) SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR5);
        else SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS5);
    } else {
        LedStates[5] = !LedStates[5];
        LedTimersEnd[5] = GlobalTickCount + ((1.0 / (2.0 * LedList[5])) * 1000);
    }

}
