#ifndef HID_MANAGER_H_
#define HID_MANAGER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include <freertos/queue.h>

#include <esp_log.h>
#include <esp_bt.h>
#include <esp_bt_defs.h>
#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>
#include <esp_gatt_defs.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>
#include <nvs_flash.h>

#include "hid_dev.h"
#include "firmware_config.h"


#define LOG_LEVEL_BLE ESP_LOG_INFO

#define TASK_BLE_STACKSIZE 2048
#define KEYBOARD_QUEUE_LENGTH 32
#define MEDIA_QUEUE_LENGTH 32

extern QueueHandle_t keyboard_q;
extern QueueHandle_t media_q;

esp_err_t hal_BLE_Init();

void halBLETask_keyboard(void * params);
void halBLETask_media(void * params);







#endif