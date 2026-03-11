#include "beep_drivers.h"

#if APP_BEEP_ENABLE

static uint8_t beep_delay;

/**
 * @brief  Initialize Buzzer GPIO
 * @param  None
 * @retval None
 */
void BEEP_Init(void)
{
	GPIO_Init(BEEP_GPIO,OUTPUT|PUSHPULL);
	#if BEEP_GPIO_TYPE
    GPIO_ClearBit(BEEP_GPIO);
	#else
	GPIO_SetBit(BEEP_GPIO);
	#endif
}

/**
 * @brief  Turn on buzzer for a specified duration
 * @param  timeout : Duration in ms
 * @retval None
 */
void BEEP_On(uint8_t timeout)
{
    beep_delay = timeout;
	#if BEEP_GPIO_TYPE
    GPIO_SetBit(BEEP_GPIO);
	#else
	GPIO_ClearBit(BEEP_GPIO);
	#endif
}

/**
 * @brief  Buzzer timeout handler. To be called in SysTick interrupt (1ms interval)
 * @param  None
 * @retval None
 */
void BEEP_Timeout(void)
{
	if (beep_delay)
    {
        beep_delay--;
        if (beep_delay == 0)
        {
			#if BEEP_GPIO_TYPE
			GPIO_ClearBit(BEEP_GPIO);
			#else
			GPIO_SetBit(BEEP_GPIO);
			#endif
        }
    }
}

#endif
