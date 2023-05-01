/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		SEEKFREE_IPS114_SPI.h
 * @brief      		IPS 液晶驱动
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-10-10
 * @note		
					IPS液晶接线定义：
					------------------------------------ 
						模块管脚            单片机管脚
						SCL                 查看SEEKFREE_IPS114_SPI.h文件内的IPS114_SCL		宏定义     硬件SPI引脚不可随意切换
						SDA                 查看SEEKFREE_IPS114_SPI.h文件内的IPS114_SDA		宏定义     硬件SPI引脚不可随意切换
						RES                 查看SEEKFREE_IPS114_SPI.h文件内的IPS114_REST_PIN宏定义    
						DC                  查看SEEKFREE_IPS114_SPI.h文件内的IPS114_DC_PIN	宏定义  
						CS                  查看SEEKFREE_IPS114_SPI.h文件内的IPS114_CS		宏定义     硬件SPI引脚不可随意切换
						BL  				查看SEEKFREE_IPS114_SPI.h文件内的IPS114_BL_PIN	宏定义 
						
						电源引脚
						VCC 3.3V电源
						GND 电源地
						最大分辨率135*240
					------------------------------------ 

 ********************************************************************************************************************/
 

#ifndef _SEEKFREE_IPS114_H
#define _SEEKFREE_IPS114_H

#include "main.h"
#include "SEEKFREE_FONT.h"


extern SPI_HandleTypeDef hspi2;
#define IPS114_DC(x)       HAL_GPIO_WritePin(IPS114_DC_GPIO_Port,IPS114_DC_Pin,(GPIO_PinState)x)
#define IPS114_REST(x)     HAL_GPIO_WritePin(IPS114_REST_GPIO_Port,IPS114_REST_Pin,(GPIO_PinState)x)
#define IPS114_CS(x)     HAL_GPIO_WritePin(IPS114_CS_GPIO_Port,IPS114_CS_Pin,(GPIO_PinState)x)




#define IPS114_W   135
#define IPS114_H   240



//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	0xF800	//红色
//#define BLUE         	0x001F  //蓝色
//#define YELLOW       	0xFFE0	//黄色
//#define GREEN        	0x07E0	//绿色
//#define WHITE        	0xFFFF	//白色
//#define BLACK        	0x0000	//黑色 
//#define GRAY  		0X8430 	//灰色
//#define BROWN 		0XBC40 	//棕色
//#define PURPLE    	0XF81F	//紫色
//#define PINK    		0XFE19	//粉色



//定义写字笔的颜色
#define IPS114_PENCOLOR    RED

//定义背景颜色
#define IPS114_BGCOLOR     WHITE



//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define IPS114_DISPLAY_DIR 3

#if (0==IPS114_DISPLAY_DIR || 1==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_W	//液晶X方宽度
#define IPS114_Y_MAX	IPS114_H   	//液晶Y方宽度
     
#elif (2==IPS114_DISPLAY_DIR || 3==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_H	//液晶X方宽度
#define IPS114_Y_MAX	IPS114_W   	//液晶Y方宽度
     
#else
#error "IPS114_DISPLAY_DIR 定义错误"
     
#endif

void ips_usrdisplay(void);
void ips114_init(void);
void ips114_clear(uint16_t color);
void ips114_drawpoint(uint16_t x,uint16_t y,uint16_t color);
void ips114_showchar(uint16_t x,uint16_t y,uint8_t dat);
void ips114_showstr(uint16_t x,uint16_t y,uint8_t dat[]);
void ips114_showint8(uint16_t x,uint16_t y,int8_t dat);
void ips114_showuint8(uint16_t x,uint16_t y,uint8_t dat);
void ips114_showint16(uint16_t x,uint16_t y,int16_t dat);
void ips114_showuint16(uint16_t x,uint16_t y,uint16_t dat);
void ips114_displayimage032(uint8_t *p, uint16_t width, uint16_t height);
void ips114_displayimage032_zoom(uint8_t *p, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height);
void ips114_displayimage7725(uint8_t *p, uint16_t width, uint16_t height);
void ips114_display_chinese(uint16_t x, uint16_t y, uint8_t size, const uint8_t *p, uint8_t number, uint16_t color);

#endif
