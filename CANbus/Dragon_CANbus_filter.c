/**
   @file Dragon_CANbus_filter.c
   @copyright TU Brno Racing
   @author Matus Kavec
   @author Tomas Lorenc
   @date 2019-2020
   @brief Setup for CAN ID filter and switched receive msg.
   @update 13.11.2020

*/

#include "Dragon_CANbus_filter.h"

#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */

#ifdef __AMS_SLAVE__
    #include "stm32f1xx_hal.h"
    #define _CAN1def_ONLY_INTERRUPT_MODE
    #define __CAN1_CANamsBus    //CAN_ams
    #define __CAN1_FILTERLIST  _dragon_CANbus_filterList_AMSS_ams
#endif

#ifdef __AMS_MASTER__
    #include "stm32f4xx_hal.h"
        #define _DUAL_CAN_ACTIVATE
    #define _CAN1def_ONLY_INTERRUPT_MODE
    #define _CAN2def_ONLY_INTERRUPT_MODE
    #define __CAN1_CANcritBus    //CAN_crit
    #define __CAN1_FILTERLIST  _dragon_CANbus_filterList_AMSM_crit
    #define __CAN2_CANamsBus    //CAN_ams
    #define __CAN2_FILTERLIST  _dragon_CANbus_filterList_AMSM_ams
    #define __EXTENDED_CAN_ACTIVATE
#endif

/**
  @brief define RX callback functions
*/
/***********CAN_GEN***************************************/
__weak void CANgen_func_Crit_error(uint8_t aPayload[]);
__weak void CANgen_func_Start_button(uint8_t aPayload[]);
__weak void CANgen_func_(uint8_t aPayload[]);
__weak void CANgen_func_VCU_status(uint8_t aPayload[]);
__weak void CANgen_func_Esp_status(uint8_t aPayload[]);
__weak void CANgen_func_Pedal_status(uint8_t aPayload[]);
__weak void CANgen_func_Ams_status(uint8_t aPayload[]);
__weak void CANgen_func_Pedal_position(uint8_t aPayload[]);

__weak void CANgen_func_NonCrit_error(uint8_t aPayload[]);
__weak void CANcrit_func_TS_on(uint8_t aPayload[]);
__weak void CANgen_func_Discharge(uint8_t aPayload[]);
__weak void CANgen_func_Brake_pres(uint8_t aPayload[]);

__weak void CANgen_func_Battery_current(uint8_t aPayload[]);
__weak void CANgen_func_Battery_voltage(uint8_t aPayload[]);
__weak void CANgen_func_Max_cell_temp(uint8_t aPayload[]);
__weak void CANgen_func_Avg_cell_temp(uint8_t aPayload[]);
__weak void CANgen_func_Min_cell_temp(uint8_t aPayload[]);
__weak void CANgen_func_Lowest_cell_volt(uint8_t aPayload[]);
__weak void CANgen_func_HV_meas_data(uint8_t aPayload[]);

__weak void CANgen_func_Battery_fan_percent(uint8_t aPayload[]);
__weak void CANgen_func_Unix_Time(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_TPP_BPP_steer(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_yawrate_vins(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_whspd_front(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_whspd_rear(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_vw_front(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_vw_rear(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_esp_trq(uint8_t aPayload[]);
__weak void CANgen_func_ESP_log_tcs_trq(uint8_t aPayload[]);
__weak void CANgen_func_Pedal_Calibration(uint8_t aPayload[]);
__weak void CANgen_func_Battery_fan_percent(uint8_t aPayload[]);

/***********CAN_CRIT**************************************/
__weak void CANcrit_func_Reset(uint8_t aPayload[]);
__weak void CANcrit_func_Esp_status(uint8_t aPayload[]);
__weak void CANcrit_func_Pedal_status(uint8_t aPayload[]);
__weak void CANcrit_func_Ams_status(uint8_t aPayload[]);
__weak void CANcrit_func_Start_button(uint8_t aPayload[]);

__weak void CANcrit_func_Pedal_position(uint8_t aPayload[]);
__weak void CANcrit_func_Brake_pres(uint8_t aPayload[]);
__weak void CANcrit_func_NonCrit_error(uint8_t aPayload[]);
__weak void CANcrit_func_TS_on(uint8_t aPayload[]);
__weak void CANcrit_func_Invertor_input_voltage(uint8_t aPayload[]);

__weak void CANcrit_func_Battery_current(uint8_t aPayload[]);
__weak void CANcrit_func_Battery_voltage(uint8_t aPayload[]);
__weak void CANcrit_func_Max_cell_temp(uint8_t aPayload[]);
__weak void CANcrit_func_Avg_cell_temp(uint8_t aPayload[]);
__weak void CANcrit_func_Min_cell_temp(uint8_t aPayload[]);
__weak void CANcrit_func_Lowest_cell_volt(uint8_t aPayload[]);

__weak void CANcrit_func_Pedal_Calibration(uint8_t aPayload[]);
__weak void CANcrit_func_Battery_fan_percent(uint8_t aPayload[]);
__weak void CANcrit_func_Unix_Time(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_TPP_BPP_steer(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_yawrate_vins(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_whspd_front(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_whspd_rear(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_vw_front(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_vw_rear(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_esp_trq(uint8_t aPayload[]);
__weak void CANcrit_func_ESP_log_tcs_trq(uint8_t aPayload[]);

/***********CAN_AMS***************************************/
__weak void CANams_func_Reboot(uint8_t aPayload[]);
__weak void CANams_func_Ping(uint8_t aPayload[]);

__weak void CANams_func_Slave1_Error(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Error(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Error(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Error(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Error(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Error(uint8_t aPayload[]);

__weak void CANams_func_Set_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave1_Pong(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Pong(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Pong(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Pong(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Pong(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Pong(uint8_t aPayload[]);

__weak void CANams_func_Slave1_discharge(uint8_t aPayload[]);
__weak void CANams_func_Slave2_discharge(uint8_t aPayload[]);
__weak void CANams_func_Slave3_discharge(uint8_t aPayload[]);
__weak void CANams_func_Slave4_discharge(uint8_t aPayload[]);
__weak void CANams_func_Slave5_discharge(uint8_t aPayload[]);
__weak void CANams_func_Slave6_discharge(uint8_t aPayload[]);

__weak void CANams_func_Slave1_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave1_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave2_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave2_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave3_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave3_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave4_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave4_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave5_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave5_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave6_Temp0(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Temp1(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Temp2(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Voltage0(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Voltage1(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Voltage2(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Voltage3(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Voltage4(uint8_t aPayload[]);
__weak void CANams_func_Slave6_Fan_PWM(uint8_t aPayload[]);

__weak void CANams_func_Slave1_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave1_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave1_3V3(uint8_t aPayload[]);

__weak void CANams_func_Slave2_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave2_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave2_3V3(uint8_t aPayload[]);

__weak void CANams_func_Slave3_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave3_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave3_3V3(uint8_t aPayload[]);

__weak void CANams_func_Slave4_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave4_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave4_3V3(uint8_t aPayload[]);

__weak void CANams_func_Slave5_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave5_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave5_3V3(uint8_t aPayload[]);

__weak void CANams_func_Slave6_BoardTemp(uint8_t aPayload[]);
__weak void CANams_func_Slave6_5V(uint8_t aPayload[]);
__weak void CANams_func_Slave6_3V3(uint8_t aPayload[]);

/**
  @brief List of RX callback functions for CANgen


*/
const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_gen[2047] = {
    #ifdef _CANgen_USED_CRIT_ERROR
      [126] &CANgen_func_Crit_error,
    #endif
    #ifdef _CANgen_USED_START_BUTTON
      [128] &CANgen_func_Start_button,
    #endif
    #ifdef _CANgen_USED_
      [200] &CANgen_func_,
    #endif
    #ifdef _CANgen_USED_VCU_STATUS
      [201] &CANgen_func_VCU_status,
    #endif
    #ifdef _CANgen_USED_ESP_STATUS
      [202] &CANgen_func_Esp_status,
    #endif
    #ifdef _CANgen_USED_PEDAL_STATUS
      [203] &CANgen_func_Pedal_status,
    #endif
    #ifdef _CANgen_USED_AMS_STATUS
      [204] &CANgen_func_Ams_status,
    #endif
    #ifdef _CANgen_USED_PEDAL_POSITION
      [205] &CANgen_func_Pedal_position,
    #endif
    #ifdef _CANgen_USED_NONCRIT_ERROR
      [400] &CANgen_func_NonCrit_error,
    #endif
    #ifdef _CANcrit_USED_TS_ON
      [401] &CANcrit_func_TS_on,
    #endif
    #ifdef _CANgen_USED_DISCHARGE
      [500] &CANgen_func_Discharge,
    #endif
    #ifdef _CANgen_USED_BRAKE_PRES
      [501] &CANgen_func_Brake_pres,
    #endif
    #ifdef _CANgen_USED_BATTERY_CURRENT
      [1050] &CANgen_func_Battery_current,
    #endif
    #ifdef _CANgen_USED_BATTERY_VOLTAGE
      [1051] &CANgen_func_Battery_voltage,
    #endif
    #ifdef _CANgen_USED_MAX_CELL_TEMP
      [1052] &CANgen_func_Max_cell_temp,
    #endif
    #ifdef _CANgen_USED_AVG_CELL_TEMP
      [1053] &CANgen_func_Avg_cell_temp,
    #endif
    #ifdef _CANgen_USED_MIN_CELL_TEMP
      [1054] &CANgen_func_Min_cell_temp,
    #endif
    #ifdef _CANgen_USED_LOWEST_CELL_VOLT
      [1055] &CANgen_func_Lowest_cell_volt,
    #endif
    #ifdef _CANgen_USED_HV_MEAS_DATA
      [1055] &CANgen_func_HV_meas_data,
    #endif
    #ifdef _CANgen_USED_BATTERY_FAN_PERCENT
      [2030] &CANgen_func_Battery_fan_percent,
    #endif
    #ifdef _CANgen_USED_UNIX_TIME
      [2031] &CANgen_func_Unix_Time,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_TPP_BPP_STEER
      [2032] &CANgen_func_ESP_log_TPP_BPP_steer,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_YAWRATE_VINS
      [2033] &CANgen_func_ESP_log_yawrate_vins,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_WHSPD_FRONT
      [2034] &CANgen_func_ESP_log_whspd_front,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_WHSPD_REAR
      [2035] &CANgen_func_ESP_log_whspd_rear,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_VW_FRONT
      [2036] &CANgen_func_ESP_log_vw_front,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_VW_REAR
      [2037] &CANgen_func_ESP_log_vw_rear,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_ESP_TRQ
      [2038] &CANgen_func_ESP_log_esp_trq,
    #endif
    #ifdef _CANgen_USED_ESP_LOG_TCS_TRQ
      [2039] &CANgen_func_ESP_log_tcs_trq,
    #endif
    #ifdef _CANgen_USED_PEDAL_CALIBRATION
      [2040] &CANgen_func_Pedal_Calibration,
    #endif
    #ifdef _CANgen_USED_BATTERY_FAN_PERCENT
      [2041] &CANgen_func_Battery_fan_percent,
    #endif
};

/**
  @brief List of RX callback functions for CANcrit


*/
const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_crit[2047] = {
  #ifdef _CANcrit_USED_RESET
    [5] &CANcrit_func_Reset,
  #endif
  #ifdef _CANcrit_USED_ESP_STATUS
    [124] &CANcrit_func_Esp_status,
  #endif
  #ifdef _CANcrit_USED_PEDAL_STATUS
    [125] &CANcrit_func_Pedal_status,
  #endif
  #ifdef _CANcrit_USED_AMS_STATUS
    [126] &CANcrit_func_Ams_status,
  #endif
  #ifdef _CANcrit_USED_START_BUTTON
    [128] &CANcrit_func_Start_button,
  #endif
  #ifdef _CANcrit_USED_PEDAL_POSITION
    [300] &CANcrit_func_Pedal_position,
  #endif
  #ifdef _CANcrit_USED_BRAKE_PRES
    [301] &CANcrit_func_Brake_pres,
  #endif
  #ifdef _CANcrit_USED_NONCRIT_ERROR
    [400] &CANcrit_func_NonCrit_error,
  #endif
  #ifdef _CANcrit_USED_TS_ON
    [401] &CANcrit_func_TS_on,
  #endif
  #ifdef _CANcrit_USED_INVERTOR_INPUT_VOLTAGE
    [500] &CANcrit_func_Invertor_input_voltage,
  #endif
  #ifdef _CANcrit_USED_BATTERY_CURRENT
    [1050] &CANcrit_func_Battery_current,
  #endif
  #ifdef _CANcrit_USED_BATTERY_VOLTAGE
    [1051] &CANcrit_func_Battery_voltage,
  #endif
  #ifdef _CANcrit_USED_MAX_CELL_TEMP
    [1052] &CANcrit_func_Max_cell_temp,
  #endif
  #ifdef _CANcrit_USED_AVG_CELL_TEMP
    [1053] &CANcrit_func_Avg_cell_temp,
  #endif
  #ifdef _CANcrit_USED_MIN_CELL_TEMP
    [1054] &CANcrit_func_Min_cell_temp,
  #endif
  #ifdef _CANcrit_USED_LOWEST_CELL_VOLT
    [1055] &CANcrit_func_Lowest_cell_volt,
  #endif
  #ifdef _CANcrit_USED_PEDAL_CALIBRATION
    [2010] &CANcrit_func_Pedal_Calibration,
  #endif
  #ifdef _CANcrit_USED_BATTERY_FAN_PERCENT
    [2030] &CANcrit_func_Battery_fan_percent,
  #endif
  #ifdef _CANcrit_USED_UNIX_TIME
    [2031] &CANcrit_func_Unix_Time,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_TPP_BPP_STEER
    [2032] &CANcrit_func_ESP_log_TPP_BPP_steer,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_YAWRATE_VINS
    [2033] &CANcrit_func_ESP_log_yawrate_vins,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_WHSPD_FRONT
    [2034] &CANcrit_func_ESP_log_whspd_front,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_WHSPD_REAR
    [2035] &CANcrit_func_ESP_log_whspd_rear,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_VW_FRONT
    [2036] &CANcrit_func_ESP_log_vw_front,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_VW_REAR
    [2037] &CANcrit_func_ESP_log_vw_rear,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_ESP_TRQ
    [2038] &CANcrit_func_ESP_log_esp_trq,
  #endif
  #ifdef _CANcrit_USED_ESP_LOG_TCS_TRQ
    [2039] &CANcrit_func_ESP_log_tcs_trq,
  #endif
};

/**
  @brief List of RX callback functions for CANams


*/
const __dragon_CANbus_FuncTypedef _dragon_CANbus_RxFuncList_ams[2047] = {
  #ifdef _CANams_USED_REBOOT
    [2] &CANams_func_Reboot,
  #endif
  #ifdef _CANams_USED_PING
    [3] &CANams_func_Ping,
  #endif
  #ifdef _CANams_USED_SLAVE1_ERROR
    [11] &CANams_func_Slave1_Error,
  #endif
  #ifdef _CANams_USED_SLAVE2_ERROR
    [12] &CANams_func_Slave2_Error,
  #endif
  #ifdef _CANams_USED_SLAVE3_ERROR
    [13] &CANams_func_Slave3_Error,
  #endif
  #ifdef _CANams_USED_SLAVE4_ERROR
    [14] &CANams_func_Slave4_Error,
  #endif
  #ifdef _CANams_USED_SLAVE5_ERROR
    [15] &CANams_func_Slave5_Error,
  #endif
  #ifdef _CANams_USED_SLAVE6_ERROR
    [16] &CANams_func_Slave6_Error,
  #endif
  #ifdef _CANams_USED_SET_FAN_PWM
    [19] &CANams_func_Set_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE1_PONG
    [21] &CANams_func_Slave1_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE2_PONG
    [22] &CANams_func_Slave2_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE3_PONG
    [23] &CANams_func_Slave3_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE4_PONG
    [24] &CANams_func_Slave4_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE5_PONG
    [25] &CANams_func_Slave5_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE6_PONG
    [26] &CANams_func_Slave6_Pong,
  #endif
  #ifdef _CANams_USED_SLAVE1_DISCHARGE
    [31] &CANams_func_Slave1_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE2_DISCHARGE
    [32] &CANams_func_Slave2_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE3_DISCHARGE
    [33] &CANams_func_Slave3_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE4_DISCHARGE
    [34] &CANams_func_Slave4_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE5_DISCHARGE
    [35] &CANams_func_Slave5_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE6_DISCHARGE
    [36] &CANams_func_Slave6_discharge,
  #endif
  #ifdef _CANams_USED_SLAVE1_TEMP0
    [110] &CANams_func_Slave1_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE1_TEMP1
    [111] &CANams_func_Slave1_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE1_TEMP2
    [112] &CANams_func_Slave1_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE1_VOLTAGE0
    [113] &CANams_func_Slave1_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE1_VOLTAGE1
    [114] &CANams_func_Slave1_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE1_VOLTAGE2
    [115] &CANams_func_Slave1_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE1_VOLTAGE3
    [116] &CANams_func_Slave1_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE1_VOLTAGE4
    [117] &CANams_func_Slave1_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE1_FAN_PWM
    [118] &CANams_func_Slave1_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE2_TEMP0
    [120] &CANams_func_Slave2_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE2_TEMP1
    [121] &CANams_func_Slave2_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE2_TEMP2
    [122] &CANams_func_Slave2_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE2_VOLTAGE0
    [123] &CANams_func_Slave2_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE2_VOLTAGE1
    [124] &CANams_func_Slave2_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE2_VOLTAGE2
    [125] &CANams_func_Slave2_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE2_VOLTAGE3
    [126] &CANams_func_Slave2_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE2_VOLTAGE4
    [127] &CANams_func_Slave2_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE2_FAN_PWM
    [128] &CANams_func_Slave2_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE3_TEMP0
    [130] &CANams_func_Slave3_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE3_TEMP1
    [131] &CANams_func_Slave3_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE3_TEMP2
    [132] &CANams_func_Slave3_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE3_VOLTAGE0
    [133] &CANams_func_Slave3_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE3_VOLTAGE1
    [134] &CANams_func_Slave3_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE3_VOLTAGE2
    [135] &CANams_func_Slave3_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE3_VOLTAGE3
    [136] &CANams_func_Slave3_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE3_VOLTAGE4
    [137] &CANams_func_Slave3_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE3_FAN_PWM
    [138] &CANams_func_Slave3_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE4_TEMP0
    [140] &CANams_func_Slave4_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE4_TEMP1
    [141] &CANams_func_Slave4_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE4_TEMP2
    [142] &CANams_func_Slave4_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE4_VOLTAGE0
    [143] &CANams_func_Slave4_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE4_VOLTAGE1
    [144] &CANams_func_Slave4_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE4_VOLTAGE2
    [145] &CANams_func_Slave4_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE4_VOLTAGE3
    [146] &CANams_func_Slave4_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE4_VOLTAGE4
    [147] &CANams_func_Slave4_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE4_FAN_PWM
    [148] &CANams_func_Slave4_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE5_TEMP0
    [150] &CANams_func_Slave5_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE5_TEMP1
    [151] &CANams_func_Slave5_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE5_TEMP2
    [152] &CANams_func_Slave5_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE5_VOLTAGE0
    [153] &CANams_func_Slave5_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE5_VOLTAGE1
    [154] &CANams_func_Slave5_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE5_VOLTAGE2
    [155] &CANams_func_Slave5_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE5_VOLTAGE3
    [156] &CANams_func_Slave5_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE5_VOLTAGE4
    [157] &CANams_func_Slave5_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE5_FAN_PWM
    [158] &CANams_func_Slave5_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE6_TEMP0
    [160] &CANams_func_Slave6_Temp0,
  #endif
  #ifdef _CANams_USED_SLAVE6_TEMP1
    [161] &CANams_func_Slave6_Temp1,
  #endif
  #ifdef _CANams_USED_SLAVE6_TEMP2
    [162] &CANams_func_Slave6_Temp2,
  #endif
  #ifdef _CANams_USED_SLAVE6_VOLTAGE0
    [163] &CANams_func_Slave6_Voltage0,
  #endif
  #ifdef _CANams_USED_SLAVE6_VOLTAGE1
    [164] &CANams_func_Slave6_Voltage1,
  #endif
  #ifdef _CANams_USED_SLAVE6_VOLTAGE2
    [165] &CANams_func_Slave6_Voltage2,
  #endif
  #ifdef _CANams_USED_SLAVE6_VOLTAGE3
    [166] &CANams_func_Slave6_Voltage3,
  #endif
  #ifdef _CANams_USED_SLAVE6_VOLTAGE4
    [167] &CANams_func_Slave6_Voltage4,
  #endif
  #ifdef _CANams_USED_SLAVE6_FAN_PWM
    [168] &CANams_func_Slave6_Fan_PWM,
  #endif
  #ifdef _CANams_USED_SLAVE1_BOARDTEMP
    [501] &CANams_func_Slave1_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE1_5V
    [502] &CANams_func_Slave1_5V,
  #endif
  #ifdef _CANams_USED_SLAVE1_3V3
    [503] &CANams_func_Slave1_3V3,
  #endif
  #ifdef _CANams_USED_SLAVE2_BOARDTEMP
    [505] &CANams_func_Slave2_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE2_5V
    [506] &CANams_func_Slave2_5V,
  #endif
  #ifdef _CANams_USED_SLAVE2_3V3
    [507] &CANams_func_Slave2_3V3,
  #endif
  #ifdef _CANams_USED_SLAVE3_BOARDTEMP
    [509] &CANams_func_Slave3_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE3_5V
    [510] &CANams_func_Slave3_5V,
  #endif
  #ifdef _CANams_USED_SLAVE3_3V3
    [511] &CANams_func_Slave3_3V3,
  #endif
  #ifdef _CANams_USED_SLAVE4_BOARDTEMP
    [513] &CANams_func_Slave4_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE4_5V
    [514] &CANams_func_Slave4_5V,
  #endif
  #ifdef _CANams_USED_SLAVE4_3V3
    [515] &CANams_func_Slave4_3V3,
  #endif
  #ifdef _CANams_USED_SLAVE5_BOARDTEMP
    [517] &CANams_func_Slave5_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE5_5V
    [518] &CANams_func_Slave5_5V,
  #endif
  #ifdef _CANams_USED_SLAVE5_3V3
    [519] &CANams_func_Slave5_3V3,
  #endif
  #ifdef _CANams_USED_SLAVE6_BOARDTEMP
    [521] &CANams_func_Slave6_BoardTemp,
  #endif
  #ifdef _CANams_USED_SLAVE6_5V
    [522] &CANams_func_Slave6_5V,
  #endif
  #ifdef _CANams_USED_SLAVE6_3V3
    [523] &CANams_func_Slave6_3V3,
  #endif
};



/**
  @brief define filter mask. (mask0, ID0, mask1, ID1, FIFO, ENABLE)
*/
const uint16_t _dragon_CANbus_filterList_VCU_gen[14][6] = {
    {0x07FFu, 0x0080u, 0x07FFu, 0x0000u, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_PUMP_gen[14][6] = {
    {0x0000U, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //0.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //1.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //2.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //3.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //4.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //5.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //6.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //7.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //8.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //9.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //10.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //11.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //12.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U}   //13.filter
};
const uint16_t _dragon_CANbus_filterList_WHEEL_gen[14][6] = {
    {0x0000U, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //0.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //1.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //2.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //3.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //4.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //5.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //6.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //7.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //8.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //9.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //10.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //11.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U},  //12.filter
    {0x07FEU, 0x0000U, 0x07FFU, 0x0000U, 0x0000U, 0x0000U}   //13.filter
};
const uint16_t _dragon_CANbus_filterList_ESP_gen[14][6] = {
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  0   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FFu, 0x041Fu, 0x07FFu, 0x0000u, 0x0000u, 0x0001u},    //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_DATALOG_gen[14][6] = {
    {0x07FFu, 0x007Eu, 0x07FCu, 0x00C8u, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FEu, 0x00CCu, 0x07FEu, 0x0190u, 0x0001u, 0x0001u},    //  1   Filtr Bank
    {0x07FEu, 0x01F4u, 0x07FEu, 0x041Au, 0x0001u, 0x0001u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FCu, 0x041Cu, 0x07FEu, 0x07EEu, 0x0000u, 0x0001u},    //  7   Filtr Bank
    {0x07F8u, 0x07F0u, 0x07FEu, 0x07F8u, 0x0000u, 0x0001u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_HV_gen[14][6] = {
    {0x07FFu, 0x01F4u, 0x07FFu, 0x0000u, 0x0000u, 0x0001u}, //  0   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  6   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}  //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_VCU_crit[14][6] = {
    {0x07FCu, 0x007Cu, 0x07FEu, 0x012Cu, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FEu, 0x0190u, 0x07FFu, 0x01F4u, 0x0001u, 0x0001u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FEu, 0x041Au, 0x07FCu, 0x041Cu, 0x0000u, 0x0001u},    //  7   Filtr Bank
    {0x07FFu, 0x07DAu, 0x07FEu, 0x07EEu, 0x0000u, 0x0001u},    //  8   Filtr Bank
    {0x07F8u, 0x07F0u, 0x07FFu, 0x0000u, 0x0000u, 0x0001u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_ESP_crit[14][6] = {
    {0x07FFu, 0x007Fu, 0x07FFu, 0x012Cu, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FFu, 0x0191u, 0x07FFu, 0x0005u, 0x0001u, 0x0001u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FEu, 0x041Au, 0x07FCu, 0x041Fu, 0x0000u, 0x0001u},    //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_PEDAL_crit[14][6] = {
    {0x07FFu, 0x0005u, 0x07FFu, 0x0000u, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_AMSM_crit[14][6] = {
    {0x07FFu, 0x0005u, 0x07FFu, 0x0080u, 0x0001u, 0x0001u},    //  0   Filtr Bank
    {0x07FFu, 0x01F4u, 0x07FFu, 0x0000u, 0x0001u, 0x0001u},    //  1   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  2   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  3   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  6   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  7   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  8   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u},    //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}     //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_AMSS_ams[14][6] = {
    {0x07ffU, 0x000bU, 0x07ffU, 0x0000U, 0x0001U, 0x0001U},   //  0   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  1   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  2   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  3   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  4   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  5   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  6   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  7   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  8   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  9   Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  10  Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  11  Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U},   //  12  Filtr Bank
    {0x07ffU, 0x0000U, 0x07ffU, 0x0000U, 0x0000U, 0x0000U}    //  13  Filtr Bank
};
const uint16_t _dragon_CANbus_filterList_AMSM_ams[14][6] = {
    {0x07FCu, 0x0015u, 0x07FCu, 0x0018u, 0x0001u, 0x0001u}, //  0   Filtr Bank
    {0x07FEu, 0x006Eu, 0x07F0u, 0x0070u, 0x0001u, 0x0001u}, //  1   Filtr Bank
    {0x07E0u, 0x0080u, 0x07F8u, 0x00A0u, 0x0001u, 0x0001u}, //  2   Filtr Bank
    {0x07FCu, 0x000Cu, 0x07FFu, 0x0010u, 0x0001u, 0x0001u}, //  3   Filtr Bank
    {0x07FFu, 0x000Bu, 0x07FFu, 0x0000u, 0x0001u, 0x0001u}, //  4   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  5   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  6   Filtr Bank
    {0x07FCu, 0x01F5u, 0x07FCu, 0x01F9u, 0x0000u, 0x0001u}, //  7   Filtr Bank
    {0x07FCu, 0x01FDu, 0x07FCu, 0x0201u, 0x0000u, 0x0001u}, //  8   Filtr Bank
    {0x07FCu, 0x0205u, 0x07FCu, 0x0209u, 0x0000u, 0x0001u}, //  9   Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  10  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  11  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}, //  12  Filtr Bank
    {0x07FFu, 0x0000u, 0x07FFu, 0x0000u, 0x0000u, 0x0000u}  //  13  Filtr Bank
};

/**
  @brief Callback function for extended msg
*/
__weak void _CANext_func_callback(uint8_t aPayload[], uint32_t IDmsg);
