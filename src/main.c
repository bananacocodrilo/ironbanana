#include "persisted_config.h"

#include "matrix.h"
#include "hal_ble.h"
#include "split_master.h"
#include "espnow_split.h"
#include "keycode_conv.h"
#include "keypress_handles.h"

#define MAIN_TAG "MAIN"

static config_data_t config;

QueueHandle_t master_recieve_q;
TaskHandle_t xKeyreportTask;

bool DEEP_SLEEP = false;


void espnow_update_matrix(void *pvParameters);
void key_reports(void *pvParameters);
void deep_sleep(void *pvParameters);

void app_main() {
	// Reset the RTC pins and prepare the matrix
	rtc_matrix_deinit();
	matrix_setup();

	// Initialize NVS
	initialize_nvs();

	#ifdef MASTER
		// Initialize config
		load_persisted_config(&config);
		
		// Activate keyboard BT stack
		halBLEInit(1, 1, 1, 0);
		ESP_LOGI("HIDD", "MAIN finished...");
	#endif

	//If the device is a master for split board initialize receiving reports from slave
	#ifdef SPLIT_MASTER
		master_recieve_q = xQueueCreate(32, REPORT_LEN * sizeof(uint8_t));
		espnow_recieve();
		xTaskCreatePinnedToCore(espnow_update_matrix, "ESP-NOW slave matrix state updates",
				4096, NULL, configMAX_PRIORITIES, NULL, 1);
		ESP_LOGI("ESPNOW", "initializezd");
	#endif

	// Start the keyboard Tasks
	// Create the key scanning task on core 1 (otherwise it will crash)
	#ifdef MASTER
		BLE_EN = 1;
		xTaskCreatePinnedToCore(key_reports, "key report task", 8192,
				xKeyreportTask, configMAX_PRIORITIES, NULL, 1);
		ESP_LOGI("Keyboard task", "initializezd");
	#endif

	#ifdef SLEEP_MINS
		xTaskCreatePinnedToCore(deep_sleep, "deep sleep task", 4096, NULL,
				configMAX_PRIORITIES, NULL, 1);
		ESP_LOGI("Sleep", "initializezd");
	#endif


}



// Task to update the matrix state via reports recieved by espnow
void espnow_update_matrix(void *pvParameters) {

	uint8_t CURRENT_MATRIX[MATRIX_ROWS][MATRIX_COLS] = { 0 };
	while (1) {
		if (xQueueReceive(espnow_recieve_q, &CURRENT_MATRIX, 10000)) {
			DEEP_SLEEP = false;
			memcpy(&SLAVE_MATRIX_STATE, &CURRENT_MATRIX, sizeof CURRENT_MATRIX);
		}
	}
}


void key_reports(void *pvParameters) {
	// Arrays for holding the report at various stages
	uint8_t past_report[REPORT_LEN] = { 0 };
	uint8_t report_state[REPORT_LEN];

	while (1) {
		memcpy(report_state, check_key_state(layouts[current_layout]),
				sizeof report_state);
		//Do not send anything if queues are uninitialized
		if (mouse_q == NULL || keyboard_q == NULL || joystick_q == NULL) {
			ESP_LOGE(MAIN_TAG, "queues not initialized");
			continue;
		}

		//Check if the report was modified, if so send it
		if (memcmp(past_report, report_state, sizeof past_report) != 0) {
			DEEP_SLEEP = false;
			memcpy(past_report, report_state, sizeof past_report);

			if(BLE_EN == 1){
				xQueueSend(keyboard_q, (void*) &report_state, (TickType_t) 0);
			}
			if(input_str_q != NULL){
				xQueueSend(input_str_q, (void*) &report_state, (TickType_t) 0);
			}
		}
	}
}


#ifdef SLEEP_MINS
void deep_sleep(void *pvParameters) {
	uint64_t initial_time = esp_timer_get_time(); // notice that timer returns time passed in microseconds!
	uint64_t current_time_passed = 0;
	while (1) {

		current_time_passed = (esp_timer_get_time() - initial_time);

		if (DEEP_SLEEP == false) {
			current_time_passed = 0;
			initial_time = esp_timer_get_time();
			DEEP_SLEEP = true;
		}

		if (current_time_passed >= 1000000 * 60 * SLEEP_MINS) {
			if (DEEP_SLEEP == true) {
				ESP_LOGE(MAIN_TAG, "going to sleep!");
#ifdef OLED_ENABLE
				vTaskDelay(20 / portTICK_PERIOD_MS);
				vTaskSuspend(xOledTask);
				deinit_oled();
#endif
				// wake up esp32 using rtc gpio
				rtc_matrix_setup();
				esp_sleep_enable_touchpad_wakeup();
				esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
				esp_deep_sleep_start();

			}
			if (DEEP_SLEEP == false) {
				current_time_passed = 0;
				initial_time = esp_timer_get_time();
				DEEP_SLEEP = true;
			}
		}

	}

}
#endif