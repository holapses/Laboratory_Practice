#define RCC *(uint32_t*)(0x40023800UL + 0x30UL)
#define RCC_GPIOB 0x02UL
#define RCC_GPIOC 0x04UL
#define GPIOB *(uint32_t*)(0x40020400UL)
#define GPIOC *(uint32_t*)(0x40020800UL)
#define GPIOB_MODER *(uint32_t*)(0x40020400UL + 0x00UL)
#define GPIOB_SET_RESET *(uint32_t*)(0x40020400UL + 0x18UL)
#define GPIOB_READ *(uint32_t*)(0x40020400UL + 0x10UL)
#define GPIOC_MODER *(uint32_t*)(0x40020800UL + 0x00UL)
#define GPIOC_SET_RESET *(uint32_t*)(0x40020800UL + 0x18UL)
#define GPIOC_READ *(uint32_t*)(0x40020800UL + 0x10UL)
#define GPIOB_PUPDR *(uint32_t*)(0x40020400UL + 0x0CUL)
#define GPIOC_PUPDR *(uint32_t*)(0x40020800UL + 0x0CUL)

#define PB7_SET (1UL << 7)
#define PB14_SET (1UL << 14)
#define PB0_SET 1UL
#define PB9_SET (1UL << 9)
#define B1_SET (1UL << 13)
#define B2_SET (1UL << 8)
#define B3_SET (1UL << 9)

#define BIT_SET(REG, BIT) (REG |= (1UL << BIT))
#define BIT_RESET(REG, BIT) (REG &= ~(1UL << BIT))