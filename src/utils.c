#include "utils.h"

uint32_t millis() {
	return esp_timer_get_time() / 1000;
}


/**
 * Initializes the NVS
 * 
 */
void initialize_nvs(nvs_handle memory_handle){
	esp_err_t err_stat = nvs_flash_init();
	if (err_stat == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK (nvs_flash_erase());
		err_stat = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err_stat);
}


/**
 * Loads the default configuration
 * 
 */
void load_default_config(config_data_t* config){
	strcpy(config->bt_device_name, GATTS_TAG);
}

/**
 * Loads the configuration stored in memory
 * 
 */

void load_stored_config(config_data_t* config, nvs_handle memory_handle){

	if (ESP_OK != nvs_open("config_c", NVS_READWRITE, &memory_handle)){
		ESP_LOGE("Utils", "Error opening NVS");
	}

	if (ESP_OK != nvs_get_str(memory_handle, 
		"btname", *config->bt_device_name, &MAX_BT_DEVICENAME_LENGTH)){

		ESP_LOGE("Utils", "Error reading Bluetooth name from NVS. Setting to \"%s\"",
			*config->bt_device_name);
	}
}
	