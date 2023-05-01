#include "filter.h"

LOWPASS_FILTER_STRUCT lpf[5];

/*------一阶低通滤波------*/
void low_filter_init(LOWPASS_FILTER_STRUCT *p, float sample_f, float cutoff_f)
{
    float Tc; //时间常数τ
    p->Fc = cutoff_f;
    p->Fs = sample_f;
    if (p->Fc <= 0.0f || p->Fs <= 0.0f)
    {
        p->Ka = 1.0f;
        p->Kb = 0.0f;
        return;
    }

    Tc = 1.0f / (PI2 * p->Fc);

    p->Ka = 1.0f / (1.0f + Tc * p->Fs);
    p->Kb = 1.0f - p->Ka;
    p->Input = 0.0f;
    p->Output = 0.0f;
}

CCMRAM void low_filter_calc(LOWPASS_FILTER_STRUCT *p)
{
    if (p->Output == p->Input)
        return;

    p->Output = p->Ka * p->Input + p->Kb * p->Output;
}

/*冒泡排序*/
CCMRAM void bubble_sort(uint16_t *a, unsigned char Num) //冒泡法排序
{
    uint16_t *p = a;
    uint8_t i, j, tmp;
    for (i = 0; i < Num - 1; i++)
    {
        for (j = 0; j + i < Num - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}

/*递推平均滤波法*/
#define N 5

CCMRAM fp32 value_buf[N];
CCMRAM uint8_t i = 0;

CCMRAM fp32 recursive_filter(fp32 a)
{
    uint8_t count = 0;
    fp32 sum = 0;

    value_buf[i++] = a;
    if (i == N)
    {
        i = 0;    //先进先出
    }
    for (count = 0; count < N; count++)
    {
        sum += value_buf[count];
    }
    return (fp32) (sum / 5.0f);
}

/*中位平均滤波*/
CCMRAM uint16_t middle_filter(uint16_t *a, unsigned char Num, char extremum)
{
    uint8_t index = 0x00;
    uint32_t avg_sample = 0x00;
    bubble_sort(a, Num);
    // quick_sort(a,0,Num-1)  ;
    for (index = extremum; index < Num - extremum; index++)
    {
        avg_sample += a[index];
    }
    /* 计算N-X 个ADC 采样的均值 */
    avg_sample /= Num - 2 * extremum;
    /* 返回均值 */
    return (uint16_t) avg_sample;
}
