#include <it_handlers.h>

uint8_t Btn1Count;
uint8_t Btn2Count;
uint8_t Btn3Count;

uint16_t ExternInterruptTickCount;
extern uint16_t GlobalTickCount;
extern _Bool WorkMode;
extern uint8_t CurLed;
extern float LedList[6];

void EXTI0_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR0);
    if(ExternInterruptTickCount >= DELAY_BUTTON_FILTER){
        Btn1Count++;
        ExternInterruptTickCount = 0;
        WorkMode = !WorkMode;
        Btn2Count = 0;
    }
}
void EXTI1_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR1);
    if(ExternInterruptTickCount >= DELAY_BUTTON_FILTER){
        Btn2Count++;
        ExternInterruptTickCount = 0;
        if(WorkMode == 0) {
            if(Btn2Count == 3) {
                LedList[CurLed] = 833;
                Btn2Count = 0;
            }
            else if(Btn2Count == 1) LedList[CurLed] = 385;
            else if(Btn2Count == 2) LedList[CurLed] = 208;
        } else {
            if(Btn2Count == 3) {
                LedList[CurLed] = 2500;
                Btn2Count = 0;
            }
            else if(Btn2Count == 1) LedList[CurLed] = 556;
            else if(Btn2Count == 2) LedList[CurLed] = 333;
        }
    }
}
void EXTI2_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR2);
    if(ExternInterruptTickCount >= DELAY_BUTTON_FILTER){
        Btn3Count++;
        Btn2Count = 0;
        ExternInterruptTickCount = 0;
        CurLed++;
        if(CurLed == 6) CurLed = 0;
    }
}
void SysTick_Handler(void) {
    GlobalTickCount++;
    ExternInterruptTickCount++;
}

