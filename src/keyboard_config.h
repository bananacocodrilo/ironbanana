#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include <stdint.h>
#include <driver/gpio.h>


// The device's name
#define GATTS_TAG "IronBanana" 
#define MAX_BT_DEVICENAME_LENGTH 40
#define ROW2COL

// Keyboard structure 
#define MASTER
#define KEYPADS 3

#define MATRIX_ROWS 4
#define MATRIX_COLS 6



//Inactivity time before going to deep sleep
#define SLEEP_MINS 10 



/***************************************************************
 *                                                             *
 *                       Here be dragons                       *                                  
 *                                                             *
 * Here ends what you can modify without understanding what    *
 * you are doing.                                              *
 *                                                             *
 ***************************************************************/
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define SET_BIT(var,pos) (var |= 1UL << pos);

#define KEYMAP_COLS MATRIX_COLS*KEYPADS

/*
 * Pins connected to the switches matrix. 
 * Make sure to use the at least one RTC pin on cols and one on rows
 * Initialize these vars on keyboard_config.c
 */
extern const gpio_num_t MATRIX_COLS_PINS[];
extern const gpio_num_t MATRIX_ROWS_PINS[];

typedef struct config_data {
	char bt_device_name[MAX_BT_DEVICENAME_LENGTH];
} config_data_t;




#define KEYMAP_COLS MATRIX_COLS*KEYPADS  // used for a symmetrical split keyboard
#define REPORT_LEN (MOD_LED_BYTES+MACRO_LEN+MATRIX_ROWS*KEYMAP_COLS) //size of hid reports with NKRO and room for 3 key macro
#define REPORT_COUNT_BYTES (MATRIX_ROWS*KEYMAP_COLS+MACRO_LEN)




#endif /*  KEYBOARD_CONFIG_H */