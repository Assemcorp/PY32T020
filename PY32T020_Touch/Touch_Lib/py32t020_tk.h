#ifndef PY32T020_TK_H
#define PY32T020_TK_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "py32t0xx.h"
#include <stdio.h>

#define TK_STDIV2 	(0x00U)
#define TK_STDIV4 	(0x01U)
#define TK_STDIV8 	(0x02U)
#define TK_STDIV12 	(0x03U)
#define TK_STDIV16 	(0x04U)
#define TK_STDIV24 	(0x05U)

#define TK_DIV0 	(0x00U)
#define TK_DIV2 	(0x02U)
#define TK_DIV3 	(0x03U)
#define TK_DIV4 	(0x04U)
#define TK_DIV5 	(0x05U)
#define TK_DIV6 	(0x06U)
#define TK_DIV7 	(0x07U)

#define TK_CFT0 	(0x00U)
#define TK_CFT1 	(0x01U)
#define TK_CFT2 	(0x02U)
#define TK_CFT3 	(0x03U)
#define TK_CFT4 	(0x04U)
#define TK_CFT5 	(0x05U)
#define TK_CFT6 	(0x06U)
#define TK_CFT7 	(0x07U)

#define TK_MIDACSTEP_0_5UA 	(0x00U)
#define TK_MIDACSTEP_2UA 	(0x01U)

#define TK_VCC1CR_1_6V (0x00U)
#define TK_VCC1CR_2_0V (0x01U)
#define TK_VCC1CR_2_4V (0x02U)
#define TK_VCC1CR_2_8V (0x03U)
#define TK_VCC1CR_3_2V (0x04U)
#define TK_VCC1CR_3_6V (0x05U)
#define TK_VCC1CR_4_0V (0x06U)
#define TK_VCC1CR_4_4V (0x07U)

#define TK_COPADATA_OUTPUT_LOW 			(0x00U)
#define TK_COPADATA_OUTPUT_HIGH 		(0x01U)
#define TK_COPADATA_OUTPUT_S1_INVERSE 	(0x02U)
#define TK_COPADATA_OUTPUT_S1 			(0x03U)

#define TK_KVREF_0_6V (0x00U)
#define TK_KVREF_1_0V (0x01U)
#define TK_KVREF_1_5V (0x02U)
#define TK_KVREF_2_0V (0x03U)

#define TK_SHORTSW_NUM_0 (0x00U)
#define TK_SHORTSW_NUM_1 (0x01U)
#define TK_SHORTSW_NUM_2 (0x02U)
#define TK_SHORTSW_NUM_3 (0x03U)

#define TK_LPABNORMAL_MODE0 (0x00U)
#define TK_LPABNORMAL_MODE1 (0x01U)

#define TK_CTRLSOURCE_SW (0x00U)
#define TK_CTRLSOURCE_HW (0x01U)

#define TK_PWMM_PWM (0x00U)
#define TK_PWMM_PRS (0x01U)


#define PRS_DOUBLEHOP 		(1) // 1: Enable dual frequency hopping, 0: Single frequency hopping

#if PRS_DOUBLEHOP
#define PWMM_PRS_LFSRW_2 	15
#endif

#define MAX_CHS				26
#define SLIDER_MAX 			4 // Maximum number of supported sliders
#define SHIELD_CHS			0XF0
#define INSIDE_CHS			0XF1

#define TK_SLEEP			1
typedef enum
{
	TK_OK = 0x00U,
	TK_ERROR = 0x01U,
	TK_BUSY = 0x02U,
	TK_TIMEOUT = 0x03U
} TK_Status;
/**
 * @brief LL TK Init Structure definition
 */
#pragma pack(4)
typedef struct
{
	uint8_t Div;          // TK_CLK prescaler
	uint8_t Stdiv;        // ST_CLK prescaler
	uint8_t PwmM;         // PWM mode
	uint8_t Lfsrw;        // Linear feedback shift register bit width
	uint8_t ExtCmod;      // External CMODE enable
	uint8_t CmphysEnable; // Comparator hysteresis enable
	uint8_t Cft;          // Comparator output filter time
	uint8_t Vcc1Cr;       // VCC1 voltage setting
	uint8_t CopaData;     // Unscanned channel output control
	uint8_t CopaMode;     // Key compensation enable
	uint8_t TrimIdac[MAX_CHS]; // Adaptive current value
	uint8_t TrimState;    // Adaptive state
	uint8_t ShortswNum;   // Short-switch count
	uint8_t MidacStep;    // Midac current step
	uint8_t Midac;        // MiDac current value
	uint8_t Vref;         // Reference voltage
	uint8_t TrimEnable;   // Adaptive current enable
	uint8_t TrimRatio[2]; // Calibration window range
	uint16_t Swdiv;       // SW prescaler
	uint16_t Win;         // Window time
	uint16_t SetTime;     // Short-switch time
	uint8_t prsseed;     // 
	uint32_t CopaChs;     // IO compensation enable
	uint32_t TrimStep;    // Adaptive current level
	uint32_t Kenable;     // Channel enable
#if (LIB_TYPE > 1)
	uint8_t CopaOutLowState;
	uint8_t CopaOutLowTrimIdac[MAX_CHS];
	uint32_t CopaOutLowTrimStep;
#endif
} TK_InitTypeDef;
#pragma pack()

#pragma pack(4)
typedef struct
{
	uint8_t res0;
	uint8_t Lpwait;  // Wake-up wait time
	uint8_t LpDac;           // Sleep current
	uint8_t WakeDelay;       // Wake-up delay; first acquisition after wake-up is inaccurate and discarded
	uint8_t RtcInt;          // RTC interrupt type enabled during sleep; RTC second interrupt interval and time will be modified after sleep
	uint8_t Vref;            // Reference voltage setting
	uint16_t EnterStopTimer; // Idle timeout before entering sleep mode
	uint16_t SleepTouchThd;  // Wake-up delta threshold
	uint16_t LpWakeTime;
	uint16_t Baseline;       // Hardware comparator value
	uint16_t NormalDelta;    // Wake-up delta threshold
	uint16_t LpWin;          // Sleep window value
	uint16_t LpCdr;          // Wake-up data value
	uint32_t WakeChs;        // Wake-up channel
	uint32_t LpKchs; 			// Wake-up channel
	uint32_t AsynchPrediv;   // RTC normal mode prescaler value
	uint16_t Alarm_tick;
} LP_InitTypeDef;
#pragma pack()

#pragma pack(4)
typedef struct __TK_HandleTypeDef
{
	TK_InitTypeDef Init;
#if TK_SLEEP
	LP_InitTypeDef Lp;
	void (*EnterStopCallback)(void); /*!< Callback function for entering deep sleep    */
	void (*ExitStopCallback)(void);  /*!< Callback function for exiting deep sleep    */
#endif
	uint8_t (*TouchKeyFlagsMask)(void); /*!< Key processing callback function   		 */
#if (LIB_TYPE > 1)
	uint8_t (*TouchWaterFlagsMask)(uint8_t chs, int16_t Differ, int16_t DifferSigle); /*!< Waterproof processing callback function */
	uint8_t (*TouchShieldFlagsMask)(uint8_t chs,uint16_t BaseLineData,uint16_t AcqData); /*!< Key processing callback function */
#endif
} TK_HandleTypeDef;
#pragma pack()

TK_Status TK_SetSenseStart(uint32_t Chs); // Start touch scan
TK_Status TK_SetLfsrw(uint8_t Lfsrw);     // Set shift register bit width in PRS mode
TK_Status TK_LibInit(void);               // Touch library initialization
TK_Status TK_LibDeInit(void);             // Touch library de-initialization
void TK_LibIRQHandler(void);
void Timer_RTC_Init(uint16_t ms,uint16_t Alarm,uint32_t RtcInt);
extern volatile TK_HandleTypeDef TK_Handle;
#ifdef __cplusplus
}
#endif
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/

#endif
