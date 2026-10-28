#include <init.h>
#include <it_handlers.h>

void LedController(void);
void LedFreq(uint8_t Led);

uint16_t GlobalTickCount;
uint8_t CurLed = 0;
float LedList[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
uint32_t LedTimersStart[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
uint32_t LedTimersEnd[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
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
        SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0)
    }

}

void LedFreq(uint8_t Led) {
    if(Led)
}