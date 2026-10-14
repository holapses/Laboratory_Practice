#include <stdint.h>
//#include <init.h>
#include <stm32f429xx.h>
#define MAX_TIME_LED 5000.0
#define MAX_TIME_SHIM 10

void led_switch(_Bool direction);
void led_brightness(uint32_t time1, uint32_t time2);
void shim(void);
void leds_on(void);
void leds_off(void);

void run_advance(void);
void run_cmsis_ver(void);
void run_simple_ver(void);
//void run_define_ver(void);

_Bool leds_state = 0;
uint8_t brightness = 0;
uint8_t led_amount = 0;
uint32_t button_time = 0;
uint32_t leds_time = 0;
_Bool leds_time_state = 0;

int main(void){
    HAL_Init();
    run_advance();
}

void run_advance(void) {
    uint32_t time_b1 = 0;

    // LEDS - PB4 PB5 PB6 PB8
    // BUTTONS - PB9 PB10
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER &= ~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER8); //Clean LED bits
    GPIOB->MODER |= (GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER8_0); //Set output for LED

    GPIOB->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10); //Clean button bits
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10); //Clean pupdr bits
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0); //Pull up for bittons

    while(1) {
        shim();

        if((GPIOB->IDR & GPIO_IDR_ID9) == 0) {
            HAL_Delay(20); //Drebezg
            if((GPIOB->IDR & GPIO_IDR_ID9) == 0) {
                button_time = HAL_GetTick();
                while((GPIOB->IDR & GPIO_IDR_ID9) == 0); //Wait holding
                if((HAL_GetTick() - button_time) <= 500) {
                    led_switch(0);
                } else {
                    time_b1 = HAL_GetTick() - button_time;
                }
            }
        }

        if((GPIOB->IDR & GPIO_IDR_ID10) == 0) {
            HAL_Delay(20); //Drebezg
            if((GPIOB->IDR & GPIO_IDR_ID10) == 0) {
                button_time = HAL_GetTick();
                while((GPIOB->IDR & GPIO_IDR_ID10) == 0); //Wait holding
                if((HAL_GetTick() - button_time) <= 500) {
                    led_switch(1);
                } else {
                    led_brightness(time_b1, HAL_GetTick() - button_time);
                }
            }
        }
    }
}

void leds_on(void) {
    switch(led_amount)
    {
    case 1:
        GPIOB->BSRR = (GPIO_BSRR_BS4);
        break;
    case 2:
        GPIOB->BSRR = (GPIO_BSRR_BS4 | GPIO_BSRR_BS5);
        break;
    case 3:
        GPIOB->BSRR = (GPIO_BSRR_BS4 | GPIO_BSRR_BS5 | GPIO_BSRR_BS6);
        break;
    case 4:
        GPIOB->BSRR = (GPIO_BSRR_BS4 | GPIO_BSRR_BS5 | GPIO_BSRR_BS6 | GPIO_BSRR_BS8);
        break;
    }
}

void leds_off(void) {
    switch(led_amount)
    {
    case 1:
        GPIOB->BSRR = (GPIO_BSRR_BR4);
        break;
    case 2:
        GPIOB->BSRR = (GPIO_BSRR_BR4 | GPIO_BSRR_BR5);
        break;
    case 3:
        GPIOB->BSRR = (GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6);
        break;
    case 4:
        GPIOB->BSRR = (GPIO_BSRR_BR4 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
        break;
    }
}

void shim(void) {
    uint32_t duration_on = ((uint32_t)(brightness) * MAX_TIME_SHIM) / 100;

    if(leds_state == 1) {
        if(leds_time_state) {
            leds_time_state = 0;
            leds_time = HAL_GetTick();
        }
        if((HAL_GetTick() - leds_time) >= duration_on){
            leds_state = 0;
            leds_time_state = 1;
        }
        leds_on();
    }
    
    if(leds_state == 0) {
        if(leds_time_state) {
            leds_time_state = 0;
            leds_time = HAL_GetTick();
        }
        if(HAL_GetTick() - leds_time >= (MAX_TIME_SHIM - duration_on)) {
            leds_state = 1;
            leds_time_state = 1;
        }
        leds_off();
    }
}

void led_switch(_Bool direction) {
    if(direction) {
        if(led_amount < 4) {
            led_amount++;
        }
    } else {
        if(led_amount > 0) {
            led_amount--;
        }
    }
}

void led_brightness(uint32_t time1, uint32_t time2) {
    uint32_t time = 0;
    if(time1 > time2) {
        time = time1 - time2;
    } else {
        time = time2 - time1;
    }

    uint32_t temp_brightness = (uint32_t)(((double)(time) / MAX_TIME_LED) * 100.0);
    if(temp_brightness >= 100) {
        brightness = 100;
    } else if(temp_brightness >= 0) {
        brightness = temp_brightness;
    } else {
        brightness = 0;
    }
}

void run_cmsis_ver(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER7 | GPIO_MODER_MODER14);
    GPIOB->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER14_0);

    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR9_0);

    while(1) {
        if(work_mode == 1) {
            GPIOB->BSRR = GPIO_BSRR_BS9; //ON control diod
        } else {
            if((GPIOB->IDR & GPIO_IDR_ID9) == 0) {
                GPIOB->BSRR = GPIO_BSRR_BS0; //ON GREEN
            } else {
                GPIOB->BSRR = GPIO_BSRR_BR0; // OFF GREEN
            }
            GPIOB->BSRR |= GPIO_BSRR_BR9; //OFF C_DIOD
        }

        if((GPIOC->IDR & GPIO_IDR_ID13) != 0) {
            GPIOB->MODER &= ~(GPIO_MODER_MODER9); //ReGister input for PB9
            GPIOB->PUPDR |= GPIO_PUPDR_PUPD9_0;
            work_mode = 0;
            GPIOB->BSRR |= GPIO_BSRR_BS14; //ON RED
        } else {
            GPIOB->BSRR |= GPIO_BSRR_BR14; // OFF RED
        }

        if((GPIOB->IDR & GPIO_IDR_ID8) == 0) {
            GPIOB->MODER |= GPIO_MODER_MODER9_0;
            work_mode = 1;
            GPIOB->BSRR |= GPIO_BSRR_BS7; //ON BLUE
        } else {
            GPIOB->BSRR |= GPIO_BSRR_BR7;
        }
    }
}

void run_simple_ver(void) {

    *(uint32_t*)(0x40023800UL + 0x30UL) |= (1UL << 1) | (1UL << 2); //Clock on port B and C

    *(uint32_t*)(0x40020400UL + 0x00UL) |= 1UL; //Register moder - Output mode for PB0(GREEN)
    *(uint32_t*)(0x40020400UL + 0x00UL) |= (1UL << 14); //Register moder - Output mode for PB7(BLUE)
    *(uint32_t*)(0x40020400UL + 0x00UL) |= (1UL << 28); //Register moder - Output mode for PB14(RED)

    *(uint32_t*)(0x40020400UL + 0x0CUL) |= (1UL << 16); //Register PUPDR pull-up for PB8
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= (1UL << 18); //Register PUPDR pull-up for PB9

    while(1) {
        if(work_mode == 1) {
                *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 9); //ON DIODcontrol
            } else {
                if(((*(uint32_t*)(0x40020400UL + 0x10UL)) & (1UL << 9)) == 0) { //if button3 ON
                    *(uint32_t*)(0x40020400UL + 0x18UL) |= 1UL; //ON DIOD(green)
                } else {
                    *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 16);
                }
                *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 25); //Off DIODcontrol
            }

        if(((*(uint32_t*)(0x40020800UL + 0x10UL)) & (1UL << 13)) != 0) { //if button1 ON
            *(uint32_t*)(0x40020400UL + 0x00UL) &= ~(1UL << 18); //Register moder - Input mode for PB9
            *(uint32_t*)(0x40020400UL + 0x0CUL) |= (1UL << 18); //Register PUPDR pull-up for PB9
            work_mode = 0;
            *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 14); //ON DIOD(red)
        } else {
            *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 30);
        }

        if(((*(uint32_t*)(0x40020400UL + 0x10UL)) & (1UL << 8)) == 0) { //if button2 ON
            *(uint32_t*)(0x40020400UL + 0x00UL) |= (1UL << 18); //Register moder - Output mode for PB9
            work_mode = 1;
            *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 7); //ON DIOD(blue)
        } else {
            *(uint32_t*)(0x40020400UL + 0x18UL) |= (1UL << 23);
        }
    }
}

/*
void run_define_ver(void) {
    RCC |= RCC_GPIOB | RCC_GPIOC; //Clock GPIOB GPIOC

    GPIOB_MODER |= PB0_SET; //PB0 OUTPUT
    GPIOB_MODER |= (1UL << 14); //PB7 OUTPUT
    GPIOB_MODER |= (1UL << 28); //PB14 OUTPUT

    GPIOB_PUPDR |= (1UL << 16); //Pull Up PB8
    GPIOB_PUPDR |= (1UL << 18); //Pull Up PB9

    while(1) {
        if(work_mode == 1) {
            GPIOB_SET_RESET |= PB9_SET; //ON control diod
        } else {
            if((GPIOB_READ & B3_SET) == 0) {
                GPIOB_SET_RESET |= PB0_SET; //ON GREEN
            } else {
                GPIOB_SET_RESET |= (1UL << 16); // OFF GREEN
            }
            GPIOB_SET_RESET |= (1UL << 25); //OFF C_DIOD
        }

        if((GPIOC_READ & B1_SET) != 0) {
            GPIOB_MODER &= ~(1UL << 18); //Refister input for PB9
            GPIOB_PUPDR |= (1UL << 18);
            work_mode = 0;
            GPIOB_SET_RESET |= PB14_SET; //ON RED
        } else {
            GPIOB_SET_RESET |= (1UL << 30); // OFF RED
        }

        if((GPIOB_READ & B2_SET) == 0) {
            GPIOB_MODER |= (1UL << 18);
            work_mode = 1;
            GPIOB_SET_RESET |= PB7_SET; //ON BLUE
        } else {
            GPIOB_SET_RESET |= (1UL << 23);
        }
    }
}

void test(void) {
    RCC |= RCC_GPIOB | RCC_GPIOC; //Clock GPIOB GPIOC

    GPIOB_MODER |= PB0_SET; //PB0 OUTPUT
    GPIOB_MODER |= (1UL << 14); //PB7 OUTPUT
    GPIOB_MODER |= (1UL << 28); //PB14 OUTPUT

    GPIOB_PUPDR |= (1UL << 16); //Pull Up PB8
    GPIOB_PUPDR |= (1UL << 18); //Pull Up PB9
    
    while(1){
        if((GPIOB_READ & B3_SET) == 0) {
            GPIOB_SET_RESET |= PB0_SET; //ON GREEN
        } else {
            GPIOB_SET_RESET |= (1UL << 16); // OFF GREEN
        }
    }
}
*/