#include "function.h"
#include "power_ctrl.h"
#include "tim.h"
#include "hrtim.h"
#include "PID.h"

#define Beep 			1
#define Switch 			1
#define tarvoltage 	23.0f
#define tarpower 	30.0f
//CtrValue.Voref = 23.0f;
//CtrValue.Poref = 50.0f;

struct _Ctr_value CtrValue = { 0.0f, 0.0f, 0.0f, MIN_BUCK_DUTY, 0, 0, 0 }; //控制参数
struct _FLAG DF = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //控制标志位

//软启动状态标志位
SState_M STState = SSInit;
//IPS刷新计数 5mS计数一次，在5mS中断里累加
uint16_t IPSShowCnt = 0;
uint16_t CANSendCnt = 0;

/** ===================================================================
 **     Function Name :void StateM(void)
 **     Description :   状态机函数
 **                     state machine function
 **     初始化状态
 **     initial state
 **     等外启动状态
 **     wait state
 **     启动状态
 **     rise state
 **     运行状态
 **     run state
 **     故障状态
 **     error state
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void StateM(void)
{
    //判断状态类型
    //judge state type
    switch (DF.SMFlag)
    {
    //初始化状态
    case Init:
        StateMInit();
        break;
        //等待状态
    case Wait:
        StateMWait();
        break;
        //软启动状态
    case Rise:
        StateMRise();
        break;
        //运行状态
    case Run:
        StateMRun();
        break;
        //故障状态
    case Err:
        StateMErr();
        break;
    }
}
/** ===================================================================
 **     Function Name :void StateMInit(void)
 **     Description :   初始化状态函数，参数初始化
 **                     initial function, parameter initialed
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void StateMInit(void)
{
    //相关参数初始化
    //initial relative parameter
    ValInit();
    //状态机跳转至等待软启状态
    //go to wait state waiting for rise state
    DF.SMFlag = Wait;
}

/** ===================================================================
 **     Function Name :void StateMWait(void)
 **     Description :   等待状态机，等待1S后无故障则软启
 **                     wait state, wait for 1s to start when there is no error
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void StateMWait(void)
{
    //计数器定义
    //counter
    static uint16_t CntS = 0;

    //关PWM
    //shutdown PWM
    DF.PWMENFlag = 0;
    //计数器累加
    //counter add
    CntS++;
    //等待5ms*200，进入启动状态
    //wait for 5ms*200, entering rise state
    if (CntS > 256)
    {
        CntS = 256;
#if Switch
        if ((DF.ErrFlag == F_NOERR) && (DF.KeyFlag1 == 1))
        {
            //计数器清0
            //counter reset to zero
            CntS = 0;
            //状态标志位跳转至等待状态
            //state flag go 2 wait state
            DF.SMFlag = Rise;
            //软启动子状态跳转至初始化状态
            //soft start(rise state) go 2 initial state
            STState = SSInit;
        }
#else
        if (DF.ErrFlag == F_NOERR)
        {
            //计数器清0
            //counter reset to zero
            CntS = 0;
            //状态标志位跳转至等待状态
            //state flag go 2 wait state
            DF.SMFlag = Rise;
            //软启动子状态跳转至初始化状态
            //soft start(rise state) go 2 initial state
            STState = SSInit;
        }
#endif
    }
}
/*
 ** ===================================================================
 **     Function Name : void StateMRise(void)
 **     Description :软启阶段
 **     软启初始化
 **     软启等待
 **     开始软启
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MAX_SSCNT       20 //等待100ms
//wait for 100ms
void StateMRise(void)
{
    //计时器
    //counter
    static uint16_t Cnt = 0;
    //最大占空比限制计数器
    //maxim duty restrict counter
    static uint16_t BuckMaxDutyCnt = 0;
    static uint16_t BoostMaxDutyCnt = 0;

    //判断软启状态
    //judge soft start state
    switch (STState)
    {
    //初始化状态
    //initial state
    case SSInit:
    {
        //关闭PWM
        //shutdown PWM
        DF.PWMENFlag = 0;
        HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
        //软启中将运行限制占空比启动，从最小占空比开始启动
        //soft starting will restrict operating duty, start at minimum duty
        CtrValue.BuckMaxDuty = MIN_BUCK_DUTY;
        CtrValue.BoostMaxDuty = MIN_BOOST_DUTY;
        //环路计算变量初始化
        //control loop calculate parameter initial
        PID_clear(&voltageout_loop);
        PID_clear(&currentout_loop);
        PID_clear(&powerin_loop);
        //跳转至软启等待状态
        //jump 2 soft start waiting state
        STState = SSWait;

        break;
    }
        //等待软启动状态
        //soft start waiting state
    case SSWait:
    {
        //计数器累加
        //counter add
        Cnt++;
        //等待100ms
        //wait for 100ms
        if (Cnt > MAX_SSCNT)
        {
            //计数器清0
            //counter reset 2 0
            Cnt = 0;
            //环路计算变量初始化
            //control loop calculate parameter initial
            PID_clear(&voltageout_loop);
            PID_clear(&currentout_loop);
            PID_clear(&powerin_loop);
            //限制启动占空比
            //restrict operation duty
            if (cap.V <= 5.0f)
            {
                CtrValue.BuckDuty = cap.V / in.V * HRTIMB_Period;
                CtrValue.BuckMaxDuty = MIN_BUCK_DUTY;
                CtrValue.BoostDuty = MIN_BOOST_DUTY;
                CtrValue.BoostMaxDuty = MIN_BOOST_DUTY;
            }
            else
            {
                CtrValue.BuckDuty = cap.V / in.V * HRTIMB_Period;
                CtrValue.BuckMaxDuty = MAX_BUCK_DUTY;
                CtrValue.BoostDuty = MIN_BOOST_DUTY;
                CtrValue.BoostMaxDuty = MAX_BOOST_DUTY;
            }
            STState = SSRun;    //跳转至软启状态
                                //jump 2 soft start state
        }
        break;
    }
        //软启动状态
        //soft start state
    case SSRun:
    {
        if (DF.PWMENFlag == 0)  //正式发波前环路变量清0
                                //clean all control loop parameter when starting PWM
        {
            //环路计算变量初始化
            //initial control loop parameter
            PID_clear(&voltageout_loop);
            PID_clear(&currentout_loop);
            PID_clear(&powerin_loop);
            //enable mosfet driver
#if calibration == 1
            HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_SET);
#else
            HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_RESET);
#endif
            HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //开启PWM输出和PWM计时器
        }
        //发波标志位置位
        //PWM start flag
        DF.PWMENFlag = 1;
        //最大占空比限制逐渐增加
        //maximum PWM duty add gradually
        BuckMaxDutyCnt++;
        BoostMaxDutyCnt++;
        //最大占空比限制累加
        //PWM maximum restrict add gradually
        CtrValue.BuckMaxDuty = CtrValue.BuckMaxDuty + BuckMaxDutyCnt * 5;
        CtrValue.BoostMaxDuty = CtrValue.BoostMaxDuty + BoostMaxDutyCnt * 5;
        if (CtrValue.BuckMaxDuty > MAX_BUCK_DUTY * 0.3)
        {
            HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_SET);
        }
        //累加到最大值
        //add to the maximum value
        if (CtrValue.BuckMaxDuty > MAX_BUCK_DUTY)
        {
            CtrValue.BuckMaxDuty = MAX_BUCK_DUTY;
        }
        if (CtrValue.BoostMaxDuty > MAX_BOOST_DUTY)
        {
            CtrValue.BoostMaxDuty = MAX_BOOST_DUTY;
        }

        if (CtrValue.BuckMaxDuty == MAX_BUCK_DUTY && CtrValue.BoostMaxDuty == MAX_BOOST_DUTY)
        {
            //状态机跳转至运行状态
            //state machine jump 2 run state
            DF.SMFlag = Run;
            //软启动子状态跳转至初始化状态
            //soft start state jump 2 initial state
            STState = SSInit;
        }
        break;
    }
    default:
        break;
    }
}
/*
 ** ===================================================================
 **     Function Name :void StateMRun(void)
 **     Description :正常运行，主处理函数在中断中运行
 **                  normal operation, main function is run in interrupt
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
void StateMRun(void)
{

}

/*
 ** ===================================================================
 **     Function Name :void StateMErr(void)
 **     Description :故障状态
 **                  error state
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
void StateMErr(void)
{
    //关闭PWM
    //Shutdown PWM
    DF.PWMENFlag = 0;
    HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_RESET);
    HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭

    //若故障消除跳转至等待重新软启
    //restart when error state clear up
    if (DF.ErrFlag == F_NOERR)
        DF.SMFlag = Wait;
}

/** ===================================================================
 **     Function Name :void ValInit(void)
 **     Description :   相关参数初始化函数
 **                     relate parameter initial function
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void ValInit(void)
{
    //关闭PWM
    //Shutdown PWM
    DF.PWMENFlag = 0;
    HAL_GPIO_WritePin(R_OD_GPIO_Port, R_OD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L_OD_GPIO_Port, L_OD_Pin, GPIO_PIN_RESET);
    HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
    //清除故障标志位
    //reset error flag
    DF.ErrFlag = 0;
    //初始化参考量
    //initial reference parameter
    CtrValue.Voref = 0;
    CtrValue.Ioref = 0;
    CtrValue.Poref = 0;
    //限制占空比
    //restrict PWM duty
    CtrValue.BuckDuty = MIN_BUCK_DUTY;
    CtrValue.BuckMaxDuty = MIN_BUCK_DUTY;
    CtrValue.BoostDuty = MIN_BOOST_DUTY;
    CtrValue.BoostMaxDuty = MIN_BOOST_DUTY;
    //环路计算变量初始化
    //control loop initial
    PID_clear(&voltageout_loop);
    PID_clear(&currentout_loop);
    PID_clear(&powerin_loop);
}

/*
 ** ===================================================================
 **     Function Name :void ShortOff(void)
 **     Description :短路保护，可以重启10次
 **                  shortage protect, can restart 10 times
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MAX_SHORT_I     14.0f//短路电流判据
//shortage current judgment
#define MIN_SHORT_V     0.2f//短路电压判据
//shortage voltage judgment
void ShortOff(void)
{
    static uint16_t RSCnt = 0;
    static uint16_t RSNum = 0;

    //当output current大于 15A，且output voltage小于0.2V时，可判定为发生短路保护
    //when output current is larger than 11A and output voltage less than 0.2V,
    //can trigger shortage protect
    if ((cap.I > MAX_SHORT_I) && (cap.V < MIN_SHORT_V))
    {
        //关闭PWM
        //shutdown PWM
        DF.PWMENFlag = 0;
        HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
        //故障标志位
        //error flag
        setRegBits(DF.ErrFlag, F_SW_SHORT);
        //跳转至故障状态
        //jump 2 error state
        DF.SMFlag = Err;
    }
    //输出短路保护恢复
    //recover for shortage protect
    //当发生输出短路保护，关机后等待4S后清除故障信息，进入等待状态等待重启
    //when triggered shortage protect, shutdown for 4s to wait for error state clean up,
    //entering wait state
    if (getRegBits(DF.ErrFlag, F_SW_SHORT))
    {
        //等待故障清楚计数器累加
        //wait for error flag cleaning counter
        RSCnt++;
        //等待2S
        //wait for 2s
        if (RSCnt > 400)
        {
            //计数器清零
            //counter reset
            RSCnt = 0;
            //短路重启只重启10次，10次后不重启
            //shortage protect only reset for 10 times,
            //after 10 times system shutdown
            if (RSNum > 10)
            {
                //确保不清除故障，不重启
                //ensuring not clean error flag
                RSNum = 11;
                //关闭PWM
                //shutdown PWM
                DF.PWMENFlag = 0;
                HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            }
            else
            {
                //短路重启计数器累加
                //shortage protect counter add
                RSNum++;
                //清除过流保护故障标志位
                //clean shortage protect flag
                clrRegBits(DF.ErrFlag, F_SW_SHORT);
            }
        }
    }
}
/*
 ** ===================================================================
 **     Function Name :void SwOCP(void)
 **     Description :软件过流保护，可重启
 **                  software shortage protect, can restart
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MAX_OCP_VAL     13.0f//13A过流保护点
void SwOCP(void)
{
    //过流保护判据保持计数器定义
    static uint16_t OCPCnt = 0;
    //故障清楚保持计数器定义
    static uint16_t RSCnt = 0;
    //保留保护重启计数器
    static uint16_t RSNum = 0;

    //当output current大于*A，且保持500ms
    if ((cap.I > MAX_OCP_VAL) && (cap.I < -MAX_OCP_VAL) && (DF.SMFlag == Run))
    {
        //条件保持计时
        OCPCnt++;
        //条件保持50ms，则认为过流发生
        if (OCPCnt > 10)
        {
            //计数器清0
            OCPCnt = 0;
            //关闭PWM
            DF.PWMENFlag = 0;
            HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            //故障标志位
            setRegBits(DF.ErrFlag, F_SW_IOUT_OCP);
            //跳转至故障状态
            DF.SMFlag = Err;
        }
    }
    else
        //计数器清0
        OCPCnt = 0;

    //输出过流后恢复
    //当发生输出软件过流保护，关机后等待4S后清除故障信息，进入等待状态等待重启
    if (getRegBits(DF.ErrFlag, F_SW_IOUT_OCP))
    {
        //等待故障清楚计数器累加
        RSCnt++;
        //等待2S
        if (RSCnt > 400)
        {
            //计数器清零
            RSCnt = 0;
            //过流重启计数器累加
            RSNum++;
            //过流重启只重启10次，10次后不重启（严重故障）
            if (RSNum > 10)
            {
                //确保不清除故障，不重启
                RSNum = 11;
                //关闭PWM
                DF.PWMENFlag = 0;
                HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            }
            else
            {
                //清除过流保护故障标志位
                clrRegBits(DF.ErrFlag, F_SW_IOUT_OCP);
            }
        }
    }
}

/*
 ** ===================================================================
 **     Function Name :void SwOVP(void)
 **     Description :软件输出过压保护，不重启
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MAX_VOUT_OVP_VAL    24.0f//24V过压保护
void VoutSwOVP(void)
{
    //过压保护判据保持计数器定义
    static uint16_t OVPCnt = 0;
    //故障清楚保持计数器定义

    //当output voltage大于24V，且保持10ms
    if (cap.V > MAX_VOUT_OVP_VAL)
    {
        //条件保持计时
        OVPCnt++;
        //条件保持10ms
        if (OVPCnt > 2)
        {
            //计时器清零
            OVPCnt = 0;
            //关闭PWM
            DF.PWMENFlag = 0;
            HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            //故障标志位
            setRegBits(DF.ErrFlag, F_SW_VOUT_OVP);
            //跳转至故障状态
            DF.SMFlag = Err;
        }
    }
    else
        OVPCnt = 0;
}

/*
 ** ===================================================================
 **     Function Name :void VinSwUVP(void)
 **     Description :输入软件欠压保护，低压输入保护,可恢复
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MIN_UVP_VAL    20.0f//20V欠压保护
#define MIN_UVP_VAL_RE 21.0f//21.0V欠压保护恢复
void VinSwUVP(void)
{
    //过压保护判据保持计数器定义
    static uint16_t UVPCnt = 0;
    static uint16_t RSCnt = 0;

    //当input voltage小于20V，且保持10ms
    if ((in.V < MIN_UVP_VAL) && (DF.SMFlag != Init) && (!DF.BBModeChange))
    {
        //条件保持计时
        UVPCnt++;
        //条件保持10ms
        if (UVPCnt > 2)
        {
            //计时器清零
            UVPCnt = 0;
            RSCnt = 0;
            //关闭PWM
            DF.PWMENFlag = 0;
            HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            //故障标志位
            setRegBits(DF.ErrFlag, F_SW_VIN_UVP);
            //跳转至故障状态
            DF.SMFlag = Err;
        }
    }
    else
        UVPCnt = 0;

    //输入欠压保护恢复
    //当发生输入欠压保护，等待输入电压恢复至正常水平后清楚故障标志位，重启
    if (getRegBits(DF.ErrFlag, F_SW_VIN_UVP))
    {
        if (in.V > MIN_UVP_VAL_RE)
        {
            //等待故障清楚计数器累加
            RSCnt++;
            //等待1S
            if (RSCnt > 200)
            {
                RSCnt = 0;
                UVPCnt = 0;
                //清楚故障标志位
                clrRegBits(DF.ErrFlag, F_SW_VIN_UVP);
            }
        }
        else
            RSCnt = 0;
    }
    else
        RSCnt = 0;
}

/*
 ** ===================================================================
 **     Funtion Name :void VinSwOVP(void)
 **     Description :软件输入过压保护，不重启
 **     Parameters  : none
 **     Returns     : none
 ** ===================================================================
 */
#define MAX_VIN_OVP_VAL    28.0f//28V过压保护
void VinSwOVP(void)
{
    //过压保护判据保持计数器定义
    static uint16_t OVPCnt = 0;

    //当input voltage大于28V，且保持100ms
    if (in.V > MAX_VIN_OVP_VAL)
    {
        //条件保持计时
        OVPCnt++;
        //条件保持10ms
        if (OVPCnt > 2)
        {
            //计时器清零
            OVPCnt = 0;
            //关闭PWM
            DF.PWMENFlag = 0;
            HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1); //关闭
            //故障标志位
            setRegBits(DF.ErrFlag, F_SW_VIN_OVP);
            //跳转至故障状态
            DF.SMFlag = Err;
        }
    }
    else
        OVPCnt = 0;
}

/** ===================================================================
 **     Funtion Name :void LEDShow(void)
 **     Description :  LED显示函数
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void LEDShow(void)
{
    switch (DF.SMFlag)
    {
    //init state, light up all led
    case Init:
    {
        htim1.Instance->CCR1 = 0;
        htim1.Instance->CCR2 = 3400;
        htim1.Instance->CCR3 = 3400;
        htim1.Instance->CCR4 = 3400;
        break;
    }
        //wait state, light up blue led
    case Wait:
    {
        htim1.Instance->CCR1 = 0;
        htim1.Instance->CCR2 = 0;
        htim1.Instance->CCR3 = 0;
        htim1.Instance->CCR4 = 3400;
        break;
    }
        //soft start state, light up green and blue led
    case Rise:
    {
        htim1.Instance->CCR1 = 0;
        htim1.Instance->CCR2 = 0;
        htim1.Instance->CCR3 = 3400;
        htim1.Instance->CCR4 = 3400;
        break;
    }
        //normal state, light up green led
    case Run:
    {
        htim1.Instance->CCR1 = 0;
        htim1.Instance->CCR2 = 0;
        htim1.Instance->CCR3 = 3400;
        htim1.Instance->CCR4 = 0;
        break;
    }
        //wrong state, light up red led
    case Err:
    {
#if Beep
        htim1.Instance->CCR1 = 1700;
#endif
        htim1.Instance->CCR2 = 3400;
        htim1.Instance->CCR3 = 0;
        htim1.Instance->CCR4 = 0;
        break;
    }
    }
}

/** ===================================================================
 **     Funtion Name :void KEYFlag(void)
 **     Description :按键的状态
 **      默认状态KEYFlag为0.按下时Flag变1，再次按下Flag变0，依次循环
 **      当机器正常运行，或者启动过程中，按下按键后，关闭输出，进入待机状态
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
#define READ_KEY1() HAL_GPIO_ReadPin(EC11_K_GPIO_Port, EC11_K_Pin)
void KEYFlag(void)
{
    //计时器，按键消抖用
    static uint16_t KeyDownCnt1 = 0;

    //按键按下
    if (READ_KEY1() == 0)
    {
        //计时，按键按下100mS有效
        KeyDownCnt1++;
        if (KeyDownCnt1 > 20)
        {
            KeyDownCnt1 = 0;            //计时器清零
            //按键状态有变化
            if (DF.KeyFlag1 == 0)
                DF.KeyFlag1 = 1;
            else
                DF.KeyFlag1 = 0;
        }
    }
    else
        KeyDownCnt1 = 0;            //计时器清零

    //当机器正常运行，或者启动过程中，按下按键后，关闭输出，进入待机状态
#if Switch
    if ((DF.KeyFlag1 == 0) && ((DF.SMFlag == Rise) || (DF.SMFlag == Run)))
    {
        DF.SMFlag = Wait;
        //关闭PWM
        DF.PWMENFlag = 0;
        HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TB1);            //关闭
    }
#endif
}

/** ===================================================================
 **     Funtion Name :void BBMode(void)
 **     Description :运行模式判断
 **      Buck模式：输出参考电压<0.8倍输入电压
 **      MIX模式：1.2倍输入电压>输出参考电压>0.8倍输入电压
 **      当进入MIX（buck-boost）模式后，退出到 Buck时需要滞缓，防止在临界点来回振荡
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void BBMode(void)
{
    //上一次模式状态量
    uint8_t PreBBFlag = 0;

    //暂存当前的模式状态量
    PreBBFlag = DF.BBFlag;
    switch (DF.BBFlag)
    {
    //NA
    case NA0:
    {
        /*init control value*/
        CtrValue.Voref = tarvoltage;
        CtrValue.Poref = tarpower;
        //power ref will change in CAN_receive file, HAL_FDCAN_RxFifo0Callback function

        if (cap.V < (in.V * 0.8f)) //vout<0.8*vin
        {
            DF.BBFlag = Buck; //buck mode
        }
        else
        {
            DF.BBFlag = Mix; //buck-boost mode
        }
        break;
    }
        // Buck模式
    case Buck:
    {
        if (cap.V > (in.V * 0.85f)) //1.2*vin>vout>0.85*vin
        {
            DF.BBFlag = Mix; //buck-boost mode
        }
        break;
    }
        //Mix模式
    case Mix:
    {
        if (cap.V < (in.V * 0.8f)) //vout<0.8*vin
        {
            DF.BBFlag = Buck; //buck mode
        }
        break;
    }
    }
    //when mode changes,set reg
    if (PreBBFlag != DF.BBFlag)
        DF.BBModeChange = 1;
//    else
//        DF.BBModeChange = 0;

}

/** ===================================================================
 **     Function Name :void DRMode(void)
 **     Description:currnt direction judge
 **     Charge mode:battery charges cap
 **     Discharge mode:cap discharge power to chassis
 **     when get into Discharge mode,exits need to put in a delay,in order to avoid oscillating
 **     Parameters  :
 **     Returns     :
 ** ===================================================================*/
void DRMode(void)
{
    //last dr mode
    uint8_t PreDRFlag = 0;

    //save current dr mode
    PreDRFlag = DF.DRFlag;

    /*full_bridge_in.I = c_in.value_elec - c_chassis.value_elec;*/
    switch (DF.DRFlag)
    {
    //PID set - ref, when over power, error is below 0
    //NA
    case NA1:
    {
        if (powerin_loop.out >= 0)
        {
            DF.DRFlag = Charge;     //charge mode
        }
        else
        {
            DF.DRFlag = Discharge;  //Discharge mode
        }
        break;
    }
        // charge mode
    case Charge:
    {
        if (powerin_loop.out < 0)
        {
            DF.DRFlag = Discharge;  //Discharge mode
        }
        break;
    }
        //discharge mode
    case Discharge:
    {
        if (powerin_loop.out >= 0)
        {
            DF.DRFlag = Charge;     //charge mode
        }
        break;
    }
    }
    //when mode changes,set reg
    if (PreDRFlag != DF.DRFlag)
        DF.DRModeChange = 1;
    else
        DF.DRModeChange = 0;

}
