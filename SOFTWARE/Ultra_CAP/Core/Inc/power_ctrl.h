#ifndef __POWER_CTRL_H
#define __POWER_CTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

/*ADC related*/
#define buf_len 1           //DMA buf length
#define ADC_Maxvalue 0xFFF  //voltage signal 12bit ADC 32x samples, 5 bits shift
                            //current signal 12bit ADC 4x  samples, 2 bits shift
#define VDDA 3.3f           //This is the VDDA supply in V

/*Hardware restriction*/
#define cap_resistance (135.0f/1000.0f) //电容内阻毫欧
#define powerbuffermin 30.0f            //缓冲能量剩余阈值

typedef struct
{
    uint8_t elec_type;          //0电压1电流
    fp32 get_volt1;             //测量值1    单片机滤波后获得
    fp32 get_volt2;             //测量值2    单片机滤波后获得
    fp32 real_value1;           //真实值1    外部仪表获得
    fp32 real_value2;           //真实值2    外部仪表获得
    fp32 offset;                //漂移
    fp32 ratio;                 //比例系数
    //漂移和比例系数是校准参数
    uint16_t value_origin;      //ADC原始数据
    fp32 value_elec;            //换算后的原始数据
} ELEC_INFO_STRUCT;

typedef struct
{
    fp32 V;
    fp32 I;
    fp32 P;

} CONTROL_STRUCT;

extern ELEC_INFO_STRUCT c_in, c_cap, c_chassis, v_in, v_cap;
extern CONTROL_STRUCT in, chassis, full_bridge_in, cap;
extern volatile uint16_t HRTIM_DMA_Buffer[4];

extern void power_init(void);
extern void ADCSample(void);
extern void BuckBoostVLoopCtlPID(void);

#ifdef __cplusplus
}
#endif

#endif /* __POWER_CTRL_H__ */

