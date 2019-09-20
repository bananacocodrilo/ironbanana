#ifndef HID_MANAGER_H_
#define HID_MANAGER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include <freertos/queue.h>

#include <esp_log.h>
#include <esp_bt.h>

#include "hidd_le_prf_int.h"

#include "firmware_config.h"

#define LOG_LEVEL_BLE ESP_LOG_INFO

#define TASK_BLE_STACKSIZE 2048

#define KRO_14 14
#define KEYBOARD_QUEUE_LENGTH 32
#define KEYBOARD_REPORT_LENGTH KRO_14

#define MEDIA_QUEUE_LENGTH 32
#define HID_CC_IN_RPT_LEN 2 // HID consumer control input report length


extern QueueHandle_t keyboard_q;
extern QueueHandle_t media_q;

esp_err_t hal_BLE_Init();


// void send_report( void );





/** @brief Connection ID for an opened HID connection */
static uint16_t hid_conn_id = 0;
/** @brief Do we have a secure connection? */
static bool sec_conn = false;
/** @brief Full UUID for the HID service (LSB, ..., MSB)*/
static uint8_t hidd_service_uuid128[] = {
  0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 
  0x00, 0x10, 0x00, 0x00, 0x12, 0x18, 0x00, 0x00, 
};


/** @brief Advertising parameters */
static esp_ble_adv_params_t hidd_adv_params = { 
  .adv_int_min = 0x20,
  .adv_int_max = 0x30, 
  .adv_type = ADV_TYPE_IND, 
  .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
  .channel_map = ADV_CHNL_ALL, 
  .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY, 
};

/** @brief Advertising data for BLE */
static esp_ble_adv_data_t hidd_adv_data = { 
  .set_scan_rsp = false,
  .include_name = true, 
  .include_txpower = true, 
  .min_interval = 0x0006, //slave connection min interval, Time = min_interval * 1.25 msec
  .max_interval = 0x0010, //slave connection max interval, Time = max_interval * 1.25 msec
  .appearance = 0x03c0,       //HID Generic,
  .manufacturer_len = 0, 
  .p_manufacturer_data = NULL, 
  .service_data_len = 0, 
  .p_service_data = NULL, 
  .service_uuid_len = sizeof(hidd_service_uuid128), 
  .p_service_uuid = hidd_service_uuid128, 
  .flag = 0x6, 
};


static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
static void hidd_event_callback(esp_hidd_cb_event_t event, esp_hidd_cb_param_t *param);



#endif