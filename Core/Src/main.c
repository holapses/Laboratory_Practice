#include "stm32f429xx.h"

void RCC_Ini(void)
{
    /* 1. Настройка Flash, число циклов 5+1 */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);

    /* 2. Включаем питание для overdrive */
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);

    /* 3. Включаем режим Voltage Scale 1 */
    // SET_BIT(PWR->CR, PWR_CR_VOS_0 | PWR_CR_VOS_1); // по идее уже включено

    /* 4. Включаем overdrive, ODEN ВКЛ -> ORDY ГОТОВНОСТЬ */
    SET_BIT(PWR->CR, PWR_CR_ODEN);
    while ((PWR->CSR & PWR_CSR_ODRDY) == 0U) {}

    /* 4. ODSWEN Переключаемся на OD -> ODSWRDY ГОТОВНОСТЬ */
    SET_BIT(PWR->CR, PWR_CR_ODSWEN);
    while ((PWR->CSR & PWR_CSR_ODSWRDY) == 0U) {}

    /* 5. Переключаемся на HSI для случая, если перед этим были на PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSI);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {} // Проверка установки

    /* 6. Отлючаем PLL */
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) != 0U) {} // Проверка включения

    /* 7. Включаем тактирование HSE */
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); // отключаем обход
    SET_BIT(RCC->CR, RCC_CR_HSEON); // включаем HSE
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) {}

    SET_BIT(RCC->CR, RCC_CR_CSSON); // Детектор неисправностей HSE

    /* 8. Настраиваем множители PLL: M=4, N=180, P=2, Q=8 */
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLSRC |
               RCC_PLLCFGR_PLLM   |
               RCC_PLLCFGR_PLLN   |
               RCC_PLLCFGR_PLLP   |
               RCC_PLLCFGR_PLLQ,
               RCC_PLLCFGR_PLLSRC_HSE |
               (4U   << RCC_PLLCFGR_PLLM_Pos) |
               (180U << RCC_PLLCFGR_PLLN_Pos) |
               (0U   << RCC_PLLCFGR_PLLP_Pos) |
               (8U   << RCC_PLLCFGR_PLLQ_Pos));

    /* 9. Запускаем PLL  */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) {}

    /* 10. Настраиваем делители для шин после PLL */
    MODIFY_REG(RCC->CFGR,
               RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
               RCC_CFGR_HPRE_DIV1 |
               RCC_CFGR_PPRE1_DIV4 |
               RCC_CFGR_PPRE2_DIV2);

    /* 11. Переключаем тактирование на PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}
}

void EXTI_ITR_Ini(void)
{
    /* EXTI SYSCGF сидит на APB2 */
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    /* Связываем пины кнопок с EXIT */
    MODIFY_REG(SYSCFG->EXTICR[0],
            SYSCFG_EXTICR1_EXTI0_Msk |
            SYSCFG_EXTICR1_EXTI1_Msk |
            SYSCFG_EXTICR1_EXTI2_Msk,
            SYSCFG_EXTICR1_EXTI0_PC |
            SYSCFG_EXTICR1_EXTI1_PC |
            SYSCFG_EXTICR1_EXTI2_PC);

    /* Разрешаем прерывание EXIT и задаем нарастающий фронт */
    SET_BIT(EXTI->IMR, EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR2);


    /* Задаем приоритеты NVIC и разрешаем прерывание NVIC */
    NVIC_SetPriority(
        EXTI0_IRQn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)
    );
    NVIC_SetPriority(
        EXTI1_IRQn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)
    );
    NVIC_SetPriority(
        EXTI2_IRQn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)
    );

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
}

uint8_t BtnCount;

void EXTI0_IRQHandler(void)
{
    BtnCount++;

    SET_BIT(EXTI->PR, EXTI_PR_PR0);
}
void EXTI1_IRQHandler(void)
{
    BtnCount++;

    SET_BIT(EXTI->PR, EXTI_PR_PR1);
}
void EXTI2_IRQHandler(void)
{
    BtnCount++;

    SET_BIT(EXTI->PR, EXTI_PR_PR2);
}