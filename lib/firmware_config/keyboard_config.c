#include "keyboard_config.h"

const gpio_num_t MATRIX_COLS_PINS[MATRIX_COLS] = { 
  GPIO_NUM_4, GPIO_NUM_27, GPIO_NUM_26 //, GPIO_NUM_17, GPIO_NUM_25, GPIO_NUM_16 
};
const gpio_num_t MATRIX_ROWS_PINS[MATRIX_ROWS] = { 
  GPIO_NUM_32, 
  GPIO_NUM_33, 
//  GPIO_NUM_2, 
//  GPIO_NUM_0 
};