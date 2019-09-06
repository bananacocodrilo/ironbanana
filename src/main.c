
#include "matrix.h"

#include <nvs_flash.h>

void app_main() {
	esp_err_t ret;

	// Reset the RTC pins and prepare the matrix
	rtc_matrix_deinit();
	matrix_setup();

	// Initialize NVS.
	ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK (nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

}