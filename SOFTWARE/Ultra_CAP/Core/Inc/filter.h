#ifndef __filter_H__
#define	__filter_H__


#include "main.h"
#include "stdint.h"
//#include "stm32g4xx_hal.h"
//#include "core_cm4.h"

uint16_t getValue(void);

#define low_filter_default {0, 0, 0, 0, 0, 0}

typedef struct
{
	float  Input;
	float  Output;
	float  Fc;
	float  Fs;
	float  Ka;
	float  Kb;
	
}LOWPASS_FILTER_STRUCT;

#define PI2  2 * PI

extern LOWPASS_FILTER_STRUCT lpf[5];

extern void bubble_sort( uint16_t *a ,unsigned char Num);//ð�ݷ�����
extern uint16_t middle_filter(uint16_t *a ,unsigned char Num,char extremum);
extern fp32 recursive_filter(fp32 a);
extern void low_filter_calc(LOWPASS_FILTER_STRUCT *p);
extern void low_filter_init(LOWPASS_FILTER_STRUCT *p,float sample_f,float cutoff_f);


#endif
