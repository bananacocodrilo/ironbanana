#ifndef KEYBOARD_CONFIG_H_
#define KEYBOARD_CONFIG_H_

#include <driver/gpio.h>

#define ROW2COL // or COL2ROW


// Keypad configuration
#define KEYPAD_POSITION 1

#define MATRIX_COLS 2
#define MATRIX_ROWS 2

extern const gpio_num_t MATRIX_COLS_PINS[];
extern const gpio_num_t MATRIX_ROWS_PINS[];


// Complete Keyboard configuration
#define NUM_KEYPADS 1


#endif