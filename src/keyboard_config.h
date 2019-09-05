#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include <stdint.h>
#include <driver/gpio.h>


//Define keyboard structure 
#define MASTER
#define KEYPADS 3

#define MATRIX_ROWS 4
#define MATRIX_COLS 6

/*
 * Pins connected to the switches matrix. 
 * Make sure to use the at least one RTC pin on cols and one on rows
 */
extern const gpio_num_t MATRIX_COLS_PINS[];
extern const gpio_num_t MATRIX_ROWS_PINS[];


#define SLEEP_MINS 10 //Inactivity time before going to deep sleep






#endif /*  KEYBOARD_CONFIG_H */