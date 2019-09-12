#include "persisted_config.h"

#include "utils.h"
#include "matrix.h"
#include "hal_ble.h"

static config_data_t config;

void app_main() {
	esp_err_t err_status;

	// Reset the RTC pins and prepare the matrix
	rtc_matrix_deinit();
	matrix_setup();

	// Initialize NVS
	initialize_nvs();

	#ifdef MASTER
		// Initialize config
		err_status = load_persisted_config(&config);
		
		// Activate keyboard BT stack
		halBLEInit(1, 1, 1, 0);
		ESP_LOGI("HIDD", "MAIN finished...");
	#endif

	//If the device is a master for split board initialize receiving reports from slave
	#ifdef SPLIT_MASTER
		espnow_recieve_q = xQueueCreate(32, REPORT_LEN * sizeof(uint8_t));
		espnow_recieve();
		xTaskCreatePinnedToCore(espnow_update_matrix, "ESP-NOW slave matrix state updates",
				4096, NULL, configMAX_PRIORITIES, NULL, 1);
		ESP_LOGI("ESPNOW", "initializezd");
	#endif


}