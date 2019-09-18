#ifndef MATRIX_H_
#define MATRIX_H_

#include <driver/gpio.h>

#include <esp_log.h>
#include <esp_timer.h>

#include "firmware_config.h"

#define DEBOUNCE_TIME 9

/**
 * Configure matrix pins as appropiate inputs/outputs
*/
void initialize_matrix_pins(void);

/**
 * Scans the state of the matrix pins
*/
void scan_matrix_pins(void);



#endif