/**
 ****************************(C) COPYRIGHT 2019 DJI****************************
 * @file       can_receive.c/h
 * @brief      there is CAN interrupt function  to receive motor data,
 *             and CAN send function to send motor current to control motor.
 *             这里是CAN中断接收函数，接收电机数据,CAN发送函数发送电机电流控制电机.
 * @note
 * @history
 *  Version    Date            Author          Modification
 *  V1.0.0     Dec-26-2018     RM              1. done
 *
 @verbatim
 ==============================================================================

 ==============================================================================
 @endverbatim
 ****************************(C) COPYRIGHT 2019 DJI****************************
 */

#include "CAN_receive.h"
#include "function.h"
#include "power_ctrl.h"

//motor data read
#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        (ptr)->last_ecd = (ptr)->ecd;                                   \
        (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);            \
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);      \
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);  \
        (ptr)->temperate = (data)[6];                                   \
    }
/*
 motor data,  0:chassis motor1 3508;1:chassis motor3 3508;2:chassis motor3 3508;3:chassis motor4 3508;
 4:yaw gimbal motor 6020;5:pitch gimbal motor 6020;6:trigger motor 2006;
 电机数据, 0:底盘电机1 3508电机,  1:底盘电机2 3508电机,2:底盘电机3 3508电机,3:底盘电机4 3508电机;
 4:yaw云台电机 6020电机; 5:pitch云台电机 6020电机; 6:拨弹电机 2006电机*/
static motor_measure_t motor_chassis[7];

static FDCAN_TxHeaderTypeDef gimbal_tx_message;
static uint8_t gimbal_can_send_data[8];
static FDCAN_TxHeaderTypeDef chassis_tx_message;
static uint8_t chassis_can_send_data[8];

static FDCAN_TxHeaderTypeDef powerctrl_tx_message;
static uint8_t powerctrl_can_send_data[8];

/**
 * @brief          send C Board operation data(has to fixed)
 * @param[in]      none
 * @retval         none
 */
void CAN_cmd_powerctrl(void)
{
    int16_t capv;
    
    powerctrl_tx_message.Identifier = Chassis_C_Board_ID;
    powerctrl_tx_message.IdType = FDCAN_STANDARD_ID;
    powerctrl_tx_message.TxFrameType = FDCAN_DATA_FRAME;
    powerctrl_tx_message.DataLength = FDCAN_DLC_BYTES_8;
    powerctrl_tx_message.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
    powerctrl_tx_message.BitRateSwitch = FDCAN_BRS_OFF;
    powerctrl_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
    powerctrl_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    powerctrl_tx_message.MessageMarker = 0;
	
		capv = (int16_t)(cap.V * 100);
		powerctrl_can_send_data[0] = capv >> 8;
    powerctrl_can_send_data[1] = capv & 0x00FF;
		powerctrl_can_send_data[2] = DF.ErrFlag >> 8;
    powerctrl_can_send_data[3] = DF.ErrFlag & 0x00FF;
		powerctrl_can_send_data[4] = 0;
    powerctrl_can_send_data[5] = 0;
    powerctrl_can_send_data[6] = 0;
    powerctrl_can_send_data[7] = 0;

    HAL_FDCAN_AddMessageToTxFifoQ(&POWERCTRL_CAN, &powerctrl_tx_message, powerctrl_can_send_data);
}

/**
 * @brief          hal CAN fifo call back, receive referee signal
 * @param[in]      hcan, the point to CAN handle
 * @retval         none
 */
/**
 * @brief          hal库CAN回调函数,接收裁判系统数据
 * @param[in]      hcan:CAN句柄指针
 * @retval         none
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    uint16_t power_ref;
		uint16_t power_buffer;

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data);

		switch (rx_header.Identifier)
    {
    case 0x779:
		{
				memcpy(&power_ref, rx_data, sizeof(uint8_t) * 2);
				memcpy(&power_buffer, (rx_data + 2), sizeof(uint8_t) * 2);
			
//        if (power_buffer > 100)
//            CtrValue.Poref = 250.0f;  //飞坡状态  处于最大功率
//        else if (power_buffer < 60 && power_buffer > 30)
//            CtrValue.Poref = (fp32)(power_ref + 5);  //消耗缓冲能量
//        else
//            CtrValue.Poref = (fp32)(power_ref - 1);

        CtrValue.Poref = (fp32)(power_ref - 1);
			
//        CAN_cmd_powerctrl();
//        printf("power_ref=%d\r\n", power_ref);
        break;
		}
    default:
        break;
    }
}

/**
 * @brief          hal CAN fifo call back, receive motor data
 * @param[in]      hcan, the point to CAN handle
 * @retval         none
 */
/**
 * @brief          hal库CAN回调函数,接收电机数据
 * @param[in]      hcan:CAN句柄指针
 * @retval         none
 */
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rx_header, rx_data);

    switch (rx_header.Identifier)
    {
    case CAN_3508_M1_ID:
    case CAN_3508_M2_ID:
    case CAN_3508_M3_ID:
    case CAN_3508_M4_ID:
    case CAN_YAW_MOTOR_ID:
    case CAN_PIT_MOTOR_ID:
    case CAN_TRIGGER_MOTOR_ID:
    {
        static uint8_t i = 0;
        //get motor id
        i = rx_header.Identifier - CAN_3508_M1_ID;
        get_motor_measure(&motor_chassis[i], rx_data);
        break;
    }

    default:
    {
        break;
    }
    }
}

/**
 * @brief          send control current of motor (0x205, 0x206, 0x207, 0x208)
 * @param[in]      yaw: (0x205) 6020 motor control current, range [-30000,30000]
 * @param[in]      pitch: (0x206) 6020 motor control current, range [-30000,30000]
 * @param[in]      shoot: (0x207) 2006 motor control current, range [-10000,10000]
 * @param[in]      rev: (0x208) reserve motor control current
 * @retval         none
 */
/**
 * @brief          发送电机控制电流(0x205,0x206,0x207,0x208)
 * @param[in]      yaw: (0x205) 6020电机控制电流, 范围 [-30000,30000]
 * @param[in]      pitch: (0x206) 6020电机控制电流, 范围 [-30000,30000]
 * @param[in]      shoot: (0x207) 2006电机控制电流, 范围 [-10000,10000]
 * @param[in]      rev: (0x208) 保留，电机控制电流
 * @retval         none
 */
void CAN_cmd_gimbal(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev)
{
    gimbal_tx_message.Identifier = CAN_GIMBAL_ALL_ID;
    gimbal_tx_message.IdType = FDCAN_STANDARD_ID;
    gimbal_tx_message.TxFrameType = FDCAN_DATA_FRAME;
    gimbal_tx_message.DataLength = 0x08;
    gimbal_can_send_data[0] = (yaw >> 8);
    gimbal_can_send_data[1] = yaw;
    gimbal_can_send_data[2] = (pitch >> 8);
    gimbal_can_send_data[3] = pitch;
    gimbal_can_send_data[4] = (shoot >> 8);
    gimbal_can_send_data[5] = shoot;
    gimbal_can_send_data[6] = (rev >> 8);
    gimbal_can_send_data[7] = rev;
    HAL_FDCAN_AddMessageToTxFifoQ(&GIMBAL_CAN, &gimbal_tx_message, gimbal_can_send_data);
}

/**
 * @brief          send CAN packet of ID 0x700, it will set chassis motor 3508 to quick ID setting
 * @param[in]      none
 * @retval         none
 */
/**
 * @brief          发送ID为0x700的CAN包,它会设置3508电机进入快速设置ID
 * @param[in]      none
 * @retval         none
 */
void CAN_cmd_chassis_reset_ID(void)
{
    chassis_tx_message.Identifier = 0x700;
    chassis_tx_message.IdType = FDCAN_STANDARD_ID;
    chassis_tx_message.TxFrameType = FDCAN_DATA_FRAME;
    chassis_tx_message.DataLength = 0x08;
    chassis_can_send_data[0] = 0;
    chassis_can_send_data[1] = 0;
    chassis_can_send_data[2] = 0;
    chassis_can_send_data[3] = 0;
    chassis_can_send_data[4] = 0;
    chassis_can_send_data[5] = 0;
    chassis_can_send_data[6] = 0;
    chassis_can_send_data[7] = 0;

    HAL_FDCAN_AddMessageToTxFifoQ(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data);
}

/**
 * @brief          send control current of motor (0x201, 0x202, 0x203, 0x204)
 * @param[in]      motor1: (0x201) 3508 motor control current, range [-16384,16384]
 * @param[in]      motor2: (0x202) 3508 motor control current, range [-16384,16384]
 * @param[in]      motor3: (0x203) 3508 motor control current, range [-16384,16384]
 * @param[in]      motor4: (0x204) 3508 motor control current, range [-16384,16384]
 * @retval         none
 */
/**
 * @brief          发送电机控制电流(0x201,0x202,0x203,0x204)
 * @param[in]      motor1: (0x201) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor2: (0x202) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor3: (0x203) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor4: (0x204) 3508电机控制电流, 范围 [-16384,16384]
 * @retval         none
 */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
    chassis_tx_message.Identifier = CAN_CHASSIS_ALL_ID;
    chassis_tx_message.IdType = FDCAN_STANDARD_ID;
    chassis_tx_message.TxFrameType = FDCAN_DATA_FRAME;
    chassis_tx_message.DataLength = 0x08;
    chassis_can_send_data[0] = motor1 >> 8;
    chassis_can_send_data[1] = motor1;
    chassis_can_send_data[2] = motor2 >> 8;
    chassis_can_send_data[3] = motor2;
    chassis_can_send_data[4] = motor3 >> 8;
    chassis_can_send_data[5] = motor3;
    chassis_can_send_data[6] = motor4 >> 8;
    chassis_can_send_data[7] = motor4;

    HAL_FDCAN_AddMessageToTxFifoQ(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data);
}

/**
 * @brief          return the yaw 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回yaw 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_yaw_gimbal_motor_measure_point(void)
{
    return &motor_chassis[4];
}

/**
 * @brief          return the pitch 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回pitch 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_pitch_gimbal_motor_measure_point(void)
{
    return &motor_chassis[5];
}

/**
 * @brief          return the trigger 2006 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回拨弹电机 2006电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_trigger_motor_measure_point(void)
{
    return &motor_chassis[6];
}

/**
 * @brief          return the chassis 3508 motor data point
 * @param[in]      i: motor number,range [0,3]
 * @retval         motor data point
 */
/**
 * @brief          返回底盘电机 3508电机数据指针
 * @param[in]      i: 电机编号,范围[0,3]
 * @retval         电机数据指针
 */
const motor_measure_t *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];
}
