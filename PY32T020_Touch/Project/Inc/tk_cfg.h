#ifndef _TK_CFG_H
#define _TK_CFG_H
#include "tk_lib.h"
#include "tk_cfg_user.h"

// <<< Use Configuration Wizard in Context Menu >>>
//  <h> Basic Settings
//  <i> Set current mode, reference voltage, scan window width, etc.
//  <o> CMOD Selection
//  <i> Select CMOD internal or external
//  <0=> Internal
//  <1=> External
#define EXTCMOD						0

//  <o> Reference Voltage
//  <i> Set the reference voltage for the comparator
//  <0=> 0.6V
//  <1=> 1.0V
//  <2=> 1.5V
//  <3=> 2.0V
#define CONFIG_VREF					3

//  <o> Scan Window Width
//  <i> Scan window width = win * (1/Ftk_clk), Ftk_clk = 24M, win=12000, scan time is 500us
//  <0-65535>
#define CONFIG_WIN					12000	

//  <e> IDAC0 Enable
//  <i> Custom current setting
#define CONFIG_IDAC0				1

//  <o> IDAC1 Enable
//  <i> Enable channel offset current
//  <0=> DISABLE
//  <1=> ENABLE
#define CONFIG_IDAC1				0

//  <i> PWM: SWCLK = APB_CLK / SW_DIV, default is 6, SWCLK = 4M
//  <i> PRS: SWCLK = APB_CLK / (SW_DIV * 2), default is 8, SWCLK = 1.5M
//  <1-511>
#define SW_DIV					8

//  <e> Frequency Hopping Mode
//  <i> Used to control frequency hopping
#define SW_MODE					1

//  <o> Frequency Hopping Mode LFSR Width
//  <i> Range: 1 ~ 15
//  <1-15>
#define PWMM_PRS_LFSRW		8

//  <o> Frequency Hopping Mode LFSR Seed
//  <i> Range: 1 ~ 255, must be odd
//  <1-255>
#define PWMM_PRS_SEED		0XA7		

//  <e> Comparator Enable
//  <i> Enable comparator function
#define COPA_ENABLE				1

//  <o> VCC1 Voltage
//  <i> Set the VCC1 voltage
//  <0=> 1.6V
//  <1=> 2.0V
//  <2=> 2.4V
//  <3=> 2.8V
//  <4=> 3.2V
//  <5=> 3.6V
//  <6=> 4.0V
//  <7=> 4.4V
#define CONFIG_VCC1				1

//  <o> Comparator Output Mode
//  <i> Set the comparator output mode
//  <0=> Low Level
//  <1=> High Level
//  <2=> Inverted
//  <3=> Synchronous
#define COPADATA_OUTPUT			0

//  <e> Low Power Mode
//  <i> Enable touch power saving mode, enters sleep mode after a period of inactivity
#define SLEEP_EN                0

//  <o> Enter Sleep Mode Time
//  <i> Set the time to enter sleep mode, unit is 5ms, 200 means 1 second
//  <0-65535>
#define ENTER_SLEEPTIME		200  	

//  <o> Scan Wake-up Time
//  <i> Set the time to wake up from sleep mode, unit is 1ms, 1000 means 1 second, note that the time should be longer to ensure the signal is stable
//  <0-1000>
#define LP_WAUP_TIME		100		

//  <o> Low Power Mode Threshold
//  <i> Set the threshold for low power mode, when the signal changes more than this value, exit low power mode
//  <0-65535>
#define LP_NORMRMALDELTA	15		

//  <o> Low Power Mode Scan Window
//  <i> Set the scan window for low power mode, unit is 5ms
//  <0-65535>
#define CONFIG_LP_WIN		6000		

//  <o> Low Power Mode Reference Voltage
//  <i> Set the reference voltage for low power mode
//  <0=> 0.6V
//  <1=> 1.0V
//  <2=> 1.5V
//  <3=> 2.0V
#define CONFIG_LPVREF		0																												
//  </e>	

// Documentation
// Documentation
// Documentation
// Documentation
//  <0-100>
#define NOISE_THD_DEFAULT	15								//
// Documentation
// Documentation
//  <1-30>
#define FILTERCOUNT			5								//	
// Documentation
// Documentation
//  <0-120000>
#define KEY_OUT_MAX_TIME					30000

#define KEY_OUT_MAX_TICK_CNT				(KEY_OUT_MAX_TIME / 5)	
// Documentation
// Documentation
//  <0-100>
#define FINGER_CONFIRM_TICK_CNT					(5) 		
// Documentation
// Documentation
//  <0-100>
#define FINGER_RELEASE_CONFIRM_TICK_CNT			(5)  		
// Documentation
// Documentation
//  <0-1000>
#define WATER_AREA_CONFIRM_TICK_CNT				(150)		// Documentation
// Documentation
// Documentation
//  <0-1000>
#define NOISE_AREA_CONFIRM_TICK_CNT				(100)		// Documentation
// Documentation
// Documentation
//  <0-1000>
#define BOTTON_AREA_CONFIRM_TICK_CNT			(60)		// Documentation
// Documentation
// Documentation
//  <0=> DISABLE
//  <1=> ENABLE
#define SIGLE_KEY_TRIGGER			0		
// Documentation
// Documentation
//  <0-255>
#define MAX_TRIGGER_KEY_CNT 		0				
// </h>

// Documentation
// Documentation
#define REF_CH_EN				1			
// Documentation
// Documentation
//  <0-2000>
#define REF_CH_THD				50		
// </e>


// <<< end of configuration section >>>

//******************************************************************************************************************************************************
#if (CH_KEY0 == TK_CH_NONE)
	#define KEY_CH_TOTAL		0
#elif (CH_KEY1 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		1
#elif (CH_KEY2 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		2
#elif (CH_KEY3 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		3
#elif (CH_KEY4 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		4
#elif (CH_KEY5 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		5
#elif (CH_KEY6 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		6
#elif (CH_KEY7 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		7
#elif (CH_KEY8 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		8
#elif (CH_KEY9 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		9
#elif (CH_KEY10 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		10
#elif (CH_KEY11 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		11
#elif (CH_KEY12 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		12
#elif (CH_KEY13 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		13
#elif (CH_KEY14 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		14
#elif (CH_KEY15 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		15
#elif (CH_KEY16 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		16
#elif (CH_KEY17 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		17
#elif (CH_KEY18 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		18
#elif (CH_KEY19 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		19
#elif (CH_KEY20 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		20
#elif (CH_KEY21 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		21
#elif (CH_KEY22 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		22
#elif (CH_KEY23 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		23
#elif (CH_KEY24 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		24
#elif (CH_KEY25 == TK_CH_NONE) 
	#define KEY_CH_TOTAL		25
#else
	#define KEY_CH_TOTAL		26
#endif

#if WATER_PROOF_EN	
	#define SHIELD_CH_TOTAL  1
#elif HIGH_SENSITVITY_EN
#if (SENSITVITY_SHIELD_CH == TK_CH_NONE)
	#define SHIELD_CH_TOTAL  0
#else
	#define SHIELD_CH_TOTAL  1
#endif
#else
	#define SHIELD_CH_TOTAL  0
#endif

#if (WATER_PROOF_EN && HIGH_SENSITVITY_EN)
	#error "error!"
#endif


#if (SLIDER_OR_WHEEL0_TYPE != TK_APP_NONE)
	#if (SLIDER_OR_WHEEL0_CH0 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL0_CH1 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL0_CH2 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	2
	#elif (SLIDER_OR_WHEEL0_CH3 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	3
	#elif (SLIDER_OR_WHEEL0_CH4 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	4
	#elif (SLIDER_OR_WHEEL0_CH5 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	5
	#elif (SLIDER_OR_WHEEL0_CH6 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	6
	#elif (SLIDER_OR_WHEEL0_CH7 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL0_CH_CNT	7
	#else
		#define SLIDER_OR_WHEEL0_CH_CNT	8
	#endif
#else 
	#define SLIDER_OR_WHEEL0_CH_CNT	0
#endif
#if (SLIDER_OR_WHEEL1_TYPE != TK_APP_NONE)
	#if (SLIDER_OR_WHEEL1_CH0 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL1_CH1 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL1_CH2 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	2
	#elif (SLIDER_OR_WHEEL1_CH3 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	3
	#elif (SLIDER_OR_WHEEL1_CH4 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	4
	#elif (SLIDER_OR_WHEEL1_CH5 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	5
	#elif (SLIDER_OR_WHEEL1_CH6 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	6
	#elif (SLIDER_OR_WHEEL1_CH7 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL1_CH_CNT	7
	#else
		#define SLIDER_OR_WHEEL1_CH_CNT	8
	#endif
#else 
	#define SLIDER_OR_WHEEL1_CH_CNT	0
#endif
#if (SLIDER_OR_WHEEL2_TYPE != TK_APP_NONE)
	#if (SLIDER_OR_WHEEL2_CH0 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL2_CH1 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL2_CH2 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	2
	#elif (SLIDER_OR_WHEEL2_CH3 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	3
	#elif (SLIDER_OR_WHEEL2_CH4 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	4
	#elif (SLIDER_OR_WHEEL2_CH5 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	5
	#elif (SLIDER_OR_WHEEL2_CH6 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	6
	#elif (SLIDER_OR_WHEEL2_CH7 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL2_CH_CNT	7
	#else
		#define SLIDER_OR_WHEEL2_CH_CNT	8
	#endif
#else 
	#define SLIDER_OR_WHEEL2_CH_CNT	0
#endif
#if (SLIDER_OR_WHEEL3_TYPE != TK_APP_NONE)
	#if (SLIDER_OR_WHEEL3_CH0 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL3_CH1 == TK_CH_NONE)
		#error "error!"
	#elif (SLIDER_OR_WHEEL3_CH2 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	2
	#elif (SLIDER_OR_WHEEL3_CH3 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	3
	#elif (SLIDER_OR_WHEEL3_CH4 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	4
	#elif (SLIDER_OR_WHEEL3_CH5 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	5
	#elif (SLIDER_OR_WHEEL3_CH6 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	6
	#elif (SLIDER_OR_WHEEL3_CH7 == TK_CH_NONE)
		#define SLIDER_OR_WHEEL3_CH_CNT	7
	#else
		#define SLIDER_OR_WHEEL3_CH_CNT	8
	#endif
#else 
	#define SLIDER_OR_WHEEL3_CH_CNT		0
#endif

#if (REF_CH_EN)
#define EXTERNAL_CHS		INSIDE_CHS		/*	�ⲿ�ο�ͨ�� */
#define EXTERNAL_CNT		1
#else
#define EXTERNAL_CNT		0
#endif

#define SLIDER_OR_WHEEL_CH_TOTAL	(SLIDER_OR_WHEEL0_CH_CNT + SLIDER_OR_WHEEL1_CH_CNT + SLIDER_OR_WHEEL2_CH_CNT + SLIDER_OR_WHEEL3_CH_CNT)

#define TK_CHMAX  					(KEY_CH_TOTAL + EXTERNAL_CNT + SHIELD_CH_TOTAL + SLIDER_OR_WHEEL_CH_TOTAL)

#endif
