#include "drivers.h"

volatile uint32_t EXTI_Flag;

#if (APP_TM1624_ENABLE && TM1624_DISP_TEST)
uint8_t TM1624_Show[14];
uint16_t TM1624_Time;
#endif

#if (APP_TM1640_ENABLE && TM1640_DISP_TEST)
uint8_t TM1640_Show[16];
uint16_t TM1640_Time;
#endif

#if APP_IWDG_ENABLE
void IWDG_Init(void)
{
	/* Enable LSI */
	LL_RCC_LSI_Enable();
	while (LL_RCC_LSI_IsReady() == 0U) {;}

	/* Enable IWDG */
	LL_IWDG_Enable(IWDG);
	/* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers */
	LL_IWDG_EnableWriteAccess(IWDG);
	/* Set IWDG prescaler */
	LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_32); /* T=1MS */
	/* Set IWDG reload value */
	LL_IWDG_SetReloadCounter(IWDG, IDWG_RELOAD_VALUE); /* 1ms*1000=1s */
	/* Check if all flags Prescaler, Reload & Window Value Update are reset or not */
	while (LL_IWDG_IsReady(IWDG) == 0U) 
	{
		;
	}
	/* Reloads IWDG counter with value defined in the reload register */
	LL_IWDG_ReloadCounter(IWDG);
}
#endif

/**
 * @brief  Initialize all peripheral drivers
 * @param  None
 * @retval None
 */
void app_drivers_init(void)
{
	#if APP_UART_ENABLE
	/* Initialize UART module */
	#if UART1_ENABLE
	UART1_Init(UART1_BAUDRATE);
	#endif
	#if UART2_ENABLE
	UART2_Init(UART2_BAUDRATE);
	#endif
	#if UART3_ENABLE
	UART3_Init(UART3_BAUDRATE);
	#endif
	#endif

	#if	OB_USER_OPTION
	/* Configure FLASH option bytes */
	uint8_t config = 0; 
	if(READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) != OB_GPIO_PIN_MODE)
		config = 1;
	else if(READ_BIT(FLASH->OPTR, FLASH_OPTR_BOR_EN) != OB_BOR_EN)
		config = 1;
	else if(READ_BIT(FLASH->OPTR, FLASH_OPTR_BOR_LEV) != OB_BOR_LEVEL)
		config = 1;
	else if(READ_BIT(FLASH->OPTR, FLASH_OPTR_IWDG_SW) != OB_IWDG_MODE)
		config = 1;
	else if(READ_BIT(FLASH->OPTR, FLASH_OPTR_IWDG_STOP) != OB_IWDG_STOP)
		config = 1;
	
	if(config)
	{
		/* OPTION Program */
		FLASH_OBProgramInitTypeDef OBInitCfg = {0};

		FLASH_Unlock();        /* Unlock Flash */
		FLASH_OB_Unlock();     /* Unlock Option */

		OBInitCfg.OptionType = OPTIONBYTE_USER;

		OBInitCfg.USERType = (OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_IWDG_STOP | OB_USER_NRST_MODE);

		OBInitCfg.USERConfig = (OB_BOR_EN | OB_BOR_LEVEL | OB_IWDG_MODE | OB_IWDG_STOP | OB_GPIO_PIN_MODE);

		/* Option Program */
		FLASH_OBProgram(&OBInitCfg);
		FLASH_Lock();      /* Lock Flash */
		FLASH_OB_Lock();   /* Lock Option */
		/* Option Launch */
		FLASH_OB_Launch();
	}	
	#endif

	#if APP_IWDG_ENABLE
	IWDG_Init();
	#endif

	#if APP_SMG_ENABLE
	/* Initialize 7-segment display scanning */
    SMG_Init();
	#endif

	#if APP_BEEP_ENABLE
	/* Initialize buzzer */
	BEEP_Init();
	#endif

	#if APP_IR_RECEIVED_ENABLE
	IR_Received_Init();
	#endif

	#if APP_TIM1_ENABLE
	/* Initialize Timer 1 */
	TIM1_Init();
	#elif APP_TIM1_PWM_ENABLE
	/* Initialize Timer 1 for PWM output */
	TIM1_PWM_Init();
	#endif

	#if APP_TIM14_ENABLE
	/* Initialize Timer 14 */
	TIM14_Init();
	#elif APP_TIM14_PWM_ENABLE
	/* Initialize Timer 14 for PWM output */
	TIM14_PWM_Init();
	#endif

	#if APP_ADC_ENABLE
	/* Initialize ADC module */
	ADC_Init();
	#endif

	#if APP_SPI_LED_ENABLE
	/* Initialize SPI to drive WS2812B LEDs */
	SPI_LED_Init();
	argb_init();
	#endif

	#if APP_USER_OTP_ENABLE
	/* Read user data */
	#if LVD_WRITE_USER_DATA
	if(User_Cache_Read(0,&power_count,1))
	{
		log_printf("power_count:%d\r\n",power_count);
	}
	else
	{
		log_printf("first power\r\n");
		power_count = 0;
	}
	#endif
	#endif

	#if APP_TM1624_ENABLE
	TM1624_Init();
	#endif

	#if APP_TM1640_ENABLE
	TM1640_Init();
	#endif
}	

/**
 * @brief  Main driver polling loop - call inside while(1)
 * @param  None
 * @retval None
 */
void app_drivers_loop(void)
{
	#if APP_IR_RECEIVED_ENABLE
	Ir_TypeDef remote;
	if(IR_Press(&remote))
	{
		log_printf("address:0X%X ",remote.ir_address);	// Received address
		log_printf("command:0X%X ",remote.ir_command);	// Received command
		log_printf("count:%d\r\n",remote.ir_count);		// Received count
	}
	#endif

	/* EXTI flag */
	if(EXTI_Flag != 0)
	{
		log_printf("EXTI_Flag:0X%X\r\n",EXTI_Flag);
		EXTI_Flag = 0;
	}

	#if APP_IWDG_ENABLE
	/* Feed the watchdog */
	LL_IWDG_ReloadCounter(IWDG);
	#endif

	#if APP_ADC_ENABLE
	ADC_Loop();
	#endif

	#if APP_UART_ENABLE
	UART_Loop();
	#endif

	#if (APP_TM1624_ENABLE && TM1624_DISP_TEST)
	if(TM1624_Time > 500)
	{
		uint8_t i;
		TM1624_Time = 0;
		for(i = 0;i < 14;i++)
		{
			TM1624_Show[i] = ~TM1624_Show[i];
		}
		TM1624_Display_Update(TM1624_Show,14,TM1624_ON | TM1624_DISP_DIM);
	}
	#endif
	
	#if (APP_TM1640_ENABLE && TM1640_DISP_TEST)
	if(TM1640_Time > 500)
	{
		uint8_t i;
		TM1640_Time = 0;
		for(i = 0;i < 16;i++)
		{
			TM1640_Show[i] = ~TM1640_Show[i];
		}
		TM1640_Display_Update(TM1640_Show,16,TM1640_ON | TM1640_DISP_DIM);
	}
	#endif
}

/**
 * @brief  1ms timer callback - call from SysTick ISR
 * @param  None
 * @retval None
 */
void app_drivers_timer(void)
{
	#if (APP_TM1624_ENABLE && TM1624_DISP_TEST)
	TM1624_Time++;
	#endif

	#if (APP_TM1640_ENABLE && TM1640_DISP_TEST)
	TM1640_Time++;
	#endif

	#if APP_SMG_ENABLE
	SMG_Scan();
	#endif

	#if APP_BEEP_ENABLE
	BEEP_Timeout();
	#endif

	#if APP_ADC_ENABLE
	adc_tick++;
	#endif

	#if APP_UART_ENABLE
	UART_TimeOut();
	#endif

	#if APP_SPI_LED_ENABLE
	argb_time++;
	#endif

}

/**
 * @brief  EXTI 0-15 interrupt callback handler
 *         Note: Runs in interrupt context, do not use blocking delays.
 * @param  PR : Interrupt pending register flags (BIT0=EXTI0, etc.)
 * @retval None
 */
void EXTI0_15_IRQHandlerCallback(uint32_t PR)
{
	uint8_t i;
	for(i = 0;i < 16;i++)
	{
		/* Handle EXTI interrupt request */
		if(PR & (1 << i))
		{
			/* EXTI interrupt triggered */
			EXTI_Flag |= 1 << i;
		}
	}
}

#if APP_TIM1_ENABLE
/**
 * @brief  Timer 1 period elapsed callback
 * @param  None
 * @retval None
 */
void TIM1_PeriodElapsedCallback(void)
{
	#if (APP_IR_RECEIVED_ENABLE == 1 && D_IR_TIM == 1)
	IR_Received_Scan();
	#endif
}
#endif

#if APP_TIM14_ENABLE
/**
 * @brief  Timer 14 period elapsed callback
 * @param  None
 * @retval None
 */
void TIM14_PeriodElapsedCallback(void)
{
	#if (APP_IR_RECEIVED_ENABLE == 1 && D_IR_TIM == 14)
	IR_Received_Scan();
	#endif
}
#endif

/**
 * @brief  Approximate NOP-based microsecond delay
 * @param  nus : Delay time in microseconds
 * @retval None
 */
void nop_delay_xus(uint16_t nus)
{
    __IO uint32_t wait_loop_index = (nus * (fac_us / 12U));
    while (wait_loop_index != 0U)
    {
        wait_loop_index--;
    }
}

/**
 * @brief  Precise microsecond delay using SysTick
 * @param  nus : Delay time in microseconds
 * @retval None
 */
void delay_us(uint16_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
	uint32_t reload;

    reload = SysTick->LOAD; // Reload value
    ticks = nus * fac_us;            // Needed tick count
    told = SysTick->VAL; // Initial tick value upon entry

    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow; // Note: SysTick is a decrementing counter
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break; // Break when configured time is reached
        }
    };
}

/**
 * @brief  Millisecond delay using SysTick
 * @param  nms : Delay time in milliseconds
 * @retval None
 */
void delay_ms(uint16_t nms)
{
    for(uint16_t i = 0;i < nms;i++)
	{
		delay_us(1000);
	}
}
