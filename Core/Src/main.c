
#include "stm32f429xx.h"

void RCC_Ini(void)
{
    /* 1. РќР°СЃС‚СЂР°РёРІР°РµРј Flash РґРѕ РїРѕРІС‹С€РµРЅРёСЏ С‡Р°СЃС‚РѕС‚С‹ */
    MODIFY_REG(FLASH->ACR,
               FLASH_ACR_LATENCY,
               FLASH_ACR_LATENCY_5WS);

    SET_BIT(FLASH->ACR,
            FLASH_ACR_PRFTEN |
            FLASH_ACR_ICEN   |
            FLASH_ACR_DCEN);

    /* 2. Р’РєР»СЋС‡Р°РµРј С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Р±Р»РѕРєР° РїРёС‚Р°РЅРёСЏ */
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);

    /* 3. Р’С‹Р±РёСЂР°РµРј Voltage Scale 1 */
    SET_BIT(PWR->CR, PWR_CR_VOS_0 | PWR_CR_VOS_1);

    /* 4. Р’РєР»СЋС‡Р°РµРј Over-drive РґР»СЏ СЂР°Р±РѕС‚С‹ РЅР° 180 РњР“С† */
    SET_BIT(PWR->CR, PWR_CR_ODEN);
    while ((PWR->CSR & PWR_CSR_ODRDY) == 0U) {}

    SET_BIT(PWR->CR, PWR_CR_ODSWEN);
    while ((PWR->CSR & PWR_CSR_ODSWRDY) == 0U) {}

    /* 5. РџРµСЂРµРєР»СЋС‡Р°РµРј SYSCLK РЅР° HSI РїРµСЂРµРґ РїРµСЂРµРЅР°СЃС‚СЂРѕР№РєРѕР№ PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSI);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {}

    /* 6. Р’С‹РєР»СЋС‡Р°РµРј PLL Рё Р¶РґС‘Рј, РїРѕРєР° РѕРЅР° РѕСЃС‚Р°РЅРѕРІРёС‚СЃСЏ */
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) != 0U) {}

    /* 7. Р’РєР»СЋС‡Р°РµРј РІРЅРµС€РЅРёР№ РёСЃС‚РѕС‡РЅРёРє HSE */
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) {}

    /* 8. РќР°СЃС‚СЂР°РёРІР°РµРј РїР°СЂР°РјРµС‚СЂС‹ PLL: M=4, N=180, P=2, Q=8 */
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

    /* 9. Р—Р°РїСѓСЃРєР°РµРј PLL Рё Р¶РґС‘Рј РіРѕС‚РѕРІРЅРѕСЃС‚Рё */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) {}

    /* 10. РќР°СЃС‚СЂР°РёРІР°РµРј РґРµР»РёС‚РµР»Рё С€РёРЅ */
    MODIFY_REG(RCC->CFGR,
               RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
               RCC_CFGR_HPRE_DIV1 |
               RCC_CFGR_PPRE1_DIV4 |
               RCC_CFGR_PPRE2_DIV2);

    /* 11. РџРµСЂРµРєР»СЋС‡Р°РµРј СЃРёСЃС‚РµРјРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅР° PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}
}

void EXTI_ITR_Ini(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    MODIFY_REG(SYSCFG->EXTICR[3],
               SYSCFG_EXTICR4_EXTI13_Msk,
               SYSCFG_EXTICR4_EXTI13_PC);

    SET_BIT(EXTI->IMR, EXTI_IMR_MR13);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR13);

    NVIC_SetPriority(
        EXTI15_10_IRQn,
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)
    );

    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

uint8_t BtnCount;

void EXTI15_10_IRQHandler(void)
{
    BtnCount++;

    SET_BIT(EXTI->PR, EXTI_PR_PR13);
}