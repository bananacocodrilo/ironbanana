#ifndef MATRIX_C
#define MATRIX_C

#include "matrix.h"



uint8_t curState = 0;
uint32_t lastDebounceTime = 0;
uint32_t DEBOUNCE_MATRIX[MATRIX_ROWS][MATRIX_COLS] = { 0 };
uint32_t PREV_MATRIX_STATE[MATRIX_ROWS][MATRIX_COLS] = { 0 };

uint8_t MATRIX_STATE[MATRIX_ROWS][MATRIX_COLS] = { 0 };
uint8_t SLAVE_MATRIX_STATE[MATRIX_ROWS][MATRIX_COLS] = { 0 };
uint8_t (*matrix_states[])[MATRIX_ROWS][MATRIX_COLS] = { &MATRIX_STATE, &SLAVE_MATRIX_STATE, };






/** 
 * Deinitializes the rtc pins after deep-sleep
*/
void rtc_matrix_deinit(void) {
	for (uint8_t col = 0; col < MATRIX_COLS; col++) {
		if (rtc_gpio_is_valid_gpio(MATRIX_COLS_PINS[col]) == 1) {
			rtc_gpio_set_level(MATRIX_COLS_PINS[col], 0);
			rtc_gpio_set_direction(MATRIX_COLS_PINS[col], RTC_GPIO_MODE_DISABLED);
			gpio_reset_pin(MATRIX_COLS_PINS[col]);
		}
	}

	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		if (rtc_gpio_is_valid_gpio(MATRIX_ROWS_PINS[row]) == 1) {
			rtc_gpio_set_level(MATRIX_ROWS_PINS[row], 0);
			rtc_gpio_set_direction(MATRIX_ROWS_PINS[row], RTC_GPIO_MODE_DISABLED);
			gpio_reset_pin(MATRIX_ROWS_PINS[row]);
		}
	}
}


/** 
 * Initializes the rtc pins for deep-sleep
*/
void rtc_matrix_setup(void) {
	uint64_t rtc_mask = 0;

	for (uint8_t col = 0; col < MATRIX_COLS; col++) {
		if (rtc_gpio_is_valid_gpio(MATRIX_COLS_PINS[col]) == 1) {
			rtc_gpio_init((MATRIX_COLS_PINS[col]));
			rtc_gpio_set_direction(MATRIX_COLS_PINS[col], RTC_GPIO_MODE_INPUT_OUTPUT);
			rtc_gpio_set_level(MATRIX_COLS_PINS[col], 1);

			ESP_LOGI(GPIO_TAG,"%d is level %d", MATRIX_COLS_PINS[col],
					gpio_get_level(MATRIX_COLS_PINS[col]));
		}
	}

	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		if (rtc_gpio_is_valid_gpio(MATRIX_ROWS_PINS[row]) == 1) {
			rtc_gpio_init((MATRIX_ROWS_PINS[row]));
			rtc_gpio_set_direction(MATRIX_ROWS_PINS[row], RTC_GPIO_MODE_INPUT_OUTPUT);

			rtc_gpio_set_drive_capability(MATRIX_ROWS_PINS[row], GPIO_DRIVE_CAP_0);
			rtc_gpio_set_level(MATRIX_ROWS_PINS[row], 0);

			rtc_gpio_wakeup_enable(MATRIX_ROWS_PINS[row], GPIO_INTR_HIGH_LEVEL);
			SET_BIT(rtc_mask, MATRIX_ROWS_PINS[row]);

			ESP_LOGI(GPIO_TAG,"%d is level %d", MATRIX_ROWS_PINS[row], 
					gpio_get_level(MATRIX_ROWS_PINS[row]));
		}
		esp_sleep_enable_ext1_wakeup(rtc_mask, ESP_EXT1_WAKEUP_ANY_HIGH);
	}
}


/** 
 * Initializes the matrix pins
*/
void matrix_setup(void) {

#ifdef COL2ROW
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

#else
	// Initializing rows
	for(uint8_t row=0; row < MATRIX_ROWS; row++) {

		gpio_pad_select_gpio(MATRIX_ROWS_PINS[row]);
		gpio_set_direction(MATRIX_ROWS_PINS[row], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_level(MATRIX_ROWS_PINS[row], 0);
		ESP_LOGI(GPIO_TAG,"%d is level %d",MATRIX_ROWS_PINS[row],gpio_get_level(MATRIX_ROWS_PINS[row]));
	}

	// Initializing columns
	for(uint8_t col=0; col < MATRIX_ROWS; col++) {

		gpio_pad_select_gpio(MATRIX_COLS_PINS[col]);
		gpio_set_direction(MATRIX_COLS_PINS[col], GPIO_MODE_INPUT_OUTPUT);
		gpio_set_drive_capability(MATRIX_COLS_PINS[col],GPIO_DRIVE_CAP_0);
		gpio_set_level(MATRIX_COLS_PINS[col], 0);

		ESP_LOGI(GPIO_TAG,"%d is level %d",MATRIX_COLS_PINS[col],gpio_get_level(MATRIX_COLS_PINS[col]));
	}
#endif
}







void scan_matrix(void) {
#ifdef COL2ROW
	// Setting column pin as low, and checking if the input of a row pin changes.
	for (uint8_t col = 0; col < MATRIX_COLS; col++) {
		gpio_set_level(MATRIX_COLS_PINS[col], 1);
		for (uint8_t row = 0; row < MATRIX_ROWS; row++) {

			curState = gpio_get_level(MATRIX_ROWS_PINS[row]);
			if (PREV_MATRIX_STATE[row][col] != curState) {
				DEBOUNCE_MATRIX[row][col] = millis();
			}
			PREV_MATRIX_STATE[row][col] = curState;
			if ((millis() - DEBOUNCE_MATRIX[row][col]) > DEBOUNCE_TIME) {

				if (MATRIX_STATE[row][col] != curState) {
					MATRIX_STATE[row][col] = curState;
				}

			}
		}
		gpio_set_level(MATRIX_COLS_PINS[col], 0);
	}

#else
	// Setting row pin as low, and checking if the input of a column pin changes.
	for(uint8_t row=0; row < MATRIX_ROWS; row++) {
		gpio_set_level(MATRIX_ROWS_PINS[row], 1);

		for(uint8_t col=0; col <MATRIX_COLS; col++) {
			curState = gpio_get_level(MATRIX_ROWS_PINS[row]);
			
      		if( PREV_MATRIX_STATE[row][col] != curState) {
				DEBOUNCE_MATRIX[row][col] = millis();
			}
			PREV_MATRIX_STATE[row][col] = curState;
			
			if( (millis() - DEBOUNCE_MATRIX[row][col]) > DEBOUNCE_TIME) {
				if( MATRIX_STATE[row][col] != curState) {
					MATRIX_STATE[row][col] = curState;
				}
			}

		}
		gpio_set_level(MATRIX_ROWS_PINS[row], 0);
	}
#endif

}





#endif /* MATRIX_C */