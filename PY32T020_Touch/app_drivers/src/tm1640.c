#include "tm1640.h"
#if APP_TM1640_ENABLE
/**
 * @brief  TM1640_Init
 * @param  None
 * @retval None
 */
void TM1640_Init(void)
{
	GPIO_Init(TM1640_CLK,OUTPUT|PUSHPULL); GPIO_ClearBit(TM1640_CLK);
	GPIO_Init(TM1640_DIN,OUTPUT|PUSHPULL); GPIO_ClearBit(TM1640_DIN);
}
/**
 * @brief  TM1640_Start
 * @param  None
 * @retval None
 */
static void TM1640_Start(void)
{
	GPIO_SetBit(TM1640_DIN);     
	GPIO_SetBit(TM1640_CLK);    
	nop_delay_xus(1);
	GPIO_ClearBit(TM1640_DIN);  
	nop_delay_xus(1);
}
/**
 * @brief  TM1640_Stop
 * @param  None
 * @retval None
 */
static void TM1640_Stop(void)
{
	GPIO_ClearBit(TM1640_DIN);     
	GPIO_ClearBit(TM1640_CLK);  
	nop_delay_xus(1);
	GPIO_SetBit(TM1640_CLK);  
	nop_delay_xus(1);
	GPIO_SetBit(TM1640_DIN);     
	nop_delay_xus(1);
}
/**
 * @brief  TM1640_SendByte
 * @param  None
 * @retval None
 */
static void TM1640_SendByte(uint8_t data)
{
	for(uint8_t i = 0;i < 8;i++)
	{
		GPIO_ClearBit(TM1640_CLK); 
		if(data & 0X01)
			GPIO_SetBit(TM1640_DIN);     
		else
			GPIO_ClearBit(TM1640_DIN);   
		nop_delay_xus(1);		
		GPIO_SetBit(TM1640_CLK);  
		data >>= 1;
		nop_delay_xus(1);
	}
}
/**
 * @brief  TM1640_Display_Update
 * @param  None
 * @retval None
 */
void TM1640_Display_Update(uint8_t *display,uint8_t num,uint8_t Config)
{
	uint8_t i;
	TM1640_Start();
	TM1640_SendByte(0X40);
	TM1640_Stop();
	
	TM1640_Start();
	TM1640_SendByte(0XC0);
	for(i = 0;i < num;i++,display++)
	{
		TM1640_SendByte(*display);
	}
	TM1640_Stop();
	
	TM1640_Start();
	TM1640_SendByte(0X80 | Config);
	TM1640_Stop();
}

#endif
