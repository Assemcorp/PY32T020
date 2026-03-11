#include "user-otp_drivers.h"
#if APP_USER_OTP_ENABLE
#define FLASH_USER_START_ADDR     0X1FFF0280
static uint32_t USER_DATA[32];
static uint8_t flash_flag = 0;
/**
 * @brief  User_Flash_Write
 * @param  None
 * @retval None
 */
uint8_t User_Flash_Write(void)
{
	/**
 * @brief  Documentation
 */
	if(flash_flag & 0X02)
	{
		/* Unlock Flash */
		FLASH_Unlock();
		Erase_UserData(FLASH_USER_START_ADDR);
		Program_UserData(FLASH_USER_START_ADDR,USER_DATA);
		FLASH_Lock();
		uint32_t addr = FLASH_USER_START_ADDR;
		for(uint8_t i = 0;i < 32;i++,addr += 4)
		{
			if(USER_DATA[i] != HW32_REG(addr))
				return 0;
		}
	}
	flash_flag &= ~0X02;
	return 1;
}
/**
 * @brief  User_Cache_Read
 * @param  None
 * @retval None
 */
uint8_t User_Cache_Read(uint8_t offset,uint8_t *data,uint8_t len)
{
	/**
 * @brief  Documentation
 */
	if((flash_flag & 0X01) == 0X00)
	{
		uint32_t addr = FLASH_USER_START_ADDR;
		for(uint8_t i = 0;i < 32;i++,addr += 4)
		{
			USER_DATA[i] = HW32_REG(addr);
		}
		flash_flag |= 0X01;
	}
	/**
 * @brief  Documentation
 */
	if((USER_DATA[0] & 0XFFFF0000) != 0XA5A50000)
	{
		return 0;
	}
	if((offset + len) > 124)
		return 0;
	uint8_t *copy_data = (uint8_t *)&USER_DATA[1];
	copy_data += offset;
	for(uint8_t i = 0;i < len;i++)
	{
		*data = *copy_data;
		data++;
		copy_data++;
	}
	return 1;
}
/**
 * @brief  User_Cache_Write
 * @param  None
 * @retval None
 */
uint8_t User_Cache_Write(uint8_t offset,uint8_t *data,uint8_t len)
{
	if((offset + len) > 124)
		return 0;
	uint8_t *copy_data = (uint8_t *)&USER_DATA[1];
	copy_data += offset;
	/**
 * @brief  Documentation
 */
	for(uint8_t i = 0;i < len;i++)
	{
		if(*copy_data != *data)
			flash_flag |= 0X02;
		*copy_data = *data;
		data++;
		copy_data++;
	}
	/**
 * @brief  Documentation
 */
	USER_DATA[0] &= ~0XFFFF0000;
	USER_DATA[0] |= 0XA5A50000;
	return 1;
}
#endif
