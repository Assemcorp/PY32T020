#include "ir_received.h"

#if APP_IR_RECEIVED_ENABLE
#define ir_state_bit(n) ((Bits8_TypeDef *)(&(ir_state)))->bit##n
#define		Queue_Size		12
typedef struct 
{
	uint8_t level_In;				// Fifo Input Index
	uint8_t level_Out;				// Fifo Output Index
	uint8_t level_count;			// High Level Counter
	uint8_t level_fifo[Queue_Size];	// Fifo buffer
}ir_Queue;
static uint8_t ir_state;
static ir_Queue ir;  
static uint8_t ir_Count;		// Key Press Count
static uint8_t ir_Rec[4];		// Received Bit Buffer
static uint8_t ir_Cnt;			// Received Bit Count
static uint16_t ir_release;		// Release Count
#define ir_last			ir_state_bit(0)
#define SYNC			ir_state_bit(1)
#define RX_OVER			ir_state_bit(2)
/**
 * @brief  Initialize IR Scanning and Decoding
 * @param  None
 * @retval None
 */
void IR_Received_Init(void)
{
	ir_state = 0;
	ir.level_Out = ir.level_In = 0;
	ir_Cnt = 0;
	GPIO_Init(IR_GPIO,INPUT|PULL_UP);
}
/**
 * @brief  IR decoding level scan function. To be called in a timer interrupt.
 * @param  None
 * @retval None
 */
void IR_Received_Scan(void)
{
	if(GPIO_ReadBit(IR_GPIO))	  // High Level
	{
		ir.level_count++;
		ir_last = 1;			 // Mark that high level has been captured
	}
	else	  					// Low Level
	{   
		if(ir_last)				// Save high level duration
		{
			ir.level_fifo[ir.level_In] = ir.level_count;
			ir.level_In++;
			if(ir.level_In >= Queue_Size)
				ir.level_In = 0;
		}	
		ir.level_count = 0;
		ir_last = 0;		
	}
	if(ir_release)
		ir_release--;
}
/**
 * @brief  IR Decoding Function
 * @param  remote : Pointer to data receiving structure
 * @retval 0 : No signal input
 * @retval 1 : Received correct IR signal
 */
uint8_t IR_Press(Ir_TypeDef *remote)
{
	uint8_t i;
	uint8_t hight_level;
	while(ir.level_In != ir.level_Out)
	{
		hight_level = ir.level_fifo[ir.level_Out];
		ir.level_Out++;
		if(ir.level_Out >= Queue_Size)
			ir.level_Out = 0;
		if(SYNC)// Received Sync Code
		{
			i = (ir_Cnt >> 3);
			if(hight_level >= DATA0_MIN_TIME && hight_level < DATA0_MAX_TIME)			
			{
				ir_Rec[i] <<= 1;	// Shift left by 1 bit.
				ir_Rec[i] &= 0XFE;	// Received 0
				ir_Cnt++;	
			}
			else if(hight_level >= DATA1_MIN_TIME && hight_level < DATA1_MAX_TIME)	
			{
				ir_Rec[i] <<= 1;	// Shift left by 1 bit.
				ir_Rec[i] |= 0X01;	// Received 1
				ir_Cnt++;
			}
			else
			{	
				SYNC = 0;
				ir_Cnt = 0; 
			}
			/* Address 16-bit, Data 16-bit */
			if(ir_Cnt == 32)
			{
				RX_OVER = 1;
				SYNC = 0;		// Clear sync code received flag
				ir_Cnt = 0;		// Clear receive bit count
				ir_Count = 1;
				ir_release = RELEASE_TIME;		// Mark data received
				break;
			}
		}
		else if(hight_level >= SYNC_MIN_TIME && hight_level < SYNC_MAX_TIME)	
		{
			SYNC = 1;		// Mark sync code successfully received
			ir_Cnt = 0;		// Clear receive bit count
			ir_Count = 0;
			ir_release = 0;
		}
		else if(hight_level >= LONG_MIN_TIME && hight_level < LONG_MAX_TIME)	
		{
			if(ir_release)						// Previous data received
			{
				ir_release = RELEASE_TIME;
				if(ir_Count < 255)
					ir_Count++;
				RX_OVER = 1;
				SYNC = 0;		// Clear sync code received flag
				ir_Cnt = 0;		// Clear receive bit count
				break;
			}
		}
		else
		{
			SYNC = 0;
			ir_Cnt = 0; 
		}
	}
	if(RX_OVER)
	{
		RX_OVER = 0;
		/* Data Verification */
		if((ir_Rec[0] == (uint8_t)~ir_Rec[1]) && (ir_Rec[2] == (uint8_t)~ir_Rec[3]))
		{
			remote->ir_address = ir_Rec[0];
			remote->ir_command = ir_Rec[2]; 
			remote->ir_count = ir_Count;
			return 1;
		}
		else
		{
			SYNC = 0;
			ir_Cnt = 0; 
			ir_release = 0;
		}
	}
	return 0;
}
#endif
