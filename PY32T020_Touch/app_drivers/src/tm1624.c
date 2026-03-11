#include "tm1624.h"
#if APP_TM1624_ENABLE
/**
 * @brief  TM1624_Init
 * @param  None
 * @retval None
 */
void TM1624_Init(void)
{
	GPIO_Init(TM1624_CLK,OUTPUT|PUSHPULL); GPIO_ClearBit(TM1624_CLK);
	GPIO_Init(TM1624_DIN,OUTPUT|PUSHPULL); GPIO_ClearBit(TM1624_DIN);
	GPIO_Init(TM1624_STB,OUTPUT|PUSHPULL); GPIO_ClearBit(TM1624_STB);
}
/**
 * @brief  TM1624_SendByte
 * @param  None
 * @retval None
 */
static void TM1624_SendByte(uint8_t dat)
{
	uint8_t i;
	for(i = 0;i < 8;i++)
	{	
		GPIO_ClearBit(TM1624_CLK);
		if(dat & 0X01) 
			GPIO_SetBit(TM1624_DIN);
		else         
			GPIO_ClearBit(TM1624_DIN);
		nop_delay_xus(1);
		GPIO_SetBit(TM1624_CLK);
		dat >>= 1;	 
		nop_delay_xus(1);
	}
	GPIO_ClearBit(TM1624_CLK);
	GPIO_ClearBit(TM1624_DIN);
}
/**
 * @brief  TM1624_ReadByte
 * @param  None
 * @retval None
 */
static uint8_t TM1624_ReadByte(void)
{
	uint8_t i;
	uint8_t dat;
	for(i = 0;i < 8;i++)
	{	
		dat >>= 1;	 
		GPIO_ClearBit(TM1624_CLK);
		nop_delay_xus(1);
		GPIO_SetBit(TM1624_CLK);
		nop_delay_xus(1);
		if(GPIO_ReadBit(TM1624_DIN)) 
			dat |= 0X80;
		nop_delay_xus(1);
	}
	GPIO_ClearBit(TM1624_CLK);
	return dat;
}
/**
 * @brief  TM1624_SendCommand
 * @param  None
 * @retval None
 */
static void TM1624_SendCommand(uint8_t cmd)
{ 
   GPIO_SetBit(TM1624_STB);
   nop_delay_xus(1);
   GPIO_ClearBit(TM1624_STB);
   TM1624_SendByte(cmd);
}
/**
 * @brief  TM1624_Display_Update
 * @param  None
 * @retval None
 */
void TM1624_Display_Update(uint8_t *display,uint8_t num,uint8_t Config)
{
	uint8_t i;
	TM1624_SendCommand(TM1624_DISP_COM);
    TM1624_SendCommand(0x40);
    TM1624_SendCommand(0xC0);
	for(i = 0;i < num;i++,display++)
	{
		TM1624_SendByte(*display);
	}
	TM1624_SendCommand(0x80 | Config);
}
/**
 * @brief  TM1624_Read_Key
 * @param  None
 * @retval None
 */
uint8_t TM1624_Read_Key(uint8_t *data)
{
	uint8_t *temp = data;
	TM1624_SendCommand(0x42);
	nop_delay_xus(1);
	GPIO_ClearBit(TM1624_CLK);
	GPIO_Init(TM1624_DIN,INPUT|PULL_UP); 
	nop_delay_xus(1);
	for(uint8_t i = 0;i < 5;i++,temp++)
	{
		*temp = TM1624_ReadByte();
	}
	GPIO_Init(TM1624_DIN,OUTPUT|PUSHPULL); 
	GPIO_ClearBit(TM1624_DIN);
	return 1;
}
#endif
