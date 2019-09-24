
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "firmware_config.h"
#include "matrix.h"
// #include "hid_manager.h"
#include "HID_kbdmousejoystick.h"

#include "main_tasks.h"


TaskHandle_t xKpReportsTask;


void app_main(){
	initialize_matrix_pins();
	// hal_BLE_Init();
	HID_kbdmousejoystick_init(1,0,0,0,BLUETOOTH_DEVICE_NAME);

	xTaskCreatePinnedToCore(keypress_reports, KP_REPORTS_TAG, KP_REPORTS_STACK_DEPTH,
		NULL, KP_REPORTS_PRIORITY, xKpReportsTask, KP_REPORTS_CORE);
}