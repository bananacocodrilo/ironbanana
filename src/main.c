
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "firmware_config.h"
#include "matrix.h"
#include "main_tasks.h"


TaskHandle_t xKpReportsTask;


void app_main(){
  	initialize_matrix_pins();

		xTaskCreatePinnedToCore(keypress_reports, KP_REPORTS_TAG, KP_REPORTS_STACK_DEPTH,
				NULL, KP_REPORTS_PRIORITY, xKpReportsTask, KP_REPORTS_CORE);
}