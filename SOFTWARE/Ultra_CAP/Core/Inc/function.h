#ifndef __FUNCTION_H
#define __FUNCTION_H	 

#include "main.h"

extern struct _Ctr_value CtrValue;
extern struct _FLAG DF;
extern uint16_t IPSShowCnt;
extern uint16_t CANSendCnt;

//函数声明
void StateM(void);
void StateMInit(void);
void StateMWait(void);
void StateMRise(void);
void StateMRun(void);
void StateMErr(void);
void ValInit(void);
void ShortOff(void);
void SwOCP(void);
void VoutSwOVP(void);
void VinSwUVP(void);
void VinSwOVP(void);
void LEDShow(void);
void KEYFlag(void);
void BBMode(void);
void DRMode(void);

/*****************************故障类型*****************/
#define     F_NOERR      		0x0000//无故障
#define     F_SW_VIN_UVP  		0x0001//输入欠压
#define     F_SW_VIN_OVP    	0x0002//输入过压
#define     F_SW_VOUT_UVP  		0x0004//输出欠压
#define     F_SW_VOUT_OVP    	0x0008//输出过压
#define     F_SW_IOUT_OCP    	0x0010//输出过流
#define     F_SW_SHORT  		0x0020//输出短路

#define MAX_BUCK_DUTY   (uint16_t)(0.95 * HRTIMB_Period)    //buck最大占空比95%
#define MIN_BUCK_DUTY	(uint16_t)(0.05 * HRTIMB_Period)    //buck最小占空比5%
#define	MAX_BUCK_DUTY1  (uint16_t)(0.75 * HRTIMB_Period)    //MIX state buck最大占空比80%
#define MAX_BOOST_DUTY  (uint16_t)(0.50 * HRTIMA_Period)    //boost最大占空比40%
#define MIN_BOOST_DUTY  (uint16_t)(0.05 * HRTIMA_Period)    //boost最小占空比5%
#define MIN_REG_VALUE   (uint16_t)100                       //HRTIM reg mini value

struct _Ctr_value
{
    fp32 Voref;             //参考电压
    fp32 Ioref;             //参考电流
    fp32 Poref;             //参考功率
    int16_t BuckMaxDuty;    //Buck最大占空比_cnt
    int16_t BoostMaxDuty;   //Boost最大占空比_cnt
    int16_t BuckMinDuty;    //Buck最小占空比_cnt
    int16_t BoostMinDuty;   //Boost最小占空比_cnt
    int16_t BuckDuty;       //Buck控制占空比_cnt
    int16_t BoostDuty;      //Boost控制占空比_cnt
};

//标志位定义
struct _FLAG
{
    uint16_t SMFlag;        //状态机标志位
    uint16_t CtrFlag;       //控制标志位
    uint16_t ErrFlag;       //故障标志位
    uint8_t BBFlag;         //运行模式标志位，Buck模式，MIX混合模式
    uint8_t DRFlag;         //current direction flag,charge,discharge
    uint8_t Cloop;          //loop control mode
    uint8_t PWMENFlag;      //启动标志位
    uint8_t KeyFlag1;       //按键标志位
    uint8_t BBModeChange;   //工作模式切换标志位
    uint8_t DRModeChange;   //current direction change flag
};

//状态机枚举量
typedef enum
{
    Init,   //初始化
    Wait,   //空闲等待
    Rise,   //软启
    Run,    //正常运行
    Err     //故障
} STATE_M;

//状态机枚举量
typedef enum
{
    NA0,    //undefine
    Buck,   //Buck mode
    Mix     //MIX mode
} BB_M;

//状态机枚举量
typedef enum
{
    NA1,        //undefine
    Charge,     //charge mode
    Discharge   //discharge mode
} DR_M;

//状态机枚举量
typedef enum
{
    current_loop,
    voltage_loop
} CL_M;

//软启动枚举变量
typedef enum
{
    SSInit, //soft start initl
    SSWait, //soft start waitting
    SSRun   //start soft start
} SState_M;

#define setRegBits(reg, mask)   (reg |= (unsigned int)(mask))
#define clrRegBits(reg, mask)  	(reg &= (unsigned int)(~(unsigned int)(mask)))
#define getRegBits(reg, mask)   (reg & (unsigned int)(mask))
#define getReg(reg)           	(reg)

#endif
