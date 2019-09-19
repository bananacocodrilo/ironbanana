#include "matrix.h"


// The accepted matrix status. This is the one we export to be used in other places 
uint8_t matrix_state[MATRIX_ROWS][MATRIX_COLS] = { 0 }; 
uint8_t prev_matrix_state[MATRIX_ROWS][MATRIX_COLS] = { 0 };
uint32_t debounce_matrix[MATRIX_ROWS][MATRIX_COLS] = { 0 };

uint8_t keyboard_matrix[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = { 0 }; 


#ifdef COL2ROW
void initialize_matrix_pins(void){
	// Initializing columns
	for (uint8_t col = 0; col < MATRIX_COLS; col++) {

		gpio_pad_select_gpio(MATRIX_COLS_PINS[col]);
		gpio_set_direction(MATRIX_COLS_PINS[col], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_level(MATRIX_COLS_PINS[col], 0);

		ESP_LOGI(GPIO_TAG,"%d is level %d", MATRIX_COLS_PINS[col],
				gpio_get_level(MATRIX_COLS_PINS[col]));
	}

	// Initializing rows
	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {

		gpio_pad_select_gpio(MATRIX_ROWS_PINS[row]);
		gpio_set_direction(MATRIX_ROWS_PINS[row], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_drive_capability(MATRIX_ROWS_PINS[row], GPIO_DRIVE_CAP_0);
		gpio_set_level(MATRIX_ROWS_PINS[row], 0);

		ESP_LOGI(GPIO_TAG,"%d is level %d", MATRIX_ROWS_PINS[row],
				gpio_get_level(MATRIX_ROWS_PINS[row]));
	}

}

#else

void initialize_matrix_pins(void){
	for(uint8_t row=0; row < MATRIX_ROWS; row++) {

		gpio_pad_select_gpio(MATRIX_ROWS_PINS[row]);
		gpio_set_direction(MATRIX_ROWS_PINS[row], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_level(MATRIX_ROWS_PINS[row], 0);
		ESP_LOGI(MATRIX_TAG,"%d is level %d",MATRIX_ROWS_PINS[row],gpio_get_level(MATRIX_ROWS_PINS[row]));
	}

	// Initializing columns
	for(uint8_t col=0; col < MATRIX_COLS; col++) {

		gpio_pad_select_gpio(MATRIX_COLS_PINS[col]);
		gpio_set_direction(MATRIX_COLS_PINS[col], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_drive_capability(MATRIX_COLS_PINS[col],GPIO_DRIVE_CAP_0);
		gpio_set_level(MATRIX_COLS_PINS[col], 0);

		ESP_LOGI(MATRIX_TAG,"%d is level %d",MATRIX_COLS_PINS[col],gpio_get_level(MATRIX_COLS_PINS[col]));
	}
}
#endif



void scan_matrix_pins(){
  uint8_t curState = 0;
  uint32_t execMillis = esp_timer_get_time() / 1000;

#ifdef COL2ROW
	// Set a column as high.
	for (uint8_t col = 0; col < MATRIX_COLS; col++) {
		gpio_set_level(MATRIX_COLS_PINS[col], 1);
	
		// Check each row
		for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
			curState = gpio_get_level(MATRIX_ROWS_PINS[row]);

			// If the previous state was different restart the debounce
			if (prev_matrix_state[row][col] != curState) {
				prev_matrix_state[row][col] = curState;
				debounce_matrix[row][col] = execMillis;
			
			// else, if the value has been stable long enough 
			} else if ((execMillis - debounce_matrix[row][col]) > DEBOUNCE_TIME) {
				// update the status matrix
				if (matrix_state[row][col] != curState) {
					matrix_state[row][col] = curState;
				}
			}
		}

		gpio_set_level(MATRIX_COLS_PINS[col], 0);
	}

#else
	// Set a row as high.
	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		gpio_set_level(MATRIX_ROWS_PINS[row], 1);

		// Check each row
		for (uint8_t col = 0; col < MATRIX_COLS; col++) {
			curState = gpio_get_level(MATRIX_COLS_PINS[col]);
      
    // ESP_LOGI(MATRIX_TAG,"Row %d on GPIO %d is level %d", row, MATRIX_ROWS_PINS[row],gpio_get_level(MATRIX_ROWS_PINS[row]));
    //   ESP_LOGI(MATRIX_TAG,"Col %d Row %d is level %d", col, row, curState);

			// If the previous state was different restart the debounce
			if (prev_matrix_state[row][col] != curState) {
				prev_matrix_state[row][col] = curState;
				debounce_matrix[row][col] = execMillis;
			
			// else, if the value has been stable long enough 
			} else if ((execMillis - debounce_matrix[row][col]) > DEBOUNCE_TIME) {
				// update the status matrix
				if (matrix_state[row][col] != curState) {
					matrix_state[row][col] = curState;
				}
			}
		}
		gpio_set_level(MATRIX_ROWS_PINS[row], 0);
	}
#endif
}


void compose_keyboard_matrix(void){
  uint8_t rowOffset = 0;
  
  // First copy the master 
  rowOffset = MATRIX_ROWS * (KEYPAD_POSITION - 1);
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      keyboard_matrix[row + rowOffset][col] = matrix_state[row][col];
    }
  }

  // TODO add support for split keyboard
}



void log_matrix_state(){	

  printf("\n\n|===|===|===|===|===|===|\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		for (uint8_t col = 0; col < MATRIX_COLS*NUM_KEYPADS; col++) {
      printf("| %s ", ((keyboard_matrix[row][col] == PRESSED) ? "*": "\u2022"));
    }
    printf("|\n|---|---|---|---|---|---|\n");
  }

}