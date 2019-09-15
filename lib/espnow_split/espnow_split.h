#ifndef ESPNOW_SPLIT_H_
#define ESPNOW_SPLIT_H_

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/timers.h>
#include <freertos/queue.h>

#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "tcpip_adapter.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"

#include "keyboard_config.h"
#include "persisted_config.h"


#define ESPNOW_SPLIT "ESPNOW_SPLIT"

//Queue for sending report from matrix scan
extern QueueHandle_t espnow_matrix_send_q;
extern QueueHandle_t espnow_encoder_send_q;

//Queue for recieving report from slave
extern QueueHandle_t espnow_recieve_q;

/** 
 * @Setup the function for sending data via espnow
 */
void espnow_send(void);
/** 
 * @Setup the function for recieveing data via espnow
 */
void espnow_recieve(void);

#endif /* ESPNOW_SPLIT_H_ */
