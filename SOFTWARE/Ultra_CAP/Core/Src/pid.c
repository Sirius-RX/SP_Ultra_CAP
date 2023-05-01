#include "pid.h"

#define LimitMax(input, max) \
  {                          \
    if (input > max)         \
    {                        \
      input = max;           \
    }                        \
    else if (input < -max)   \
    {                        \
      input = -max;          \
    }                        \
  }

CCMRAM pid_type_def voltageout_loop;
CCMRAM pid_type_def currentout_loop;
CCMRAM pid_type_def powerin_loop;
CCMRAM pid_type_def powerbuf_loop;
CCMRAM pid_type_def power_referee_loop;

/**
 * @brief          pid struct data init
 * @param[out]     pid: PID struct data point
 * @param[in]      mode: PID_POSITION: normal pid
 * @param[in]      PID: 0: kp, 1: ki, 2:kd
 * @param[in]      max_out: pid max out
 * @param[in]      max_iout: pid max iout
 * @retval         none
 */
void PID_init(pid_type_def *pid, const fp32 p, const fp32 i, const fp32 d, fp32 max_out, fp32 max_iout, fp32 min_out,
        fp32 min_iout)
{
    if (pid == NULL || pid == NULL)
    {
        return;
    }
//    pid->mode = mode;
    pid->Kp = p;
    pid->Ki = i;
    pid->Kd = d;
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->min_out = min_out;
    pid->min_iout = min_iout;
    pid->dbuf[0] = pid->dbuf[1] = 0.0f;
    pid->error[0] = pid->error[1] = 0.0f;
    pid->pout = pid->iout = pid->dout = pid->out = 0.0f;
}

/**
 * @brief          pid calculate
 * @param[out]     pid: PID struct data point
 * @param[in]      ref: feedback data
 * @param[in]      set: set point
 * @retval         pid out
 */
#define N_filter 24000

CCMRAM fp32 PID_calc(pid_type_def *pid, fp32 ref, fp32 set)
{
    if (pid == NULL)
    {
        return 0.0f;
    }

    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;
    pid->pout = pid->Kp * pid->error[0];
    pid->iout += pid->Ki * pid->error[0];
    pid->dbuf[1] = pid->dbuf[0];
    pid->dbuf[0] = (pid->error[0] - pid->error[1]);
    pid->dout = pid->Kd * pid->dbuf[0];
    LimitMax(pid->iout, pid->max_iout);
    pid->out = pid->pout + pid->iout + pid->dout;

    if (pid->out > pid->max_out)
    {
        pid->out = pid->max_out;
    }
    else if (pid->out < pid->min_out)
    {
        pid->out = pid->min_out;
    }

    return pid->out;
}

/**
 * @brief          pid out clear
 * @param[out]     pid: PID struct data point
 * @retval         none
 */
CCMRAM void PID_clear(pid_type_def *pid)
{
    if (pid == NULL)
    {
        return;
    }

    pid->error[0] = pid->error[1] = 0.0f;
    pid->dbuf[0] = pid->dbuf[1] = 0.0f;
    pid->out = pid->pout = pid->iout = pid->dout = 0.0f;
    pid->fdb = pid->set = 0.0f;
}
