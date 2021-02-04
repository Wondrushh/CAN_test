/**
   @file Dragon_CANbus_filter.h
   @copyright TU Brno Racing
   @author Matus Kavec
   @author Tomas Lorenc
   @date 2019-2020
   @brief Setup for CAN ID filter and switched receive msg.
   @update 13.11.2020

*/

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef INC_DRAGON_CANBUS_FILTER_H_
#define INC_DRAGON_CANBUS_FILTER_H_

//#define __AMS_SLAVE__
//#define __AMS_MASTER__
//test
#include <stdint.h>
#include "Dragon_CANbus.h"

// @brief  Define used callback function for CANgen
//#define _CANgen_USED_CRIT_ERROR
//#define _CANgen_USED_START_BUTTON

//#define _CANgen_USED_
//#define _CANgen_USED_VCU_STATUS
//#define _CANgen_USED_ESP_STATUS
//#define _CANgen_USED_PEDAL_STATUS
//#define _CANgen_USED_AMS_STATUS
//#define _CANgen_USED_PEDAL_POSITION

//#define _CANgen_USED_NONCRIT_ERROR
//#define _CANcrit_USED_TS_ON
//#define _CANgen_USED_DISCHARGE
//#define _CANgen_USED_BRAKE_PRES

//#define _CANgen_USED_BATTERY_CURRENT
//#define _CANgen_USED_BATTERY_VOLTAGE
//#define _CANgen_USED_MAX_CELL_TEMP
//#define _CANgen_USED_AVG_CELL_TEMP
//#define _CANgen_USED_MIN_CELL_TEMP
//#define _CANgen_USED_LOWEST_CELL_VOLT
//#define _CANgen_USED_HV_MEAS_DATA

//#define _CANgen_USED_BATTERY_FAN_PERCENT
//#define _CANgen_USED_UNIX_TIME
//#define _CANgen_USED_ESP_LOG_TPP_BPP_STEER
//#define _CANgen_USED_ESP_LOG_YAWRATE_VINS
//#define _CANgen_USED_ESP_LOG_WHSPD_FRONT
//#define _CANgen_USED_ESP_LOG_WHSPD_REAR
//#define _CANgen_USED_ESP_LOG_VW_FRONT
//#define _CANgen_USED_ESP_LOG_VW_REAR
//#define _CANgen_USED_ESP_LOG_ESP_TRQ
//#define _CANgen_USED_ESP_LOG_TCS_TRQ
//#define _CANgen_USED_PEDAL_CALIBRATION
//#define _CANgen_USED_BATTERY_FAN_PERCENT

// @brief  Define used callback function for CANcrit
//#define _CANcrit_USED_RESET
//#define _CANcrit_USED_ESP_STATUS
//#define _CANcrit_USED_PEDAL_STATUS
//#define _CANcrit_USED_AMS_STATUS

//#define _CANcrit_USED_START_BUTTON

//#define _CANcrit_USED_PEDAL_POSITION
//#define _CANcrit_USED_BRAKE_PRES
//#define _CANcrit_USED_NONCRIT_ERROR
//#define _CANcrit_USED_TS_ON
//#define _CANcrit_USED_INVERTOR_INPUT_VOLTAGE

//#define _CANcrit_USED_BATTERY_CURRENT
//#define _CANcrit_USED_BATTERY_VOLTAGE
//#define _CANcrit_USED_MAX_CELL_TEMP
//#define _CANcrit_USED_AVG_CELL_TEMP
//#define _CANcrit_USED_MIN_CELL_TEMP
//#define _CANcrit_USED_LOWEST_CELL_VOLT

//#define _CANcrit_USED_PEDAL_CALIBRATION
//#define _CANcrit_USED_BATTERY_FAN_PERCENT
//#define _CANcrit_USED_UNIX_TIME
//#define _CANcrit_USED_ESP_LOG_TPP_BPP_STEER
//#define _CANcrit_USED_ESP_LOG_YAWRATE_VINS
//#define _CANcrit_USED_ESP_LOG_WHSPD_FRONT
//#define _CANcrit_USED_ESP_LOG_WHSPD_REAR
//#define _CANcrit_USED_ESP_LOG_VW_FRONT
//#define _CANcrit_USED_ESP_LOG_VW_REAR
//#define _CANcrit_USED_ESP_LOG_ESP_TRQ
//#define _CANcrit_USED_ESP_LOG_TCS_TRQ

// @brief  Define used callback function for CANams
#ifdef __AMS_SLAVE__
	#define _CANams_USED_REBOOT
	#define _CANams_USED_PING
	#define _CANams_USED_SET_FAN_PWM
	
	//#define _CANams_USED_SLAVE1_FAN_PWM
	//#define _CANams_USED_SLAVE1_DISCHARGE
	
	//#define _CANams_USED_SLAVE2_FAN_PWM
	//#define _CANams_USED_SLAVE2_DISCHARGE
	
	//#define _CANams_USED_SLAVE3_FAN_PWM
	//#define _CANams_USED_SLAVE3_DISCHARGE
	
	//#define _CANams_USED_SLAVE4_FAN_PWM
	//#define _CANams_USED_SLAVE4_DISCHARGE
	
	//#define _CANams_USED_SLAVE5_FAN_PWM
	//#define _CANams_USED_SLAVE5_DISCHARGE
	
	//#define _CANams_USED_SLAVE6_FAN_PWM
	//#define _CANams_USED_SLAVE6_DISCHARGE
#endif

#ifdef __AMS_MASTER__
	#define _CANams_USED_SLAVE1_ERROR
	#define _CANams_USED_SLAVE2_ERROR
	#define _CANams_USED_SLAVE3_ERROR
	#define _CANams_USED_SLAVE4_ERROR
	#define _CANams_USED_SLAVE5_ERROR
	#define _CANams_USED_SLAVE6_ERROR
	
	#define _CANams_USED_SLAVE1_PONG
	#define _CANams_USED_SLAVE2_PONG
	#define _CANams_USED_SLAVE3_PONG
	#define _CANams_USED_SLAVE4_PONG
	#define _CANams_USED_SLAVE5_PONG
	#define _CANams_USED_SLAVE6_PONG
	
	#define _CANams_USED_SLAVE1_TEMP0
	#define _CANams_USED_SLAVE1_TEMP1
	#define _CANams_USED_SLAVE1_TEMP2
	#define _CANams_USED_SLAVE1_VOLTAGE0
	#define _CANams_USED_SLAVE1_VOLTAGE1
	#define _CANams_USED_SLAVE1_VOLTAGE2
	#define _CANams_USED_SLAVE1_VOLTAGE3
	#define _CANams_USED_SLAVE1_VOLTAGE4
	
	#define _CANams_USED_SLAVE2_TEMP0
	#define _CANams_USED_SLAVE2_TEMP1
	#define _CANams_USED_SLAVE2_TEMP2
	#define _CANams_USED_SLAVE2_VOLTAGE0
	#define _CANams_USED_SLAVE2_VOLTAGE1
	#define _CANams_USED_SLAVE2_VOLTAGE2
	#define _CANams_USED_SLAVE2_VOLTAGE3
	#define _CANams_USED_SLAVE2_VOLTAGE4
	
	#define _CANams_USED_SLAVE3_TEMP0
	#define _CANams_USED_SLAVE3_TEMP1
	#define _CANams_USED_SLAVE3_TEMP2
	#define _CANams_USED_SLAVE3_VOLTAGE0
	#define _CANams_USED_SLAVE3_VOLTAGE1
	#define _CANams_USED_SLAVE3_VOLTAGE2
	#define _CANams_USED_SLAVE3_VOLTAGE3
	#define _CANams_USED_SLAVE3_VOLTAGE4
	
	#define _CANams_USED_SLAVE4_TEMP0
	#define _CANams_USED_SLAVE4_TEMP1
	#define _CANams_USED_SLAVE4_TEMP2
	#define _CANams_USED_SLAVE4_VOLTAGE0
	#define _CANams_USED_SLAVE4_VOLTAGE1
	#define _CANams_USED_SLAVE4_VOLTAGE2
	#define _CANams_USED_SLAVE4_VOLTAGE3
	#define _CANams_USED_SLAVE4_VOLTAGE4
	
	#define _CANams_USED_SLAVE5_TEMP0
	#define _CANams_USED_SLAVE5_TEMP1
	#define _CANams_USED_SLAVE5_TEMP2
	#define _CANams_USED_SLAVE5_VOLTAGE0
	#define _CANams_USED_SLAVE5_VOLTAGE1
	#define _CANams_USED_SLAVE5_VOLTAGE2
	#define _CANams_USED_SLAVE5_VOLTAGE3
	#define _CANams_USED_SLAVE5_VOLTAGE4
	
	#define _CANams_USED_SLAVE6_TEMP0
	#define _CANams_USED_SLAVE6_TEMP1
	#define _CANams_USED_SLAVE6_TEMP2
	#define _CANams_USED_SLAVE6_VOLTAGE0
	#define _CANams_USED_SLAVE6_VOLTAGE1
	#define _CANams_USED_SLAVE6_VOLTAGE2
	#define _CANams_USED_SLAVE6_VOLTAGE3
	#define _CANams_USED_SLAVE6_VOLTAGE4
	#define _CANams_USED_SLAVE6_FAN_PWM
	
	#define _CANams_USED_SLAVE1_BOARDTEMP
	#define _CANams_USED_SLAVE1_5V
	#define _CANams_USED_SLAVE1_3V3
	
	#define _CANams_USED_SLAVE2_BOARDTEMP
	#define _CANams_USED_SLAVE2_5V
	#define _CANams_USED_SLAVE2_3V3
	
	#define _CANams_USED_SLAVE3_BOARDTEMP
	#define _CANams_USED_SLAVE3_5V
	#define _CANams_USED_SLAVE3_3V3
	
	#define _CANams_USED_SLAVE4_BOARDTEMP
	#define _CANams_USED_SLAVE4_5V
	#define _CANams_USED_SLAVE4_3V3
	
	#define _CANams_USED_SLAVE5_BOARDTEMP
	#define _CANams_USED_SLAVE5_5V
	#define _CANams_USED_SLAVE5_3V3
	
	#define _CANams_USED_SLAVE6_BOARDTEMP
	#define _CANams_USED_SLAVE6_5V
	#define _CANams_USED_SLAVE6_3V3
#endif

/**
  @brief  Define structure TX message ID for CAN gen
  CANgen_ID_XXX
*/
typedef enum {
	CANgen_ID_Crit_error = 126u,
	CANgen_ID_Start_button = 128u,
	CANgen_ID_ = 200u,
	CANgen_ID_VCU_status = 201u,
	CANgen_ID_Esp_status = 202u,
	CANgen_ID_Pedal_status = 203u,
	CANgen_ID_Ams_status = 204u,
	CANgen_ID_Pedal_position = 205u,
	CANgen_ID_NonCrit_error = 400u,
	CANgen_ID_TS_on = 401u,
	CANgen_ID_Discharge = 500u,
	CANgen_ID_Brake_pres = 501u,
	CANgen_ID_Battery_current = 1050u,
	CANgen_ID_Battery_voltage = 1051u,
	CANgen_ID_Max_cell_temp = 1052u,
	CANgen_ID_Avg_cell_temp = 1053u,
	CANgen_ID_Min_cell_temp = 1054u,
	CANgen_ID_Lowest_cell_volt = 1055u,
	CANgen_ID_HV_meas_data = 1055u,
	CANgen_ID_Battery_fan_percent = 2030u,
	CANgen_ID_Unix_Time = 2031u,
	CANgen_ID_ESP_log_TPP_BPP_steer = 2032u,
	CANgen_ID_ESP_log_yawrate_vins = 2033u,
	CANgen_ID_ESP_log_whspd_front = 2034u,
	CANgen_ID_ESP_log_whspd_rear = 2035u,
	CANgen_ID_ESP_log_vw_front = 2036u,
	CANgen_ID_ESP_log_vw_rear = 2037u,
	CANgen_ID_ESP_log_esp_trq = 2038u,
	CANgen_ID_ESP_log_tcs_trq = 2039u,
	CANgen_ID_Pedal_Calibration = 2040u,
} CANdef_CANgen_ID;


/**
  @brief  Define structure TX message ID for CAN crit
  CANcrit_ID_XXX
*/
typedef enum {
  CANcrit_ID_Reset = 5u,
  CANcrit_ID_Esp_status = 124u,
  CANcrit_ID_Pedal_status = 125u,
  CANcrit_ID_Ams_status = 126u,
  CANcrit_ID_Start_button = 128u,
  CANcrit_ID_Pedal_position = 300u,
  CANcrit_ID_Brake_pres = 301u,
  CANcrit_ID_NonCrit_error = 400u,
  CANcrit_ID_TS_on = 401u,
  CANcrit_ID_Invertor_input_voltage = 500u,
  CANcrit_ID_Battery_current = 1050u,
  CANcrit_ID_Battery_voltage = 1051u,
  CANcrit_ID_Max_cell_temp = 1052u,
  CANcrit_ID_Avg_cell_temp = 1053u,
  CANcrit_ID_Min_cell_temp = 1054u,
  CANcrit_ID_Lowest_cell_volt = 1055u,
  CANcrit_ID_Pedal_Calibration = 2010u,
  CANcrit_ID_Battery_fan_percent = 2030u,
  CANcrit_ID_Unix_Time = 2031u,
  CANcrit_ID_ESP_log_TPP_BPP_steer = 2032u,
  CANcrit_ID_ESP_log_yawrate_vins = 2033u,
  CANcrit_ID_ESP_log_whspd_front = 2034u,
  CANcrit_ID_ESP_log_whspd_rear = 2035u,
  CANcrit_ID_ESP_log_vw_front = 2036u,
  CANcrit_ID_ESP_log_vw_rear = 2037u,
  CANcrit_ID_ESP_log_esp_trq = 2038u,
  CANcrit_ID_ESP_log_tcs_trq = 2039u
} CANdef_CANcrit_ID;

/**
  @brief  Define structure TX message ID for CAN ams
  CANams_ID_XXX
*/
typedef enum {
  CANams_ID_Reboot = 2u,
  CANams_ID_Ping = 3u,

  CANams_ID_Slave1_Error = 11u,
  CANams_ID_Slave2_Error = 12u,
  CANams_ID_Slave3_Error = 13u,
  CANams_ID_Slave4_Error = 14u,
  CANams_ID_Slave5_Error = 15u,
  CANams_ID_Slave6_Error = 16u,

  CANams_ID_Set_Fan_PWM = 19u,

  CANams_ID_Slave1_Pong = 21u,
  CANams_ID_Slave2_Pong = 22u,
  CANams_ID_Slave3_Pong = 23u,
  CANams_ID_Slave4_Pong = 24u,
  CANams_ID_Slave5_Pong = 25u,
  CANams_ID_Slave6_Pong = 26u,

  CANams_ID_Slave1_discharge = 31u,
  CANams_ID_Slave2_discharge = 32u,
  CANams_ID_Slave3_discharge = 33u,
  CANams_ID_Slave4_discharge = 34u,
  CANams_ID_Slave5_discharge = 35u,
  CANams_ID_Slave6_discharge = 36u,

  CANams_ID_Slave1_Temp0 = 110u,
  CANams_ID_Slave1_Temp1 = 111u,
  CANams_ID_Slave1_Temp2 = 112u,
  CANams_ID_Slave1_Voltage0 = 113u,
  CANams_ID_Slave1_Voltage1 = 114u,
  CANams_ID_Slave1_Voltage2 = 115u,
  CANams_ID_Slave1_Voltage3 = 116u,
  CANams_ID_Slave1_Voltage4 = 117u,
  CANams_ID_Slave1_Fan_PWM = 118u,

  CANams_ID_Slave2_Temp0 = 120u,
  CANams_ID_Slave2_Temp1 = 121u,
  CANams_ID_Slave2_Temp2 = 122u,
  CANams_ID_Slave2_Voltage0 = 123u,
  CANams_ID_Slave2_Voltage1 = 124u,
  CANams_ID_Slave2_Voltage2 = 125u,
  CANams_ID_Slave2_Voltage3 = 126u,
  CANams_ID_Slave2_Voltage4 = 127u,
  CANams_ID_Slave2_Fan_PWM = 128u,

  CANams_ID_Slave3_Temp0 = 130u,
  CANams_ID_Slave3_Temp1 = 131u,
  CANams_ID_Slave3_Temp2 = 132u,
  CANams_ID_Slave3_Voltage0 = 133u,
  CANams_ID_Slave3_Voltage1 = 134u,
  CANams_ID_Slave3_Voltage2 = 135u,
  CANams_ID_Slave3_Voltage3 = 136u,
  CANams_ID_Slave3_Voltage4 = 137u,
  CANams_ID_Slave3_Fan_PWM = 138u,

  CANams_ID_Slave4_Temp0 = 140u,
  CANams_ID_Slave4_Temp1 = 141u,
  CANams_ID_Slave4_Temp2 = 142u,
  CANams_ID_Slave4_Voltage0 = 143u,
  CANams_ID_Slave4_Voltage1 = 144u,
  CANams_ID_Slave4_Voltage2 = 145u,
  CANams_ID_Slave4_Voltage3 = 146u,
  CANams_ID_Slave4_Voltage4 = 147u,
  CANams_ID_Slave4_Fan_PWM = 148u,

  CANams_ID_Slave5_Temp0 = 150u,
  CANams_ID_Slave5_Temp1 = 151u,
  CANams_ID_Slave5_Temp2 = 152u,
  CANams_ID_Slave5_Voltage0 = 153u,
  CANams_ID_Slave5_Voltage1 = 154u,
  CANams_ID_Slave5_Voltage2 = 155u,
  CANams_ID_Slave5_Voltage3 = 156u,
  CANams_ID_Slave5_Voltage4 = 157u,
  CANams_ID_Slave5_Fan_PWM = 158u,

  CANams_ID_Slave6_Temp0 = 160u,
  CANams_ID_Slave6_Temp1 = 161u,
  CANams_ID_Slave6_Temp2 = 162u,
  CANams_ID_Slave6_Voltage0 = 163u,
  CANams_ID_Slave6_Voltage1 = 164u,
  CANams_ID_Slave6_Voltage2 = 165u,
  CANams_ID_Slave6_Voltage3 = 166u,
  CANams_ID_Slave6_Voltage4 = 167u,
  CANams_ID_Slave6_Fan_PWM = 168u,

  CANams_ID_Slave1_BoardTemp = 501u,
  CANams_ID_Slave1_5V = 502u,
  CANams_ID_Slave1_3V3 = 503u,

  CANams_ID_Slave2_BoardTemp = 505u,
  CANams_ID_Slave2_5V = 506u,
  CANams_ID_Slave2_3V3 = 507u,

  CANams_ID_Slave3_BoardTemp = 509u,
  CANams_ID_Slave3_5V = 510u,
  CANams_ID_Slave3_3V3 = 511u,

  CANams_ID_Slave4_BoardTemp = 513u,
  CANams_ID_Slave4_5V = 514u,
  CANams_ID_Slave4_3V3 = 515u,

  CANams_ID_Slave5_BoardTemp = 517u,
  CANams_ID_Slave5_5V = 518u,
  CANams_ID_Slave5_3V3 = 519u,

  CANams_ID_Slave6_BoardTemp = 521u,
  CANams_ID_Slave6_5V = 522u,
  CANams_ID_Slave6_3V3 = 523u
} CANdef_CANams_ID;

/**
  @brief Helper typedef for dragon_CANbus_RxFuncList
*/
typedef void (*__dragon_CANbus_FuncTypedef) (uint8_t aPayload[]);

/**
  @brief List of RX callback functions
  @info V budoucnu může být pole menší
*/
extern const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_gen[2047];
extern const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_crit[2047];
extern const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_ams[2047];

/**
  @brief define filter mask. (mask, ID, FIFO, ENABLE)
*/
extern const uint16_t _dragon_CANbus_filterList_VCU_gen[14][6];		//V1.1
extern const uint16_t _dragon_CANbus_filterList_PUMP_gen[14][6];	//V0.0
extern const uint16_t _dragon_CANbus_filterList_WHEEL_gen[14][6];	//V0.0
extern const uint16_t _dragon_CANbus_filterList_ESP_gen[14][6];		//V1.0
extern const uint16_t _dragon_CANbus_filterList_DATALOG_gen[14][6];	//V1.2
extern const uint16_t _dragon_CANbus_filterList_HV_gen[14][6];		//V1.0
extern const uint16_t _dragon_CANbus_filterList_VCU_crit[14][6];	//V1.4
extern const uint16_t _dragon_CANbus_filterList_ESP_crit[14][6];	//V1.3
extern const uint16_t _dragon_CANbus_filterList_PEDAL_crit[14][6];	//V1.0
extern const uint16_t _dragon_CANbus_filterList_AMSM_crit[14][6];	//V1.4
extern const uint16_t _dragon_CANbus_filterList_AMSS_ams[14][6];	//V2.2
extern const uint16_t _dragon_CANbus_filterList_AMSM_ams[14][6];	//V2.1

/**
  @brief Callback function for extended msg
*/
void _CANext_func_callback(uint8_t aPayload[], uint32_t IDmsg);

#endif /* INC_DRAGON_CANBUS_FILTER_H_ */
#ifdef __cplusplus /* __cplusplus */
}
#endif
