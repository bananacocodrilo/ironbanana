#include "matrix.h"

void initialize_matrix_pins(void){
  uint8_t input_length, output_length;
  gpio_num_t* input_pins, output_pins;

  #ifdef COL2ROW
    input_length = sizeof(MATRIX_COLS_PINS)/sizeof(MATRIX_COLS_PINS[0]);
    input_pins = MATRIX_COLS_PINS;

    output_length = sizeof(MATRIX_ROWS_PINS)/sizeof(MATRIX_ROWS_PINS[0]);
    output_pins = MATRIX_ROWS_PINS;
  
  #else
    input_length = sizeof(MATRIX_COLS_PINS)/sizeof(MATRIX_COLS_PINS[0]);
    input_pins = MATRIX_COLS_PINS;

    output_length = sizeof(MATRIX_ROWS_PINS)/sizeof(MATRIX_ROWS_PINS[0]);
    output_pins = MATRIX_ROWS_PINS;
  #endif

  for(uint8_t i = 0; i < input_length; i++) {
    ESP_LOGI(MATRIX_TAG, "what: %d", input_length);
  }

}





	// for(uint8_t row=0; row < MATRIX_ROWS; row++) {

	// 	gpio_pad_select_gpio(MATRIX_ROWS_PINS[row]);
	// 	gpio_set_direction(MATRIX_ROWS_PINS[row], GPIO_MODE_INPUT_OUTPUT);
	// 	gpio_set_level(MATRIX_ROWS_PINS[row], 0);
	// 	ESP_LOGI(GPIO_TAG,"%d is level %d",MATRIX_ROWS_PINS[row],gpio_get_level(MATRIX_ROWS_PINS[row]));
	// }

	// // Initializing columns
	// for(uint8_t col=0; col < MATRIX_ROWS; col++) {

	// 	gpio_pad_select_gpio(MATRIX_COLS_PINS[col]);
	// 	gpio_set_direction(MATRIX_COLS_PINS[col], GPIO_MODE_INPUT_OUTPUT);
	// 	gpio_set_drive_capability(MATRIX_COLS_PINS[col],GPIO_DRIVE_CAP_0);
	// 	gpio_set_level(MATRIX_COLS_PINS[col], 0);

	// 	ESP_LOGI(GPIO_TAG,"%d is level %d",MATRIX_COLS_PINS[col],gpio_get_level(MATRIX_COLS_PINS[col]));
	// }