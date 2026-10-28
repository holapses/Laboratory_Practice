#include <init.h>
#include <it_handlers.h>

void LedController(void);
void LedFreq(uint8_t Led);

uint16_t GlobalTickCount;
uint8_t CurLed = 0;
float LedList[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
_Bool WorkMode = 0;

while(1){

}

void LedController(void) {
    LedFreq(0);
    LedFreq(1);
    LedFreq(2);
    LedFreq(3);
    LedFreq(4);
    LedFreq(5);
}

void LedFreq(uint8_t Led) {
    
}