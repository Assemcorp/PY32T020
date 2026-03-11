#include "main.h"
#include "tk_cfg.h"
#if APP_TK_ENABLE
#pragma pack(4)
typedef struct
{
    uint16_t RawData[TK_CHMAX];
    uint16_t FilteredDataDBG[TK_CHMAX];
    uint16_t BaseLineDataDBG[TK_CHMAX];
    int16_t DifferLev[TK_CHMAX];
    int16_t Differ[TK_CHMAX];
    int16_t FingerTHD[TK_CHMAX];
    uint16_t FilteredData[TK_CHMAX];
    uint16_t BaseLineData[TK_CHMAX];
    uint16_t RawDatasBuf[FILTERCOUNT * TK_CHMAX];
    uint8_t BufIdx[TK_CHMAX];
    uint8_t TouchKeyChSeq[TK_CHMAX];
    TKArea_TypeDef TK_Area[TK_CHMAX];
    TKArea_TypeDef TK_AreaPending[TK_CHMAX];
    uint16_t TK_AreaConfirmTickCnt[TK_CHMAX];
    uint16_t TK_KeyOutTimeLimitCnt[TK_CHMAX];
    uint8_t FilteredCount[TK_CHMAX];
    uint32_t FilteredSum[TK_CHMAX];
#if (LIB_TYPE > 1)
    uint16_t SingleBaseLineData[TK_CHMAX];
    uint16_t SingleAcqData[TK_CHMAX];
    uint16_t SingleAcqRawDatasBuf[FILTERCOUNT * TK_CHMAX];
#endif
} TKMem_TypeDef;
#pragma pack()
#if TK_SLEEP
static void EnterStop_Callback(void);
static void ExitStop_Callback(void);
#endif
static uint8_t APP_TouchKeyFlagsMask(void);

const uint8_t KEY_CH_TAB[] = {
    CH_KEY0,  CH_KEY1,  CH_KEY2,  CH_KEY3,  CH_KEY4,  CH_KEY5,  CH_KEY6,  CH_KEY7,  CH_KEY8,
    CH_KEY9,  CH_KEY10, CH_KEY11, CH_KEY12, CH_KEY13, CH_KEY14, CH_KEY15, CH_KEY16, CH_KEY17,
    CH_KEY18, CH_KEY19, CH_KEY20, CH_KEY21, CH_KEY22, CH_KEY23, CH_KEY24, CH_KEY25,
};
const uint16_t KEY_THD_TAB[] = {
    KEY0_THD,  KEY1_THD,  KEY2_THD,  KEY3_THD,  KEY4_THD,  KEY5_THD,  KEY6_THD,  KEY7_THD,  KEY8_THD,
    KEY9_THD,  KEY10_THD, KEY11_THD, KEY12_THD, KEY13_THD, KEY14_THD, KEY15_THD, KEY16_THD, KEY17_THD,
    KEY18_THD, KEY19_THD, KEY20_THD, KEY21_THD, KEY22_THD, KEY23_THD, KEY24_THD, KEY25_THD,
};

#if (LIB_TYPE > 0)
const uint8_t SLIDERORWHEEL_CH_TAB[SLIDER_MAX][8] = {
    {SLIDER_OR_WHEEL0_CH0, SLIDER_OR_WHEEL0_CH1, SLIDER_OR_WHEEL0_CH2, SLIDER_OR_WHEEL0_CH3, SLIDER_OR_WHEEL0_CH4,
     SLIDER_OR_WHEEL0_CH5, SLIDER_OR_WHEEL0_CH6, SLIDER_OR_WHEEL0_CH7},
    {SLIDER_OR_WHEEL1_CH0, SLIDER_OR_WHEEL1_CH1, SLIDER_OR_WHEEL1_CH2, SLIDER_OR_WHEEL1_CH3, SLIDER_OR_WHEEL1_CH4,
     SLIDER_OR_WHEEL1_CH5, SLIDER_OR_WHEEL1_CH6, SLIDER_OR_WHEEL1_CH7},
    {SLIDER_OR_WHEEL2_CH0, SLIDER_OR_WHEEL2_CH1, SLIDER_OR_WHEEL2_CH2, SLIDER_OR_WHEEL2_CH3, SLIDER_OR_WHEEL2_CH4,
     SLIDER_OR_WHEEL2_CH5, SLIDER_OR_WHEEL2_CH6, SLIDER_OR_WHEEL2_CH7},
    {SLIDER_OR_WHEEL3_CH0, SLIDER_OR_WHEEL3_CH1, SLIDER_OR_WHEEL3_CH2, SLIDER_OR_WHEEL3_CH3, SLIDER_OR_WHEEL3_CH4,
     SLIDER_OR_WHEEL3_CH5, SLIDER_OR_WHEEL3_CH6, SLIDER_OR_WHEEL3_CH7},
};

const uint8_t SLIDERORWHEEL_TYPE_TAB[SLIDER_MAX] = {SLIDER_OR_WHEEL0_TYPE, SLIDER_OR_WHEEL1_TYPE, SLIDER_OR_WHEEL2_TYPE,
                                                    SLIDER_OR_WHEEL3_TYPE};

const uint16_t SLIDERORWHEEL_RESOLUTION_TAB[SLIDER_MAX] = {SLIDER_OR_WHEEL0_RESOLUTION, SLIDER_OR_WHEEL1_RESOLUTION,
                                                           SLIDER_OR_WHEEL2_RESOLUTION, SLIDER_OR_WHEEL3_RESOLUTION};

const uint16_t SLIDERORWHEEL_THD_TAB[SLIDER_MAX] = {SLIDER_OR_WHEEL0_THD, SLIDER_OR_WHEEL1_THD, SLIDER_OR_WHEEL2_THD,
                                                    SLIDER_OR_WHEEL3_THD};
#endif

#if (LIB_TYPE > 1)
static uint8_t APP_TouchWaterFlagsMask(uint8_t chs, int16_t Differ, int16_t DifferSigle);
static uint8_t APP_TouchShieldFlagsMask(uint8_t chs, uint16_t BaseLineData, uint16_t AcqData);
#endif
/**
 */
static TKMem_TypeDef TK_Mem;
#if DEBUG_ENABLE && (DEBUG_MODE == 0)
char log_string[64];
#endif
#if (SLEEP_EN && TK_SLEEP)
static uint8_t Rtc_Wake;
#endif
/**
 * @brief  TK user parameter initialization
 * @param  None
 * @retval None
 */
void TK_UserParaInit(void)
{
    union {
        uint32_t word;
        struct
        {
            uint8_t VERSION_TYPE : 8;
            uint8_t VERSION_RC : 8;
            uint8_t VERSION_SUB1 : 8;
            uint8_t VERSION_MAIN : 8;
        } byte;
    } LibVersion;
    uint8_t offset;
#if (LIB_TYPE > 0)
    uint8_t j, k, n;
#endif
    LibVersion.word = TK_GetVersion();
    if (LibVersion.byte.VERSION_TYPE != LIB_TYPE)
    {
        /*	Library version mismatch with defined version*/
        while (1)
        {
            ;
        }
    }
    TKCtr.KeyOutTimeLimitCNT = KEY_OUT_MAX_TICK_CNT; // Long-press timeout duration, unit: 5ms
    TKCtr.TK_Config = 0;
    TK_Info.pTkAreaInfor->FingerAreaConfirmTickCNT = FINGER_CONFIRM_TICK_CNT;            // Key press (0->1) filter count
    TK_Info.pTkAreaInfor->FingerReleaseConfirmTickCNT = FINGER_RELEASE_CONFIRM_TICK_CNT; // Key release (1->0) filter count
    TK_Info.pTkAreaInfor->WaterAreaConfirmTickCNT = WATER_AREA_CONFIRM_TICK_CNT;
    TK_Info.pTkAreaInfor->NoiseAreaConfirmTickCNT = NOISE_AREA_CONFIRM_TICK_CNT;
    TK_Info.pTkAreaInfor->BottonAreaConfirmTickCNT = BOTTON_AREA_CONFIRM_TICK_CNT;
    FilterCtr.AvgModCNT = FILTERCOUNT; // Set filter count
    FilterCtr.NoiseTHD = NOISE_THD_DEFAULT;
    /*	Callback function initialization	*/
#if TK_SLEEP
    TK_Handle.EnterStopCallback = EnterStop_Callback;
    TK_Handle.ExitStopCallback = ExitStop_Callback;
#endif
    TK_Handle.TouchKeyFlagsMask = APP_TouchKeyFlagsMask;
    /*	Data pointer setup		*/
    TK_Info.pTouchKeyDatas->BaseLineData = TK_Mem.BaseLineData;
    TK_Info.pTouchKeyDatas->BaseLineDataDBG = TK_Mem.BaseLineDataDBG;
    TK_Info.pTouchKeyDatas->Differ = TK_Mem.Differ;
    TK_Info.pTouchKeyDatas->DifferLev = TK_Mem.DifferLev;
    TK_Info.pTouchKeyDatas->FilteredData = TK_Mem.FilteredData;
    TK_Info.pTouchKeyDatas->FilteredDataDBG = TK_Mem.FilteredDataDBG;
    TK_Info.pTouchKeyDatas->FingerTHD = TK_Mem.FingerTHD;
    TK_Info.pTouchKeyDatas->RawData = TK_Mem.RawData;
    TK_Info.pTouchKeyDatas->FilteredCount = TK_Mem.FilteredCount;
    TK_Info.pTouchKeyDatas->FilteredSum = TK_Mem.FilteredSum;
    TK_Info.pTK_DataBuf->RawDatasBuf = TK_Mem.RawDatasBuf;
    TK_Info.pTK_DataBuf->BufIdx = TK_Mem.BufIdx;
    TK_Info.pTouchKeyChInfor->TouchKeyChSeq = TK_Mem.TouchKeyChSeq;
    TK_Info.pTkAreaInfor->TK_Area = TK_Mem.TK_Area;
    TK_Info.pTkAreaInfor->TK_AreaPending = TK_Mem.TK_AreaPending;
    TK_Info.pTK_TickCouter->TK_AreaConfirmTickCnt = TK_Mem.TK_AreaConfirmTickCnt;
    TK_Info.pTK_TickCouter->TK_KeyOutTimeLimitCnt = TK_Mem.TK_KeyOutTimeLimitCnt;
#if (LIB_TYPE > 1)
    TK_Handle.TouchWaterFlagsMask = APP_TouchWaterFlagsMask;
    TK_Handle.TouchShieldFlagsMask = APP_TouchShieldFlagsMask;
    TK_Info.pTouchKeyDatas->SingleAcqData = TK_Mem.SingleAcqData;
    TK_Info.pTouchKeyDatas->SingleBaseLineData = TK_Mem.SingleBaseLineData;
    TK_Info.pTK_DataBuf->SingleAcqRawDatasBuf = TK_Mem.SingleAcqRawDatasBuf;
#endif
    /*	Initialize key channels	*/
    TKCtr.TouchKeyChCnt = KEY_CH_TOTAL;
    for (offset = 0; offset < TKCtr.TouchKeyChCnt; offset++)
    {
        TK_Info.pTouchKeyChInfor->TouchKeyChSeq[offset] = KEY_CH_TAB[offset];
        TK_Info.pTouchKeyDatas->FingerTHD[offset] = KEY_THD_TAB[offset];
    }
#if (LIB_TYPE > 0)
    /*	Initialize slider/wheel channels	*/
    TK_Info.pSliderChInfor->SliderWheelType = SLIDERORWHEEL_TYPE_TAB;
    TK_Info.pSliderChInfor->SliderWheelResloution = SLIDERORWHEEL_RESOLUTION_TAB;
    for (k = 0; k < SLIDER_MAX; k++)
    {
        TKCtr.SliderOrWheelPosition[k] = -1;
        TK_Info.pSliderChInfor->SliderWheelxChCnt[k] = 0;
        if (SLIDERORWHEEL_TYPE_TAB[k] == TK_APP_WHEEL || SLIDERORWHEEL_TYPE_TAB[k] == TK_APP_SLIDER)
        {
            TK_Info.pSliderChInfor->SliderWheelxStartChIdx[k] = offset;
            for (j = 0; j < 8; j++)
            {
                if (SLIDERORWHEEL_CH_TAB[k][j] == TK_CH_NONE)
                {
                    break;
                }
                TK_Info.pSliderChInfor->SliderWheelxChCnt[k]++;
            }
            n = offset;
            for (j = 0; j < TK_Info.pSliderChInfor->SliderWheelxChCnt[k]; j++)
            {
                TK_Info.pTouchKeyChInfor->TouchKeyChSeq[offset] = SLIDERORWHEEL_CH_TAB[k][j];
                TK_Info.pTouchKeyDatas->FingerTHD[offset] = 0;
                offset += 1;
            }
            TK_Info.pTouchKeyDatas->FingerTHD[n] = SLIDERORWHEEL_THD_TAB[k];
        }
    }
#endif
#if (LIB_TYPE > 1)
    ShieldInfor.WaterProof_En = WATER_PROOF_EN;
    ShieldInfor.HighSensitvity_En = HIGH_SENSITVITY_EN;
    ShieldInfor.ShieldStartChIdx = TK_CH_NONE;
    if (ShieldInfor.WaterProof_En == 1)
    {
        ShieldInfor.WaterProof_Chs = WATER_SHIELD_CH;
        ShieldInfor.WaterProof_Mode = WATER_PROOF_MODE;
        ShieldInfor.WaterProof_Ratio0 = WATER_RATIO_0;
        ShieldInfor.WaterProof_Ratio1 = WATER_RATIO_1;
        ShieldInfor.DusterCloth_En = DUSTERCLOTH_EN;
        ShieldInfor.DusterCloth_THD = DUSTERCLOTH_THD;
        ShieldInfor.Noise = 3; // Shield channel data variation within -NoiseTHD ~ +NoiseTHD range is considered stable
        /*	Set channel		*/
        ShieldInfor.ShieldStartChIdx = offset;
        TK_Info.pTouchKeyChInfor->TouchKeyChSeq[offset] = SHIELD_CHS;
        TK_Info.pTouchKeyDatas->FingerTHD[offset] = NOISE_THD_DEFAULT << 1;
        offset += 1;
    }
    else if (ShieldInfor.HighSensitvity_En == 1)
    {
        ShieldInfor.HighSensitvity_Chs = SENSITVITY_SHIELD_CH;
        if (ShieldInfor.HighSensitvity_Chs != TK_CH_NONE)
        {
            /*	Set channel		*/
            ShieldInfor.ShieldStartChIdx = offset;
            TK_Info.pTouchKeyChInfor->TouchKeyChSeq[offset] = SHIELD_CHS;
            TK_Info.pTouchKeyDatas->FingerTHD[offset] = NOISE_THD_DEFAULT;
            offset += 1;
        }
    }
#endif
#if SIGLE_KEY_TRIGGER
    TKCtr.TK_Config |= SIGLE_KEY;
#endif
#if (REF_CH_EN)
    FilterCtr.ExternalStartIdx = offset;
    TK_Info.pTouchKeyChInfor->TouchKeyChSeq[offset] = EXTERNAL_CHS;
    TK_Info.pTouchKeyDatas->FingerTHD[offset] = REF_CH_THD;
    offset += 1;
#else
    FilterCtr.ExternalStartIdx = TK_CH_NONE;
#endif
    TKCtr.MultiKeyCnt = MAX_TRIGGER_KEY_CNT;
    /*	Total touch scan channel count	*/
    TK_Info.pTouchKeyChInfor->TouchAcqChCnt = TK_CHMAX;
}
/**
 * @brief  TK register initialization
 * @param  None
 * @retval None
 */
void TK_RegisterCfg(void)
{
#define st_clk 2 // ST clock is 2MHz, so 2 counts = 1us
    /*	Touch basic configuration initialization	*/
    if (SystemCoreClock == 48000000l)
    {
        TK_Handle.Init.Div = TK_DIV2;      // 48M/2 = 24M
        TK_Handle.Init.Stdiv = TK_STDIV24; // 48M/24 = 2M
    }
    else
    {
        TK_Handle.Init.Div = TK_DIV0;      // 24M/1 = 24M
        TK_Handle.Init.Stdiv = TK_STDIV12; // 24M/12 = 2M
    }
    TK_Handle.Init.PwmM = SW_MODE;
    TK_Handle.Init.ExtCmod = EXTCMOD;
    TK_Handle.Init.CmphysEnable = ENABLE;
    TK_Handle.Init.Cft = TK_CFT7;
    TK_Handle.Init.Vcc1Cr = CONFIG_VCC1;
    TK_Handle.Init.CopaData = COPADATA_OUTPUT;
    TK_Handle.Init.CopaMode = COPA_ENABLE;
    TK_Handle.Init.CopaChs = TKCtr.TK_KeyEnable;
    TK_Handle.Init.Kenable = TKCtr.TK_KeyEnable;
#if (SW_MODE == TK_PWMM_PRS)
    TK_Handle.Init.Lfsrw = PWMM_PRS_LFSRW;
    TK_Handle.Init.Swdiv = SW_DIV;
	TK_Handle.Init.prsseed = PWMM_PRS_SEED;
    TK_Handle.Init.SetTime = TK_Handle.Init.Swdiv * 100;
#else
    TK_Handle.Init.Swdiv = SW_DIV;
    TK_Handle.Init.SetTime = TK_Handle.Init.Swdiv * 100;
#endif
    TK_Handle.Init.Win = CONFIG_WIN;
    TK_Handle.Init.ShortswNum = TK_SHORTSW_NUM_3;
    TK_Handle.Init.Vref = CONFIG_VREF;
    TK_Handle.Init.TrimEnable = CONFIG_IDAC0 | (CONFIG_IDAC1 << 1);
    if (TK_Handle.Init.TrimEnable == 0X00)
    {
        TK_Handle.Init.MidacStep = TK_MIDACSTEP_0_5UA;
        TK_Handle.Init.Midac = 200;
    }
    else
    {
        TK_Handle.Init.TrimRatio[0] = 70;
        TK_Handle.Init.TrimRatio[1] = 75;
    }
/*	Low power mode initialization	*/
#if (SLEEP_EN && TK_SLEEP)
    TKCtr.SleepEn = 1; // Enable sleep mode
    TK_Handle.Lp.EnterStopTimer = ENTER_SLEEPTIME;
    TK_Handle.Lp.LpWin = CONFIG_LP_WIN;
    TK_Handle.Lp.LpKchs = TKCtr.TK_KeyEnable;
    TK_Handle.Lp.Lpwait = 50 * st_clk;
    TK_Handle.Lp.Vref = CONFIG_LPVREF;
    TK_Handle.Lp.LpWakeTime = LP_WAUP_TIME;
#else
    TKCtr.SleepEn = 0; // Disable sleep mode
#endif
    TKCtr.SleepTime = 0;
    TK_LibInit();
}
/**
 * @brief Touch single-channel scan complete interrupt
 */
void TK_IRQHandler(void)
{
    TK_LibIRQHandler();
}
#if (SLEEP_EN && TK_SLEEP)
/**
 * @brief RTC interrupt
 */
void RTC_IRQHandler(void)
{
    if (LL_RTC_IsActiveFlag_SEC(RTC) != 0)
    {
        /* Clear sec flag */
        LL_RTC_ClearFlag_SEC(RTC);
        /*	If second interrupt is enabled before sleep, this will trigger at interval TK_Handle.Lp.LpWakeTime	*/
        Rtc_Wake |= 0X01;
    }
    if (LL_RTC_IsActiveFlag_ALR(RTC) != 0)
    {
        /* Clear alarm flag */
        LL_RTC_ClearFlag_ALR(RTC);
        /*	If alarm interrupt is enabled before sleep, this will trigger at interval TK_Handle.Lp.LpWakeTime * (TK_Handle.Lp.Alarm_tick + 1)
         */
        Rtc_Wake |= 0X02;
    }
}
#endif
#if TK_SLEEP
/**
 * @brief Callback function called when entering sleep mode
 * @param  None
 * @retval None
 */
static void EnterStop_Callback(void)
{
    /* Disable SysTick Interrupt */
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
#if (SLEEP_EN && TK_SLEEP)
    Rtc_Wake = 0;
#endif
    EXTI_Flag = 0;
/*	Low power mode initialization	*/
#if (SLEEP_EN && TK_SLEEP)
    TK_Handle.Lp.SleepTouchThd = LP_NORMRMALDELTA; // Set low-power mode threshold value
    TK_Handle.Lp.RtcInt = 0;//RTC_CRH_ALRIE;                       // RTC_CRH_ALRIE;          // RTC interrupt to enable
    TK_Handle.Lp.Alarm_tick = 10; 				   // Periodic MCU wake-up time when alarm interrupt is enabled
#endif
#if APP_ADC_ENABLE
    /*	Wait for ADC sequence conversion to complete*/
    while (LL_ADC_REG_IsConversionOngoing(ADC1) == 1)
    {
        ;
    }
    LL_ADC_Disable(ADC1);
#endif
#if (APP_TIM1_ENABLE || APP_TIM1_PWM_ENABLE)
    LL_TIM_DeInit(TIM1);
#endif
#if (APP_TIM14_ENABLE || APP_TIM14_PWM_ENABLE)
    LL_TIM_DeInit(TIM14);
#endif
#if APP_SMG_ENABLE
    SMG_Sleep();
#endif
}
/**
 * @brief Callback function called when exiting sleep mode
 * @param  None
 * @retval None
 */
static void ExitStop_Callback(void)
{
    /*	Touch wakeup		*/
    if (TK_Handle.Lp.WakeChs != 0)
    {
        TKCtr.SleepTime = 0;
    }
#if (SLEEP_EN && TK_SLEEP)
    /*	RTC wakeup flag	*/
    if (Rtc_Wake != 0)
    {
		
    }
#endif
    /*	External interrupt wakeup flag	*/
    if (EXTI_Flag != 0)
    {
        TKCtr.SleepTime = 0;
    }
#if APP_SMG_ENABLE
    SMG_Wake();
#endif
#if APP_ADC_ENABLE
    ADC_Init();
#endif
#if APP_TIM1_ENABLE
    /*	Timer 1 initialization	*/
    TIM1_Init();
#elif APP_TIM1_PWM_ENABLE
    /*	Timer 1 PWM output initialization	*/
    TIM1_PWM_Init();
#endif
#if APP_TIM14_ENABLE
    /*	Timer 14 initialization	*/
    TIM14_Init();
#elif APP_TIM14_PWM_ENABLE
    /*	Timer 14 PWM output initialization	*/
    TIM14_PWM_Init();
#endif
    /* Enable SysTick Interrupt */
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}
#endif
#if (LIB_TYPE > 1)
/**
 * @brief Touch waterproofing handler,
 * @param  	GuardBaseLineData		GuardeAcqData
 * @retval 	1: Water detected
            0: No water
 */
static uint8_t APP_TouchShieldFlagsMask(uint8_t chs, uint16_t BaseLineData, uint16_t AcqData)
{
    ShieldInfor.DusterClothDel = AcqData - BaseLineData;
    log_printf("ShieldDiffer:%d\r\n", ShieldInfor.DusterClothDel); // Get the data variation of the shield channel
    if (ShieldInfor.WaterProof_En == 1 && ShieldInfor.DusterCloth_En == 1)
    {
        if (ShieldInfor.DusterClothDel > ShieldInfor.DusterCloth_THD) // Water detected, return 1 to mask the key
            return 1;
    }
    return 0;
}
/**
 * @brief Touch waterproofing handler,
 * @param  	Differ: Normal sampling value		DifferSigle: Special sampling value
 * @retval 	0: Normal touch
            1: Water flow event
            2: Key trigger while water is present

 */
static uint8_t APP_TouchWaterFlagsMask(uint8_t chs, int16_t Differ, int16_t DifferSigle)
{
    ShieldInfor.trigger_ratio[0] = (DifferSigle * 100 / Differ);              // Key sampling ratio between two samples
    ShieldInfor.trigger_ratio[1] = ShieldInfor.DusterClothDel * 100 / Differ; // Ratio of COM channel differ to current key differ
    log_printf("key:%d, r0:%d r1:%d    ", chs, ShieldInfor.trigger_ratio[0], ShieldInfor.trigger_ratio[1]);
    if (ShieldInfor.WaterProof_En == 1)
    {
        // Water splash key detection
        if (ShieldInfor.WaterProof_Chs == TK_CH_NONE)
        {
            if (ShieldInfor.trigger_ratio[1] >= ShieldInfor.WaterProof_Ratio0)
            {
                log_printf("water flow! 1\r\n");
                return 1;
            }
        }
        else
        {
            if (ShieldInfor.trigger_ratio[0] >= ShieldInfor.WaterProof_Ratio1)
            {
                log_printf("water flow! 2\r\n");
                return 1;
            }
        }
        // Key detection with water present
        if (ShieldInfor.WaterProof_Mode == 1)
        {
            if (ShieldInfor.trigger_ratio[0] < ShieldInfor.WaterProof_Ratio0)
            {
                log_printf("water flow! 3\r\n");
                return 1;
            }
        }
        else
        {
            if (ShieldInfor.trigger_ratio[0] < ShieldInfor.WaterProof_Ratio0)
            {
                log_printf("water key press!\r\n");
                return 2;
            }
        }
    }
    log_printf("normal press!\r\n");
    return 0;
}
#endif
/**
 * @brief TK key mask: called by library when a key triggers; return 1 to suppress the key event
 * @param  None
 * @retval None
 */
static uint8_t APP_TouchKeyFlagsMask(void)
{
    return 0;
}
#else
/**
 * @brief  TK user parameter initialization
 * @param  None
 * @retval None
 */
void TK_UserParaInit(void)
{
}
/**
 * @brief  TK register initialization
 * @param  None
 * @retval None
 */
void TK_RegisterCfg(void)
{
}
#endif
