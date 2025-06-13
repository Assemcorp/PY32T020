/**
 ******************************************************************************
 * @file    main.c
 * @author  MCU Application Team
 * @author  AssemCorp
 * @brief   Main program body
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
#if APP_TK_ENABLE
static void TK_Loop(void);
uint32_t KeyFlag = 0;
#endif
/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/********************************************************
**    Function:   void SystemClockConfig(void)
**    Purpose:    System clock initialization
**    Input:      None
**    Output:     None
*********************************************************/
static void SystemClockConfig(void)
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
/********************************************************
**    Function:   int main(void)
**    Purpose:    Main program entry
**    Input:      None
**    Output:     None
*********************************************************/
int main(void)
{
	SystemClockConfig();
	/* User driver initialization */
	app_drivers_init();
/* User application initialization */
/* Touch key initialization */
#if APP_TK_ENABLE
	TK_Init();
#endif
	/* Start main loop */
	log_printf("start loop\r\n");
	while (1)
	{
#if APP_TK_ENABLE
		TK_Loop();
#endif
		app_drivers_loop();
	}
}
#if APP_SYSTICK_ENABLE
/********************************************************
**    Function:   void SysTick_Handler(void)
**    Purpose:    System tick interrupt handler, current timing is 1ms
**    Input:      None
**    Output:     None
*********************************************************/
void SysTick_Handler(void)
{
	static uint16_t Prescaler = 0;
#if (SYSTICK_DEBUG_GPIO != NO_PIN && SYSTICK_DEBUG)
	GPIO_ToggleBit(SYSTICK_DEBUG_GPIO);
#endif
	Prescaler++;
	if (Prescaler >= (1000 / SYSTICK_TIMING_TIME))
	{
		Prescaler = 0;
		app_drivers_timer();
#if APP_TK_ENABLE
		TK_TimerHandler(1);
#endif
	}
}
#endif
#if APP_TK_ENABLE
/********************************************************
**    Function:   void TK_Loop(void)
**    Purpose:    Touch key scan and status read
**    Input:      None
**    Output:     None
*********************************************************/
static void TK_Loop(void)
{
	uint32_t temp;
	uint8_t i;
	/* Touch key state machine */
	TK_MainFsm();
	/*************************************************************************************************
	   TKCtr.KeyFlags is the interface data for all touch keys.
	   Each bit of TKCtr.KeyFlags corresponds to a key status. 1 means pressed, 0 means released.
	*************************************************************************************************/
	temp = TKCtr.KeyFlags ^ KeyFlag;
	if (temp != 0)
	{
		KeyFlag = TKCtr.KeyFlags;
		log_printf("KeyFlag:0X%X\r\n", KeyFlag);
#if APP_SMG_ENABLE
		LED_Show(KeyFlag); // Show corresponding LED
#endif
		for (i = 0; i < TKCtr.TouchKeyChCnt; i++)
		{
			if (temp & 0X01)
			{
				if (KeyFlag & ((0X01) << i)) // Key pressed
				{
#if APP_BEEP_ENABLE
					BEEP_On(100);
#endif
#if APP_SMG_ENABLE
					SMG_Show(i + 1);
#endif
					switch (i)
					{
					/* KEY0 pressed */
					case 0:

						break;
					/* KEY1 pressed */
					case 1:
						break;
					}
				}
				else
				{
					switch (i)
					{
					/* KEY0 released */
					case 0:
						break;
					/* KEY1 released */
					case 1:
						break;
					}
				}
			}
			temp >>= 1;
		}
	}
#if (LIB_TYPE > 0)
	if (TKCtr.SliderOrWheelPosition[0] != -1)
	{
	}
#endif
}
#endif
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* Users can add their own printing information as needed,
	   for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* Infinite loop */
	while (1)
	{
		;
	}
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/