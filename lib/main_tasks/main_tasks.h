#ifndef MAIN_TASKS_H_
#define MAIN_TASKS_H_

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "firmware_config.h"
#include "matrix.h"
#include "layouts.h"
#include "hid_manager.h"
#include "keyboard.h"

#include "add_ons.h"


// Config for keypress_reports
#define KP_REPORTS_TAG  "Keypress reports task"
#define KP_REPORTS_STACK_DEPTH  8192 //8KB
#define KP_REPORTS_PRIORITY 10  
#define KP_REPORTS_CORE 0

// Adds the keypresses to the reports queues
void keypress_reports(void *pvParameters);




#endif