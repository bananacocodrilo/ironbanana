#include "persisted_config.h"

#include "utils.h"
#include "matrix.h"


static config_data_t config;

void app_main() {
	nvs_handle memory_handle;
	esp_err_t err_status;

	// Reset the RTC pins and prepare the matrix
	rtc_matrix_deinit();
	matrix_setup();

	// Initialize NVS
	initialize_nvs();

	#ifdef MASTER
	// Initialize config
		err_status = load_persisted_config(&config);
	// 	//activate keyboard BT stack
	// 	halBLEInit(1, 1, 1, 0);
	// 	ESP_LOGI("HIDD", "MAIN finished...");
	#endif



}