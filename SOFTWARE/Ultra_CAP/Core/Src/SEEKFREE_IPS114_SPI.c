/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		SEEKFREE_IPS114_SPI.c
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

 电源引脚
 VCC 3.3V电源
 GND 电源地
 最大分辨率135*240
 ------------------------------------

 ********************************************************************************************************************/

#include "SEEKFREE_IPS114_SPI.h"
#include "power_ctrl.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      IPS显示程序，用以方便交互&Debug
//  @param      void
//  @return
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
CCMRAM void ips_usrdisplay(void)
//void ips_usrdisplay(void)
{
//    ips114_showstr(0, 1, (uint8_t *) "c_in=");
    ips114_showint16(150, 0, (int16_t) (in.P * 100));
    ips114_showint16(60, 1, (int16_t) (in.I * 1000));
//    ips114_showstr(120, 1, (uint8_t *) "c_cap=");
    ips114_showint16(180, 1, (int16_t) (cap.I * 1000));
//    ips114_showstr(0, 3, (uint8_t *) "c_chassis=");
    ips114_showint16(120, 3, (int16_t) (chassis.I * 1000));
//    ips114_showstr(0, 5, (uint8_t *) "v_in=");
    ips114_showint16(60, 5, (int16_t) (in.V * 1000));
//    ips114_showstr(120, 5, (uint8_t *) "v_cap=");
    ips114_showint16(180, 5, (int16_t) (cap.V * 1000));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips114_writeIndex(uint8_t dat)			//写命令
{
    IPS114_CS(0);
    IPS114_DC(0);
    HAL_SPI_Transmit(&hspi2, &dat, 1, 500);
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips114_writeData(uint8_t dat)			//写数据
{
    IPS114_CS(0);
    IPS114_DC(1);
    HAL_SPI_Transmit(&hspi2, &dat, 1, 500);
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips114_writedata_16bit(uint16_t dat)	//向液晶屏写一个16位数据
{
    uint8_t h, l;
    h = dat >> 8;
    l = (uint8_t) dat;
    IPS114_CS(0);
    IPS114_DC(1);
    HAL_SPI_Transmit(&hspi2, &h, 1, 500);
    HAL_SPI_Transmit(&hspi2, &l, 1, 500);
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      1.14寸 IPS液晶初始化
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips114_init(void)
{

    IPS114_CS(1);
    HAL_GPIO_WritePin(IPS114_BL_GPIO_Port, IPS114_BL_Pin, (GPIO_PinState) 1);

    IPS114_REST(0);
    HAL_Delay(200);

    IPS114_REST(1);
    HAL_Delay(100);

    ips114_writeIndex(0x36);

    if (IPS114_DISPLAY_DIR == 0)
        ips114_writeData(0x00);
    else if (IPS114_DISPLAY_DIR == 1)
        ips114_writeData(0xC0);
    else if (IPS114_DISPLAY_DIR == 2)
        ips114_writeData(0x70);
    else
        ips114_writeData(0xA0);

    ips114_writeIndex(0x3A);
    ips114_writeData(0x05);

    ips114_writeIndex(0xB2);
    ips114_writeData(0x0C);
    ips114_writeData(0x0C);
    ips114_writeData(0x00);
    ips114_writeData(0x33);
    ips114_writeData(0x33);

    ips114_writeIndex(0xB7);
    ips114_writeData(0x35);

    ips114_writeIndex(0xBB);
    ips114_writeData(0x37);

    ips114_writeIndex(0xC0);
    ips114_writeData(0x2C);

    ips114_writeIndex(0xC2);
    ips114_writeData(0x01);

    ips114_writeIndex(0xC3);
    ips114_writeData(0x12);

    ips114_writeIndex(0xC4);
    ips114_writeData(0x20);

    ips114_writeIndex(0xC6);
    ips114_writeData(0x0F);

    ips114_writeIndex(0xD0);
    ips114_writeData(0xA4);
    ips114_writeData(0xA1);

    ips114_writeIndex(0xE0);
    ips114_writeData(0xD0);
    ips114_writeData(0x04);
    ips114_writeData(0x0D);
    ips114_writeData(0x11);
    ips114_writeData(0x13);
    ips114_writeData(0x2B);
    ips114_writeData(0x3F);
    ips114_writeData(0x54);
    ips114_writeData(0x4C);
    ips114_writeData(0x18);
    ips114_writeData(0x0D);
    ips114_writeData(0x0B);
    ips114_writeData(0x1F);
    ips114_writeData(0x23);

    ips114_writeIndex(0xE1);
    ips114_writeData(0xD0);
    ips114_writeData(0x04);
    ips114_writeData(0x0C);
    ips114_writeData(0x11);
    ips114_writeData(0x13);
    ips114_writeData(0x2C);
    ips114_writeData(0x3F);
    ips114_writeData(0x44);
    ips114_writeData(0x51);
    ips114_writeData(0x2F);
    ips114_writeData(0x1F);
    ips114_writeData(0x1F);
    ips114_writeData(0x20);
    ips114_writeData(0x23);

    ips114_writeIndex(0x21);

    ips114_writeIndex(0x11);
    HAL_Delay(120);

    ips114_writeIndex(0x29);
    ips114_clear(IPS114_BGCOLOR);

    /*显示固定字符串，减少系统资源占用*/
    ips114_showstr(0, 0, (uint8_t *) "SiriusP");
    ips114_display_chinese(0, 7 * 16, 16, chinese_test[0], 4, BLUE);
    ips114_showstr(80, 0, (uint8_t *) "powerin=");
    ips114_showstr(0, 1, (uint8_t *) "c_in=");
    ips114_showstr(120, 1, (uint8_t *) "c_cap=");
    ips114_showstr(0, 3, (uint8_t *) "c_chassis=");
    ips114_showstr(0, 5, (uint8_t *) "v_in=");
    ips114_showstr(120, 5, (uint8_t *) "v_cap=");
    ips114_showstr(120, 7, (uint8_t *) "loop_state=");
}

void ips114_set_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (IPS114_DISPLAY_DIR == 0)
    {
        ips114_writeIndex(0x2a);	//列地址设置
        ips114_writedata_16bit(x1 + 52);
        ips114_writedata_16bit(x2 + 52);
        ips114_writeIndex(0x2b);	//行地址设置
        ips114_writedata_16bit(y1 + 40);
        ips114_writedata_16bit(y2 + 40);
        ips114_writeIndex(0x2c);	//储存器写
    }
    else if (IPS114_DISPLAY_DIR == 1)
    {
        ips114_writeIndex(0x2a);	//列地址设置
        ips114_writedata_16bit(x1 + 53);
        ips114_writedata_16bit(x2 + 53);
        ips114_writeIndex(0x2b);	//行地址设置
        ips114_writedata_16bit(y1 + 40);
        ips114_writedata_16bit(y2 + 40);
        ips114_writeIndex(0x2c);	//储存器写
    }
    else if (IPS114_DISPLAY_DIR == 2)
    {
        ips114_writeIndex(0x2a);	//列地址设置
        ips114_writedata_16bit(x1 + 40);
        ips114_writedata_16bit(x2 + 40);
        ips114_writeIndex(0x2b);	//行地址设置
        ips114_writedata_16bit(y1 + 53);
        ips114_writedata_16bit(y2 + 53);
        ips114_writeIndex(0x2c);	//储存器写
    }
    else
    {
        ips114_writeIndex(0x2a);	//列地址设置
        ips114_writedata_16bit(x1 + 40);
        ips114_writedata_16bit(x2 + 40);
        ips114_writeIndex(0x2b);	//行地址设置
        ips114_writedata_16bit(y1 + 52);
        ips114_writedata_16bit(y2 + 52);
        ips114_writeIndex(0x2c);	//储存器写
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_clear(IPS114_YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void ips114_clear(uint16_t color)
{
    uint16_t i, j;
    ips114_set_region(0, 0, IPS114_X_MAX - 1, IPS114_Y_MAX - 1);
    for (i = 0; i < IPS114_X_MAX; i++)
    {
        for (j = 0; j < IPS114_Y_MAX; j++)
        {
            ips114_writedata_16bit(color);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_drawpoint(0,0,IPS114_RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void ips114_drawpoint(uint16_t x, uint16_t y, uint16_t color)
{
    ips114_set_region(x, y, x, y);
    ips114_writedata_16bit(color);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS114_Y_MAX-1）
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void ips114_showchar(uint16_t x, uint16_t y, uint8_t dat)
{
    uint8_t i, j;
    uint8_t temp;

    for (i = 0; i < 16; i++)
    {
        ips114_set_region(x, y + i, x + 7, y + i);
        temp = tft_ascii[dat - 32][i];	//减32因为是取模是从空格开始取得 空格在ascii中序号是32
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x01)
            {
                ips114_writedata_16bit(IPS114_PENCOLOR);
            }
            else
                ips114_writedata_16bit(IPS114_BGCOLOR);
            temp >>= 1;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符串
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void ips114_showstr(uint16_t x, uint16_t y, uint8_t dat[])
{
    uint16_t j;

    j = 0;
    while (dat[j] != '\0')
    {
        ips114_showchar(x + 8 * j, y * 16, dat[j]);
        j++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8_t
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showint8(0,0,x);//x为int8_t类型
//-------------------------------------------------------------------------------------------------------------------
void ips114_showint8(uint16_t x, uint16_t y, int8_t dat)
{
    uint8_t a[3];
    uint8_t i;
    if (dat < 0)
    {
        ips114_showchar(x, y * 16, '-');
        dat = -dat;
    }
    else
        ips114_showchar(x, y * 16, ' ');

    a[0] = dat / 100;
    a[1] = dat / 10 % 10;
    a[2] = dat % 10;
    i = 0;
    while (i < 3)
    {
        ips114_showchar(x + (8 * (i + 1)), y * 16, '0' + a[i]);
        i++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8_t
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showuint8(0,0,x);//x为uint8_t类型
//-------------------------------------------------------------------------------------------------------------------
void ips114_showuint8(uint16_t x, uint16_t y, uint8_t dat)
{
    uint8_t a[3];
    uint8_t i;

    a[0] = dat / 100;
    a[1] = dat / 10 % 10;
    a[2] = dat % 10;
    i = 0;
    while (i < 3)
    {
        ips114_showchar(x + (8 * i), y * 16, '0' + a[i]);
        i++;
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16_t
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showint16(0,0,x);//x为int16_t类型
//-------------------------------------------------------------------------------------------------------------------
void ips114_showint16(uint16_t x, uint16_t y, int16_t dat)
{
    uint8_t a[5];
    uint8_t i;
    if (dat < 0)
    {
        ips114_showchar(x, y * 16, '-');
        dat = -dat;
    }
    else
        ips114_showchar(x, y * 16, ' ');

    a[0] = dat / 10000;
    a[1] = dat / 1000 % 10;
    a[2] = dat / 100 % 10;
    a[3] = dat / 10 % 10;
    a[4] = dat % 10;

    i = 0;
    while (i < 5)
    {
        ips114_showchar(x + (8 * (i + 1)), y * 16, '0' + a[i]);
        i++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS114_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS114_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16_t
//  @return     void
//  @since      v1.0
//  Sample usage:               ips114_showuint16(0,0,x);//x为uint16_t类型
//-------------------------------------------------------------------------------------------------------------------
void ips114_showuint16(uint16_t x, uint16_t y, uint16_t dat)
{
    uint8_t a[5];
    uint8_t i;

    a[0] = dat / 10000;
    a[1] = dat / 1000 % 10;
    a[2] = dat / 100 % 10;
    a[3] = dat / 10 % 10;
    a[4] = dat % 10;

    i = 0;
    while (i < 5)
    {
        ips114_showchar(x + (8 * i), y * 16, '0' + a[i]);
        i++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      汉字显示
//  @param      x       横坐标 0-（IPS114_X_MAX-1）
//  @param      y       纵坐标 0-（IPS114_Y_MAX-1）
//  @param      size    取模的时候设置的汉字字体大小，也就是一个汉字占用的点阵长宽为多少个点，取模的时候需要长宽是一样的。
//  @param      *p      需要显示的汉字数组
//  @param      number  需要显示多少位
//  @param      color   显示颜色
//  @return     void
//  @since      v1.0
//  Sample usage:		ips114_display_chinese(0,0,16,chinese_test[0],4,RED);//显示font文件里面的 示例
//  @Note       使用PCtoLCD2002软件取模		    阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void ips114_display_chinese(uint16_t x, uint16_t y, uint8_t size, const uint8_t *p, uint8_t number, uint16_t color)
{
    int i, j, k;
    uint8_t temp, temp1, temp2;
    const uint8_t *p_data;

    temp2 = size / 8;

    ips114_set_region(x, y, number * size - 1 + x, y + size - 1);

    for (i = 0; i < size; i++)
    {
        temp1 = number;
        p_data = p + i * temp2;
        while (temp1--)
        {
            for (k = 0; k < temp2; k++)
            {
                for (j = 8; j > 0; j--)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if (temp)
                        ips114_writedata_16bit(color);
                    else
                        ips114_writedata_16bit(IPS114_BGCOLOR);
                }
                p_data++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }
    }
}

