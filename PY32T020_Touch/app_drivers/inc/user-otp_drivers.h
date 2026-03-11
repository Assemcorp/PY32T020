#ifndef _USER_OTP_DRIVERS_H_
#define _USER_OTP_DRIVERS_H_
#include "app_config.h"
#if APP_USER_OTP_ENABLE
/**
 * @brief  Write cached data to Flash
 * @param  None
 * @retval 0 : Save failed
 * @retval 1 : Save successful
 */
uint8_t User_Flash_Write(void);
/**
 * @brief  Read data from cache (up to 124 bytes available)
 * @param  offset : Start offset in cache
 * @param  data   : Pointer to the buffer to read into
 * @param  len    : Number of bytes to read
 * @retval 0 : Invalid data or length exceeded
 * @retval 1 : Data read successfully
 */
uint8_t User_Cache_Read(uint8_t offset,uint8_t *data,uint8_t len);
/**
 * @brief  Write data to cache (up to 124 bytes available)
 * @param  offset : Start offset in cache
 * @param  data   : Pointer to the data to write
 * @param  len    : Number of bytes to write (Note: comment originally said read but meant write)
 * @retval 0 : Length exceeded
 * @retval 1 : Data written successfully
 */
uint8_t User_Cache_Write(uint8_t offset,uint8_t *data,uint8_t len);
#endif
#endif
