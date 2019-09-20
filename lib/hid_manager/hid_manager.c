#include "hid_manager.h"


QueueHandle_t media_q;
QueueHandle_t keyboard_q;

uint8_t key_report[KEYBOARD_REPORT_LENGTH] = { 0 };
uint8_t media_report[HID_CC_IN_RPT_LEN] = { 0 };

esp_err_t hal_BLE_Init() {
  esp_bt_controller_config_t bt_cfg;
  esp_err_t ret;

	/* set the security iocap & auth_req & key size & init key response key parameters to the stack*/
	esp_ble_auth_req_t auth_req = ESP_LE_AUTH_BOND; //bonding with peer device after authentication
	esp_ble_io_cap_t iocap = ESP_IO_CAP_NONE; //set the IO capability to No output No input
	uint8_t key_size = 16;      //the key size should be 7~16 bytes
	uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
	uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;

	TaskHandle_t xBLETask_keyboard;
	TaskHandle_t xBLETask_media;


  keyboard_q = xQueueCreate(KEYBOARD_QUEUE_LENGTH, KEYBOARD_REPORT_LENGTH * sizeof(uint8_t));
	media_q = xQueueCreate(MEDIA_QUEUE_LENGTH, HID_CC_IN_RPT_LEN * sizeof(uint8_t));

  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
  bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

  
	ret = esp_bt_controller_init(&bt_cfg);
	if (ret) {
		ESP_LOGE(HID_MANAGER_TAG, "%s initialize controller failed\n", __func__);
		return ESP_FAIL;
	}

	ret = esp_bluedroid_init();
	if (ret) {
		ESP_LOGE(HID_MANAGER_TAG, "%s init bluedroid failed\n", __func__);
		return ESP_FAIL;
	}

	ret = esp_bluedroid_enable();
	if (ret) {
		ESP_LOGE(HID_MANAGER_TAG, "%s init bluedroid failed\n", __func__);
		return ESP_FAIL;
	}

	if (!hidd_le_env.enabled) {
		memset(&hidd_le_env, 0, sizeof(hidd_le_env_t));
		hidd_le_env.enabled = true;
	}

	
	esp_ble_gap_register_callback(gap_event_handler);
	hidd_le_env.hidd_cb = hidd_event_callback;

	if (hidd_register_cb() != ESP_OK) {
		ESP_LOGE(HID_MANAGER_TAG, "register CB failed");
		return ESP_FAIL;
	}

	esp_ble_gatts_app_register(BATTRAY_APP_ID);
	if (esp_ble_gatts_app_register(HIDD_APP_ID) != ESP_OK) {
		ESP_LOGE(HID_MANAGER_TAG, "Register App failed");
		return ESP_FAIL;
	}



	xTaskCreatePinnedToCore(halBLETask_keyboard, "ble_task_keyboard",
			TASK_BLE_STACKSIZE, NULL, configMAX_PRIORITIES, &xBLETask_keyboard,
			0);
	xTaskCreatePinnedToCore(halBLETask_media, "ble_task_media",
			TASK_BLE_STACKSIZE, NULL, configMAX_PRIORITIES, &xBLETask_media, 0);


	//set log level according to define
	esp_log_level_set(HID_LE_PRF_TAG, LOG_LEVEL_BLE);
	esp_log_level_set(HID_MANAGER_TAG, LOG_LEVEL_BLE);

	return ESP_OK;
}






/** @brief Callback for GAP events */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){
	switch (event) {

	case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
		esp_ble_gap_start_advertising(&hidd_adv_params);
		break;

	case ESP_GAP_BLE_SEC_REQ_EVT:
		for (int i = 0; i < ESP_BD_ADDR_LEN; i++) {
			ESP_LOGD(HID_MANAGER_TAG, "%x:", param->ble_security.ble_req.bd_addr[i]);
		}
		esp_ble_gap_security_rsp(param->ble_security.ble_req.bd_addr, true);
		break;

	case ESP_GAP_BLE_AUTH_CMPL_EVT:
		sec_conn = true;
		esp_bd_addr_t bd_addr;
		memcpy(bd_addr, param->ble_security.auth_cmpl.bd_addr,
				sizeof(esp_bd_addr_t));
		ESP_LOGI(HID_MANAGER_TAG, "remote BD_ADDR: %08x%04x",
				(bd_addr[0] << 24) + (bd_addr[1] << 16) + (bd_addr[2] << 8)
						+ bd_addr[3], (bd_addr[4] << 8) + bd_addr[5]);
		ESP_LOGI(HID_MANAGER_TAG, "address type = %d",
				param->ble_security.auth_cmpl.addr_type);
		ESP_LOGI(HID_MANAGER_TAG, "pair status = %s",
				param->ble_security.auth_cmpl.success ? "success" : "fail");
		if (!param->ble_security.auth_cmpl.success) {
			ESP_LOGE(HID_MANAGER_TAG, "fail reason = 0x%x",
					param->ble_security.auth_cmpl.fail_reason);
		}
		break;

	default:
		break;
	}
}


/** @brief Callback for HID events. */
static void hidd_event_callback(esp_hidd_cb_event_t event, esp_hidd_cb_param_t *param) {
	switch (event) {
	case ESP_HIDD_EVENT_REG_FINISH:
		if (param->init_finish.state == ESP_HIDD_INIT_OK) {
			//esp_bd_addr_t rand_addr = {0x04,0x11,0x11,0x11,0x11,0x05};

			esp_ble_gap_set_device_name(GATTS_TAG);
			esp_ble_gap_config_adv_data(&hidd_adv_data);
		}
		break;

	case ESP_BAT_EVENT_REG:
		break;
	case ESP_HIDD_EVENT_DEINIT_FINISH:
		break;
	case ESP_HIDD_EVENT_BLE_CONNECT:
		ESP_LOGI(HID_MANAGER_TAG, "ESP_HIDD_EVENT_BLE_CONNECT");
		hid_conn_id = param->connect.conn_id;
		break;
	case ESP_HIDD_EVENT_BLE_DISCONNECT:
		sec_conn = false;
		ESP_LOGI(HID_MANAGER_TAG, "ESP_HIDD_EVENT_BLE_DISCONNECT");
		esp_ble_gap_start_advertising(&hidd_adv_params);
		break;
	case ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT:
		ESP_LOGI(HID_MANAGER_TAG, "%s, ESP_HIDD_EVENT_BLE_VENDOR_REPORT_WRITE_EVT",
				__func__);
		ESP_LOG_BUFFER_HEX(HID_MANAGER_TAG, param->vendor_write.data,
				param->vendor_write.length);
		break;
	default:
		break;
	}
	return;
}



/** @brief CONTINOUS TASK - sending HID commands via BLE
 * 
 * This task is used to wait for HID commands, sent to the hid_ble
 * queue. If one command is received, it will be sent to a (possibly)
 * connected BLE device.
 */
void halBLETask_keyboard(void * params) {
	if (keyboard_q != NULL){
		xQueueReset(keyboard_q);
	}
	while(1) {
		// Check if queue is initialized
		if (keyboard_q != NULL) {
			while (1) {
				//pend on MQ, if timeout triggers, just wait again.
				if (xQueueReceive(keyboard_q, &key_report, portMAX_DELAY)) {
					//if we are not connected, discard.
					if (sec_conn == true){
						hid_dev_send_report(hidd_le_env.gatt_if, hid_conn_id, HID_RPT_ID_KEY_IN, 
							HID_REPORT_TYPE_INPUT, KEYBOARD_REPORT_LENGTH, key_report);
					}
				}
			}
		} else {
			ESP_LOGE(HID_MANAGER_TAG, "ble hid queue not initialized, retry in 1s");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
}



void halBLETask_media(void * params) {

	//Empty queue if initialized (there might be something left from last connection)
	if (media_q != NULL){
		xQueueReset(media_q);
	}

	while(1){
		//check if queue is initialized
		if (media_q != NULL){
			while(1){
				//pend on MQ, if timeout triggers, just wait again.
				if (xQueueReceive(media_q, &media_report, portMAX_DELAY)) {
					//if we are not connected, discard.
					if (sec_conn == true){
						hid_dev_send_report(hidd_le_env.gatt_if, hid_conn_id, HID_RPT_ID_CC_IN, 
							HID_REPORT_TYPE_INPUT, HID_CC_IN_RPT_LEN, media_report);
					}
				}
			}
		}else{
			ESP_LOGE(HID_MANAGER_TAG, "ble hid queue not initialized, retry in 1s");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
}
