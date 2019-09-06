

#include "utils.h"
#include "matrix.h"


static config_data_t config;

void app_main() {
	esp_err_t err_stat;
	nvs_handle memory_handle;
	size_t max_word_length = MAX_BT_DEVICENAME_LENGTH;


	// Reset the RTC pins and prepare the matrix
	rtc_matrix_deinit();
	matrix_setup();

	// Initialize NVS
	initialize_nvs(memory_handle);

	// Initialize config
	load_default_config(&config);
	load_stored_config(&config, memory_handle);


	strcpy(config.bt_device_name, GATTS_TAG);
	nvs_get_str(memory_handle, "btname", config.bt_device_name, &max_word_length);




}