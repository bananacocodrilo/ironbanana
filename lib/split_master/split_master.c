#include "split_master.h"

static const uint8_t channel = 1;

static void wifi_initialize_recieve(void) {
	uint8_t slave_mac_adr[6];
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

	ESP_LOGI(SPLIT_MASTER_TAG, "Initialing WiFi");
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_create_default());

	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); // For some reason ESP-NOW only works if all devices are in the same mode
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	
	ESP_ERROR_CHECK(esp_wifi_start());
	esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE); // Make sure we are on the same channel
	ESP_ERROR_CHECK(esp_wifi_get_mac(ESP_IF_WIFI_STA, slave_mac_adr));

	//Printout the mac ID (in case we change the starting one)
	printf("\nDEVICE MAC ADDRESS:[");
	for (int i = 0; i < 6; i++) {
		printf("%2X:", slave_mac_adr[i]);
	}
	printf("]\n");
}

//ESP-NOW callback upon receiving data
static void espnow_recv_cb(const uint8_t *mac_addr, const uint8_t *data,
		int data_len) {
	uint8_t CURRENT_ENCODER[1] = { 0 };
	uint8_t CURRENT_MATRIX[MATRIX_ROWS][MATRIX_COLS] = { 0 };
	ESP_LOGI(SPLIT_MASTER_TAG, "Data received!");

	// for key reports
	if (data_len == MATRIX_ROWS * MATRIX_COLS) {
		memcpy(CURRENT_MATRIX, data, sizeof(CURRENT_MATRIX));
		xQueueSend(espnow_recieve_q, (void*) &CURRENT_MATRIX, (TickType_t) 0);
	}

}

//Initialize receiving via ESP-NOW
static void espnow_initialize_recieve(void) {
	ESP_LOGI(SPLIT_MASTER_TAG, "Initialing ESP-NOW");
	esp_now_init();
	esp_now_register_recv_cb(espnow_recv_cb);
}

void espnow_recieve(void) {
	ESP_LOGI(SPLIT_MASTER_TAG, "Initialing ESP-NOW functions for receiving data");

	wifi_initialize_recieve();
	espnow_initialize_recieve();
}
