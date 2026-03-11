#include "tim14_drivers.h"
#if APP_TIM14_ENABLE
/**
 * @brief  TIM14_Init
 * @param  None
 * @retval None
 */
void TIM14_Init(void)
{
	LL_TIM_InitTypeDef TimHandle = {0};
	uint32_t Prescale;
	uint32_t Autoreload;
	uint32_t Frequency = 1000000 / TIM14_TIMING_TIME;
	/**
 * @brief  Documentation
 */
	#if (TIM14_DEBUG_GPIO != NO_PIN && TIM14_DEBUG)
	GPIO_Init(TIM14_DEBUG_GPIO,OUTPUT|PUSHPULL);
	GPIO_ClearBit(TIM14_DEBUG_GPIO);
	#endif
	for(Prescale = 1U; Prescale < 0xFFFFU; Prescale++)   /* prescale could be 0~0xFFFF */
    {
        Autoreload = (SystemCoreClock / Frequency) / Prescale;
        /* If target value is larger than CNR, need to use a larger prescaler */
        if(Autoreload < (0x10000U))
        {
            break;
        }
    }
    /* Enable TIM14 clock */
	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM14);
	/* TIM Config */
	TimHandle.ClockDivision     = LL_TIM_CLOCKDIVISION_DIV1;        /* Clock division: tDTS=tCK_INT */
	TimHandle.CounterMode       = LL_TIM_COUNTERMODE_UP;            /* CounterMode:Up */
	TimHandle.RepetitionCounter = 0;                                /* repetition counter value:1-1 */
    TimHandle.Autoreload = Autoreload - 1;                             /**
 * @brief  Documentation
 */
	TimHandle.Prescaler = Prescale - 1;                               	/* Prescaler:24 - 1 */
	/* Initialize TIM14 */
	LL_TIM_Init(TIM14,&TimHandle);
	/* Enable the TIM Update interrupt */
	LL_TIM_EnableIT_UPDATE(TIM14);
	/* Enable TIM1  */
	LL_TIM_EnableCounter(TIM14);
	#if TIM14_IRQ_ENABLE
	/* Set the interrupt priority */
    NVIC_SetPriority(TIM14_IRQn, TIM14_IRQ_PRIORITY);
    /* Enable TIM Break, Update, Trigger and Commutation Interrupts */
    NVIC_EnableIRQ(TIM14_IRQn);
	#endif
}
/**
 * @brief  TIM14_PeriodElapsedCallback
 * @param  None
 * @retval None
 */
__weak void TIM14_PeriodElapsedCallback(void)
{


}
/**
 * @brief  TIM14_IRQHandler
 * @param  None
 * @retval None
 */
void TIM14_IRQHandler(void)
{
	/* TIM Update event */
	if(LL_TIM_IsActiveFlag_UPDATE(TIM14) != 0)
	{
		LL_TIM_ClearFlag_UPDATE(TIM14);
		/**
 * @brief  Documentation
 */
		#if (TIM14_DEBUG_GPIO != NO_PIN && TIM14_DEBUG)
		GPIO_ToggleBit(TIM14_DEBUG_GPIO);
		#endif
		TIM14_PeriodElapsedCallback();
	}
}
#elif APP_TIM14_PWM_ENABLE
static LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};
static uint32_t TIM14_Autoreload;
/**
 * @brief  TIM14_PWM_Init
 * @param  None
 * @retval None
 */
void TIM14_PWM_Init(void)
{
	/* Configure TIM1 */
	LL_TIM_InitTypeDef TIM1CountInit = {0};
	uint32_t Prescale;
	for(Prescale = 1U; Prescale < 0xFFFFU; Prescale++)   /* prescale could be 0~0xFFFF */
    {
        TIM14_Autoreload = (SystemCoreClock / TIM14_PWM_FREQUENCE) / Prescale;
        /* If target value is larger than CNR, need to use a larger prescaler */
        if(TIM14_Autoreload < (0x10000U))
        {
            break;
        }
    }
	/* Enable TIM14 peripheral clock */
	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM14);
	TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* Set divider:tDTS=tCK_INT  */
	TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /**
 * @brief  Documentation
 */
	TIM1CountInit.Autoreload      	  = TIM14_Autoreload - 1;               /**
 * @brief  Documentation
 */
	TIM1CountInit.Prescaler           = Prescale - 1;              /**
 * @brief  Documentation
 */
	TIM1CountInit.RepetitionCounter   = 0;                        /**
 * @brief  Documentation
 */
	/* Initialize TIM1 */
	LL_TIM_Init(TIM14,&TIM1CountInit);
    /* Set PWM channel */
	TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;       /**
 * @brief  Documentation
 */
	TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;    /* Enable selected channle    */
	TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH;   /**
 * @brief  Documentation
 */
	TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW;   /**
 * @brief  Documentation
 */
	#if (TIM14_CH1_PIN == 9)
	GPIO_Init(TIM14_CH1_PIN,ALTERNATE | GPIO_TIM14_AF6);
	#else
	GPIO_Init(TIM14_CH1_PIN,ALTERNATE | GPIO_TIM14_AF5);
	#endif
	TIM14_PWM_Pulse(LL_TIM_CHANNEL_CH1,TIM14_DUTY_CYCLE);
	/* Enable output */
	LL_TIM_EnableAllOutputs(TIM14);
	/* Enable TIM1 */
	LL_TIM_EnableCounter(TIM14);
}
/**
 * @brief  TIM14_PWM_Pulse
 * @param  None
 * @retval None
 */
void TIM14_PWM_Pulse(uint32_t CHx,uint16_t percent)
{
	/* CH1 compare value:250 */
	TIM_OC_Initstruct.CompareValue  = TIM14_Autoreload  * percent / TIM14_RESOLUTION;
	/* Configure CH1 */
	LL_TIM_OC_Init(TIM14,CHx,&TIM_OC_Initstruct);
}
#endif
