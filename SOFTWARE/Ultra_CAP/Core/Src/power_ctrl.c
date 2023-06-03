#include "power_ctrl.h"
#include "function.h"
#include "pid.h"
#include "filter.h"
#include "IIR_FIlter.h"

ELEC_INFO_STRUCT c_in;      //current in
ELEC_INFO_STRUCT c_cap;     //current cap
ELEC_INFO_STRUCT c_chassis; //current chassis
ELEC_INFO_STRUCT v_in;      //voltage in
ELEC_INFO_STRUCT v_cap;     //voltage cap

CCMRAM CONTROL_STRUCT in, chassis, full_bridge_in, cap;
//     BAT_input output_chassis dcdc_input dcdc_output(cap)

volatile fp32 pid_final = 0;
volatile fp32 capIcalc = 0;

volatile uint16_t HRTIM_DMA_Buffer[4] = { 0, 12920, 100, 25840 };
//                             buck_duty adc_duty boostup_duty boostdown_duty

/*Linear calibration once*/
void ADC_Linear_calibration_init(ELEC_INFO_STRUCT *p, fp32 real1, fp32 get1, fp32 real2, fp32 get2)
{
    fp64 a, b;
    p->get_volt1 = get1;
    p->get_volt2 = get2;
    p->real_value1 = real1;
    p->real_value2 = real2;
    if ((p->get_volt2 - p->get_volt1 == 0) || (p->real_value2 - p->real_value1 == 0))
    {
        return;
    }

    a = (p->real_value2 - p->real_value1) / (p->get_volt2 - p->get_volt1);
    b = (p->real_value1 - p->get_volt1 * a);

    p->ratio = a * p->ratio;
    p->offset = b;
}

/*change adc value to elec(A, V)*/
CCMRAM void ADC_value_to_elec(ELEC_INFO_STRUCT *p)
{
    p->value_elec = (p->value_origin) * p->ratio + p->offset;
}

/*power control function init*/
void power_init(void)
{
    /*V_Gain is (2.21K + 20 K) / 2.21K*/
    v_in.elec_type = 0;
    v_in.ratio = (10.0f * VDDA) / ADC_Maxvalue;
    v_in.offset = 0;
    v_cap.elec_type = 0;
    v_cap.ratio = (10.0f * VDDA) / ADC_Maxvalue;
    v_cap.offset = 0;

    /*I_Gain is 1 / (1m * 200)*/
    c_in.elec_type = 1;
    c_in.ratio = (VDDA * 5.0f) / ADC_Maxvalue;
    c_in.offset = 0;
    c_cap.elec_type = 1;
    c_cap.ratio = (VDDA * 5.0f) / ADC_Maxvalue;
    c_cap.offset = 0;
    c_chassis.elec_type = 1;
    c_chassis.ratio = (VDDA * 5.0f) / ADC_Maxvalue;
    c_chassis.offset = 0;

#define PARA_CAL_ENABLE (1) //elec_calibration: 0 -> disable; 1 -> enable
#define board_num (2)       //board series num
#define LPF_ENABLE (0)      //low pass filter: 0 -> disable; 1 -> enable

#if PARA_CAL_ENABLE == 1

#if board_num == 1 //finished
    ADC_Linear_calibration_init(&c_in, 1.004f, 1.361905f, 8.0f, 11.161173f);
    ADC_Linear_calibration_init(&c_cap, 1.0f, 1.35f, 8.01f, 10.56f);
    ADC_Linear_calibration_init(&c_chassis, 1.0f, 1.42f, 8.0f, 11.1f);
#endif
#if board_num == 2 //have to finish
    ADC_Linear_calibration_init(&c_in, 1.005f, 1.56f, 8.003f, 12.3f);
    ADC_Linear_calibration_init(&c_cap, 1.012f, 1.33f, 7.99f, 10.32f);
    ADC_Linear_calibration_init(&c_chassis, 1.0f, 1.45f, 7.99f, 10.95f);
#endif
#if board_num == 3 //have to finish
    ADC_Linear_calibration_init(&c_in, 1.006f, 1.535165f, 8.004f, 12.16f);
    ADC_Linear_calibration_init(&c_cap, 1.0f, 1.35f, 7.99f, 10.25f);
    ADC_Linear_calibration_init(&c_chassis, 1.0f, 1.4f, 7.99f, 10.77f);
#endif
#if board_num == 4 //have to finish
    ADC_Linear_calibration_init(&c_in, 1.006f, 1.482784f, 8.006f, 11.95f);
    ADC_Linear_calibration_init(&c_cap, 1.0f, 1.34f, 7.99f, 10.14f);
    ADC_Linear_calibration_init(&c_chassis, 1.0f, 1.39f, 7.99f, 10.71f);
#endif

#endif

    /*PID init is in function BuckBoostVLoopCtlPID*/
//    PID_init(&voltageout_loop, 0.03f, 450.0f / 200000.0f, 0.000008f * 200000.0f, 0.95, 1, 0, -1); //voltage loop
//    PID_init(&voltageout_loop, 0.0164f, 76.0f / 200000.0f, 0.00000647f * 200000.0f, 0.53, 1, 0, -1); //voltage loop
//    PID_init(&currentout_loop, 0.006f, 22.0f / 200000.0f, 0.0f * 200000.0f, 0.95, 1, 0, -1); //current loop
//    PID_init(&powerin_loop, 0.0042f, 5.627f / 200000.0f, 0.0f * 200000.0f, 0.95, 1, 0, -1);   //power loop
//    PID_init(&power_referee_loop, 0.3,0.05f,0, 120, 50, -120, -50);
    /*LPF init*/
#if LPF_ENABLE == 1
    for (char i = 0; i < 5; i++)
    {
        low_filter_init(&lpf[i], 200e3, 30e3);
    }
#endif

}

/*ADC sample function*/
CCMRAM void ADCSample(void)
{

    ADC_value_to_elec(&c_cap);
    ADC_value_to_elec(&c_chassis);
    ADC_value_to_elec(&v_in);
    ADC_value_to_elec(&v_cap);

    //ADC c_in calculate is last to wait for FMAC finish
    ADC_value_to_elec(&c_in);

    //sample has 0 shift,use 0 when sample num are too small
    if (v_cap.value_elec <= 0.1f)
    {
        v_cap.value_elec = 0.1f;  //prevent from dividing 0
    }

    /*ADC sampling filtered in ADC peripheral's internal adder and shifter to release CPU load*/
#if LPF_ENABLE == 1
//    lpf[0].Input = c_in.value_elec;
//    lpf[1].Input = in.V * in.I;
//    lpf[1].Input = v_in.value_elec;
//    lpf[2].Input = v_cap.value_elec;
//    lpf[3].Input = c_cap.value_elec;
//    lpf[4].Input = c_chassis.value_elec;

//    for (char i = 0; i < 5; i++)
//    {
//        low_filter_calc(&lpf[i]);
//    }

    in.V = v_in.value_elec;
    in.I = c_in.value_elec;

    /*power in filter*/
    lpf[1].Input = in.V * in.I;
    low_filter_calc(&lpf[1]);
    in.P = lpf[1].Output;
    in.P = in.V * in.I;

    full_bridge_in.I = c_in.value_elec - c_chassis.value_elec;
    cap.V = v_cap.value_elec;

    /*calculate cap current*/
    capIcalc = (in.V / cap.V) * full_bridge_in.I * 1.1f;

    if (capIcalc >= 1.0f)
    {
        cap.I = c_cap.value_elec;
    }
    else
    {
        cap.I = capIcalc;
    }
    cap.P = cap.V * cap.I;

#else
    in.V = v_in.value_elec;
    in.I = c_in.value_elec;

    in.P = in.V * in.I;

    full_bridge_in.I = c_in.value_elec - c_chassis.value_elec;
    cap.V = v_cap.value_elec;

    /*calculate cap current*/
    capIcalc = (in.V / cap.V) * full_bridge_in.I * 1.1f;

    if (capIcalc >= 0.5f)
    {
        cap.I = c_cap.value_elec;
    }
    else
    {
        cap.I = capIcalc;
    }
    cap.P = cap.V * cap.I;
#endif
}

/*
 ** ===================================================================
 **     Funtion Name : void BuckBoostVLoopCtlPID(void)
 **     Description :  BUCK-BOOST模式下环路计算
 **                    BUCK-BOOST mode loop calculate
 **     检测输出参考电压与输入电压的关系，判断环路工作于BUCK模式，还是BUCK-BOOST模式
 **     detect output reference voltage's relationship with input voltage,
 **     judge loop control mode is buck-boost mode or buck mode
 **     BUCK模式下，BOOST的开关管工作在固定占空比，控制BUCK的占空比控制输出电压
 **     in BUCK mode, boost side mosfet is work in fixed duty, buck side mosfet control output voltage
 **     BUCK-BOOST模式下，BUCK的开关管工作在固定占空比，控制BOOST的占空比控制输出电压
 **     in BUCK-BOOST mode, buck side mosfet is work in fixed duty, boost side mosfet control output voltage
 **     Parameters  :无
 **                 none
 **     Returns     :无
 **                 none
 ** ===================================================================
 */
CCMRAM void BuckBoostVLoopCtlPID(void)
{
//    static uint16_t BBmodecnt;

    //when buck-boost mode changes, need to turn down pwm out to avoid oscillating
    //BBModeChange is mode changing flag
    if (DF.BBModeChange)
    {
        PID_clear(&voltageout_loop);
        PID_clear(&currentout_loop);
        PID_clear(&powerin_loop);
    }

    /*judge operation mode, BUCK or BUCK-BOOST*/
    switch (DF.BBFlag)
    {
    case NA0:   //init
    {
        PID_clear(&voltageout_loop);
        PID_clear(&currentout_loop);
        PID_clear(&powerin_loop);
        break;
    }
    case Buck:  //BUCK mode
    {
        /*PID init*/
        if (DF.BBModeChange)
        {
            PID_init(&voltageout_loop, 0.03f, 200.0f / 200000.0f, 8e-06f * 200000.0f, 0.95, 1, 0.05, -1);   //buck voltage loop
            PID_init(&currentout_loop, 0.007f, 64.0f / 200000.0f, 8.7e-07f * 200000.0f, 0.95, 1, 0.05, -1); //buck current loop
            PID_init(&powerin_loop, 0.009f, 35.0f / 200000.0f, 4e-06f * 200000.0f, 12, 12, -12, -12);       //buck power loop
            HRTIM_DMA_Buffer[3] = (uint16_t) (0.96 * HRTIMA_Period);
            DF.BBModeChange = 0;
        }

        /*PID calculate*/
        PID_calc(&voltageout_loop, cap.V, CtrValue.Voref);
        PID_calc(&powerin_loop, in.P, CtrValue.Poref);
        PID_calc(&currentout_loop, cap.I, powerin_loop.out);
        /*PID select*/

        if (currentout_loop.out < voltageout_loop.out)
        {
            pid_final = currentout_loop.out;
            DF.Cloop = current_loop;
        }
        else
        {
            pid_final = voltageout_loop.out;
            DF.Cloop = voltage_loop;
        }

#if LPF_ENABLE == 1
        /*PID out filter*/
        lpf[4].Input = pid_final;
        low_filter_calc(&lpf[4]);
        /*PID update*/
        CtrValue.BuckDuty = lpf[4].Output * HRTIMB_Period;
#else
        /*PID update*/
        CtrValue.BuckDuty = pid_final * HRTIMB_Period;
#endif
        CtrValue.BoostDuty = MIN_REG_VALUE; //BOOST duty fixed PWM 0.95

        /*max out & min out restrict*/
        //soft start related
        if (CtrValue.BuckDuty > CtrValue.BuckMaxDuty)
        {
            CtrValue.BuckDuty = CtrValue.BuckMaxDuty;
        }
        //avoiding a voltage spike
        if (CtrValue.BuckDuty < (cap.V / 33.0f * HRTIMB_Period))
        {
            CtrValue.BuckDuty = cap.V / 33.0f * HRTIMB_Period;
        }
        break;
    }
    case Mix:   //Mix mode
    {
        /*PID init*/
        if (DF.BBModeChange)
        {
            PID_init(&voltageout_loop, 0.03f, 200.0f / 200000.0f, 8e-06f * 200000.0f, 0.5, 0.5, 0.05, -0.5);    //buckboost voltage loop
            PID_init(&currentout_loop, 0.01f, 68.0f / 200000.0f, 1.3e-06f * 200000.0f, 0.5, 0.5, 0.05, -0.5);   //buckboost current loop
            PID_init(&powerin_loop, 0.0065f, 9.0f / 200000.0f, 3.3e-07f * 200000.0f, 8, 8, -8, -8);             //buckboost power loop
            HRTIM_DMA_Buffer[3] = (uint16_t) (HRTIMA_Period - MIN_REG_VALUE );
        }

        /*PID calculate*/
        PID_calc(&voltageout_loop, cap.V, CtrValue.Voref);
        PID_calc(&powerin_loop, in.P, CtrValue.Poref);
        PID_calc(&currentout_loop, cap.I, powerin_loop.out);
        /*PID select*/

        if (currentout_loop.out < voltageout_loop.out)
        {
            pid_final = currentout_loop.out;
            DF.Cloop = current_loop;
        }
        else
        {
            pid_final = voltageout_loop.out;
            DF.Cloop = voltage_loop;
        }

#if LPF_ENABLE == 1
        /*PID out filter*/
        lpf[4].Input = pid_final;
        low_filter_calc(&lpf[4]);
        /*PID update*/
        CtrValue.BoostDuty = lpf[4].Output * HRTIMB_Period;
#else
        /*PID update*/
        CtrValue.BoostDuty = pid_final * HRTIMA_Period;
#endif
        CtrValue.BuckDuty = MAX_BUCK_DUTY1; //buck duty fix 0.75

        /*max out & min out restrict*/
        //when topology changes, need to give a initial status
        if (DF.BBModeChange)
        {
            //soft change
            CtrValue.BoostDuty = (1.003f - 0.8f * in.V / cap.V) * HRTIMA_Period;
            DF.BBModeChange = 0;
        }
        //soft start related
        if (CtrValue.BoostDuty > CtrValue.BoostMaxDuty)
        {
            CtrValue.BoostDuty = CtrValue.BoostMaxDuty;
        }
        break;
    }
    }

    /*PWMENFlag is pwm enable flag, when this reg unset, PWM get to minimum period*/
    if (DF.PWMENFlag == 0)
    {
        CtrValue.BuckDuty = MIN_BUCK_DUTY;
        CtrValue.BoostDuty = MIN_BOOST_DUTY;
    }

    /*update PWM regs*/
    HRTIM_DMA_Buffer[0] = CtrValue.BuckDuty;    //Buck PWM update
    HRTIM_DMA_Buffer[1] = CtrValue.BuckDuty >> 1;   //ADC sampling trigger
    HRTIM_DMA_Buffer[2] = CtrValue.BoostDuty;   //Boost PWM update
}
