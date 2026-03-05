#ifndef _TK_CFG_USER_H
#define _TK_CFG_USER_H

// Touch key channel definition, fill in order of KEY, define unused keys as TK_CH_NONE
#define CH_KEY0			TK_CH17
#define CH_KEY1			TK_CH15
#define CH_KEY2			TK_CH11
#define CH_KEY3			TK_CH5
#define CH_KEY4			TK_CH16
#define CH_KEY5			TK_CH10
#define CH_KEY6			TK_CH7
#define CH_KEY7			TK_CH6
#define CH_KEY8			TK_CH_NONE
#define CH_KEY9			TK_CH_NONE
#define CH_KEY10		TK_CH_NONE
#define CH_KEY11		TK_CH_NONE
#define CH_KEY12		TK_CH_NONE
#define CH_KEY13		TK_CH_NONE
#define CH_KEY14		TK_CH_NONE
#define CH_KEY15		TK_CH_NONE
#define CH_KEY16		TK_CH_NONE
#define CH_KEY17		TK_CH_NONE
#define CH_KEY18		TK_CH_NONE
#define CH_KEY19		TK_CH_NONE
#define CH_KEY20		TK_CH_NONE
#define CH_KEY21		TK_CH_NONE
#define CH_KEY22		TK_CH_NONE
#define CH_KEY23		TK_CH_NONE
#define CH_KEY24		TK_CH_NONE
#define CH_KEY25		TK_CH_NONE
//--------------------------------------------------------------
// Touch Key Threshold Settings
#define KEY0_THD        100
#define KEY1_THD        100
#define KEY2_THD        100
#define KEY3_THD        100
#define KEY4_THD        100
#define KEY5_THD        100
#define KEY6_THD        100
#define KEY7_THD        100
#define KEY8_THD		40
#define KEY9_THD		40
#define KEY10_THD		40
#define KEY11_THD		40
#define KEY12_THD		40
#define KEY13_THD		40
#define KEY14_THD		40
#define KEY15_THD		40
#define KEY16_THD		40
#define KEY17_THD		40
#define KEY18_THD		40
#define KEY19_THD		40
#define KEY20_THD		40
#define KEY21_THD		40
#define KEY22_THD		40
#define KEY23_THD		40
#define KEY24_THD		40
#define KEY25_THD		40
//==============================================================
#define WATER_PROOF_EN			0			/*  1: Enable, 0: Disable   */
#define WATER_SHIELD_CH			TK_CH_NONE	/*  Shield channel  */
#define WATER_PROOF_MODE		0			/*  0: Mode 0, 1: Mode 1 */
#define WATER_RATIO_0			15			/*  Water ratio 0   */
#define WATER_RATIO_1			45			/*  Water ratio 1       */
#define DUSTERCLOTH_EN			0			/*  1: Enable, 0: Disable */
#define DUSTERCLOTH_THD			250			/*  Duster cloth threshold  */

#define HIGH_SENSITVITY_EN		0			/*  1: Enable, 0: Disable */
#define SENSITVITY_SHIELD_CH	TK_CH_NONE		/* Shield channel   */

//==============================================================
#define SLIDER_OR_WHEEL0_TYPE			TK_APP_NONE			// Type
#define SLIDER_OR_WHEEL0_RESOLUTION		100					// Resolution
#define SLIDER_OR_WHEEL0_THD			80					// Threshold
#define SLIDER_OR_WHEEL0_CH0			TK_CH4				// Channel 0
#define SLIDER_OR_WHEEL0_CH1			TK_CH8				
#define SLIDER_OR_WHEEL0_CH2			TK_CH5
#define SLIDER_OR_WHEEL0_CH3			TK_CH6
#define SLIDER_OR_WHEEL0_CH4			TK_CH7
#define SLIDER_OR_WHEEL0_CH5			TK_CH_NONE
#define SLIDER_OR_WHEEL0_CH6			TK_CH_NONE
#define SLIDER_OR_WHEEL0_CH7			TK_CH_NONE

#define SLIDER_OR_WHEEL1_TYPE			TK_APP_NONE			// Type
#define SLIDER_OR_WHEEL1_RESOLUTION		255					// Resolution
#define SLIDER_OR_WHEEL1_THD			450					// Threshold
#define SLIDER_OR_WHEEL1_CH0			TK_CH19				// Channel 0
#define SLIDER_OR_WHEEL1_CH1			TK_CH23
#define SLIDER_OR_WHEEL1_CH2			TK_CH24
#define SLIDER_OR_WHEEL1_CH3			TK_CH25
#define SLIDER_OR_WHEEL1_CH4			TK_CH_NONE
#define SLIDER_OR_WHEEL1_CH5			TK_CH_NONE
#define SLIDER_OR_WHEEL1_CH6			TK_CH_NONE
#define SLIDER_OR_WHEEL1_CH7			TK_CH_NONE

#define SLIDER_OR_WHEEL2_TYPE			TK_APP_NONE			// Type
#define SLIDER_OR_WHEEL2_RESOLUTION		255					// Resolution
#define SLIDER_OR_WHEEL2_THD			80					// Threshold
#define SLIDER_OR_WHEEL2_CH0			TK_CH_NONE			// Channel 0
#define SLIDER_OR_WHEEL2_CH1			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH2			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH3			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH4			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH5			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH6			TK_CH_NONE
#define SLIDER_OR_WHEEL2_CH7			TK_CH_NONE

#define SLIDER_OR_WHEEL3_TYPE			TK_APP_NONE			// Type
#define SLIDER_OR_WHEEL3_RESOLUTION		255					// Resolution
#define SLIDER_OR_WHEEL3_THD			80					// Threshold
#define SLIDER_OR_WHEEL3_CH0			TK_CH_NONE			// Channel 0
#define SLIDER_OR_WHEEL3_CH1			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH2			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH3			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH4			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH5			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH6			TK_CH_NONE
#define SLIDER_OR_WHEEL3_CH7			TK_CH_NONE
//==============================================================
#endif
//--------------------------------------------------------------
