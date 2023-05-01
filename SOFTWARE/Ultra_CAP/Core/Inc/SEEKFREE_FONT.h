/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		字体文件
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 8.3 or MDK 5.26
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-10-10
 ********************************************************************************************************************/
#ifndef _SEEKFREE_FONT_h
#define _SEEKFREE_FONT_h

#include "stm32g4xx_hal.h"
#include "struct_typedef.h"

extern const uint8_t tft_ascii[95][16];
extern const uint8_t asc2_1608[1520];
extern const uint8_t chinese_test[8][16];



//-------常用颜色----------
#define RED    0xF800//红色
#define BLUE   0x001F//蓝色
#define YELLOW 0xFFE0//黄色
#define GREEN  0x07E0//绿色
#define WHITE  0xFFFF//白色
#define BLACK  0x0000//黑色 
#define GRAY   0X8430//灰色
#define BROWN  0XBC40//棕色
#define PURPLE 0XF81F//紫色
#define PINK   0XFE19//粉色


#endif
