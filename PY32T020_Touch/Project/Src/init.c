#include "init.h"
#include "main.h"  /* bring in HAL/LL macros and configuration */

/*
 * System clock initialization moved from main.c
 */
void SystemClockConfig(void)
{
#if (HSI_FREQUENCE == 48000000UL)
    /* Change system frequency */
    SET_BIT(RCC->CR, RCC_CR_HSION);
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), LL_RCC_HSICALIBRATION_48MHz);
    while ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) != (RCC_CR_HSIRDY)))
    {
        ;
    }
#else
    SET_BIT(RCC->CR, RCC_CR_HSION);
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_0);
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), LL_RCC_HSICALIBRATION_24MHz);
    while ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) != (RCC_CR_HSIRDY)))
    {
        ;
    }
#endif
    /* Set AHB divider: HCLK = SYSCLK */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    /* HSISYS used as SYSCLK clock source  */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
    {
        ;
    }
    /* Set APB1 divider */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    SystemCoreClockUpdate();
    /* Enable SYSCFG and PWR clocks */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_PWR_EnableBkUpAccess();
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Enable GPIOB clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    /* Enable GPIOF clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
#if APP_SYSTICK_ENABLE
    /* GPIO toggle for debug */
#if (SYSTICK_DEBUG_GPIO != NO_PIN && SYSTICK_DEBUG)
    GPIO_Init(SYSTICK_DEBUG_GPIO, OUTPUT | PUSHPULL);
    GPIO_ClearBit(SYSTICK_DEBUG_GPIO);
#endif
    /* Initialize Systick timer */
    SysTick_Config(SystemCoreClock / 1000000 * SYSTICK_TIMING_TIME);
    /* Set the interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, SYSTICK_IRQ_PRIORITY);
    /* Enable TIM Break, Update, Trigger and Commutation Interrupts */
    NVIC_EnableIRQ(SysTick_IRQn);
#endif
}
