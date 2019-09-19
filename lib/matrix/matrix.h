#ifndef MATRIX_H_
#define MATRIX_H_

#include <driver/gpio.h>

#include <esp_log.h>
#include <esp_timer.h>

#include "firmware_config.h"

#define DEBOUNCE_TIME 10

enum direction {
  RELEASED = 0,
  PRESSED
};

extern uint8_t keyboard_matrix[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS];


/**
 * Configure matrix pins as appropiate inputs/outputs
*/
void initialize_matrix_pins(void);

/**
 * Scans the state of the matrix pins
*/
void scan_matrix_pins(void);

/**
 * Joins master's and slaves' matrix into a single one
*/
void compose_keyboard_matrix(void);

/**
 * Visual log of the keyboard state
*/
void log_matrix_state(void);

#endif