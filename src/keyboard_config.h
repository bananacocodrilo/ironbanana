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
const gpio_num_t MATRIX_COLS_PINS[] = { 
  GPIO_NUM_4, GPIO_NUM_27, GPIO_NUM_26, GPIO_NUM_39, GPIO_NUM_25, GPIO_NUM_36 
  };
const gpio_num_t MATRIX_ROWS_PINS[] = { 
  GPIO_NUM_32, 
  GPIO_NUM_33, 
  GPIO_NUM_34, 
  GPIO_NUM_35 
  };


#define SLEEP_MINS 10 //Inactivity time before going to deep sleep






#endif /*  KEYBOARD_CONFIG_H */