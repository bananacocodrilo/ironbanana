

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

	// Initialize config
	err_status = load_stored_config(&config, &memory_handle);
	if(err_status != ESP_OK){
		load_default_config(&config);
	}






}