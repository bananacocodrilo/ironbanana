#ifndef MATRIX_H_
#define MATRIX_H_


#include <stdint.h>


#include <driver/rtc_io.h>

#include <esp_timer.h>
#include <esp_sleep.h>
#include <esp_log.h>


#include "keyboard_config.h"


#define GPIO_TAG "GPIO"

#define DEBOUNCE_TIME 7

extern uint8_t MATRIX_STATE[MATRIX_ROWS][MATRIX_COLS];
extern uint8_t SLAVE_MATRIX_STATE[MATRIX_ROWS][MATRIX_COLS];
extern uint8_t (*matrix_states[])[MATRIX_ROWS][MATRIX_COLS];

/*
 * @brief deinitialize rtc pins
 */
void rtc_matrix_deinit(void);

/*
 * @brief initialize rtc pins
 */
void rtc_matrix_setup(void);

/*
 * @brief initialize matrix
 */
void matrix_setup(void);

/*
 * @brief scan matrix
 */
void scan_matrix(void);

#endif /* MATRIX_H_ */
