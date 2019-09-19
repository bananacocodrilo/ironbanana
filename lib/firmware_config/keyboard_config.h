#ifndef KEYBOARD_CONFIG_H_
#define KEYBOARD_CONFIG_H_

#include <driver/gpio.h>

#define ROW2COL // or COL2ROW


// Keypad configuration
#define KEYPAD_POSITION 1 // For split keyboards this is the position of this keypad in the complete layout

#define MATRIX_COLS 3
#define MATRIX_ROWS 2

extern const gpio_num_t MATRIX_COLS_PINS[];
extern const gpio_num_t MATRIX_ROWS_PINS[];


// Complete Keyboard configuration
#define NUM_KEYPADS 1


#endif