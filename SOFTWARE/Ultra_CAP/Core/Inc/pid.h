#ifndef __PID_H
#define __PID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "struct_typedef.h"

enum PID_MODE
{
    PID_POSITION = 0, PID_DELTA = 1
};

typedef struct
{
//    uint8_t mode;   //PID模式，PID_POSITION位置式和PID_DELTA增量式
    //PID 三参数
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;   //最大输出
    fp32 min_out;   //最输出
    fp32 max_iout;  //最大积分输出
    fp32 min_iout;  //最小积分输出
    fp32 set;       //设定值
    fp32 fdb;

    fp32 out;
    fp32 pout;
    fp32 iout;
    fp32 dout;
    fp32 dbuf[2];
    fp32 error[2];  //误差项 0最新 1上一次 2上上次

} pid_type_def;


extern void PID_init(pid_type_def *pid, const fp32 p, const fp32 i, const fp32 d, fp32 max_out,
        fp32 max_iout, fp32 min_out, fp32 min_iout);
extern fp32 PID_calc(pid_type_def *pid, fp32 ref, fp32 set);
extern void PID_clear(pid_type_def *pid);

extern pid_type_def voltageout_loop;
extern pid_type_def currentout_loop;
extern pid_type_def powerin_loop;
extern pid_type_def powerbuf_loop;
extern pid_type_def power_referee_loop;

#ifdef __cplusplus
}
#endif

#endif
