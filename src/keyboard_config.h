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

/** 
 * Size of the keyboard. For splits keyboards this 
 * is the size of each piece.
 * In case there are different sizes use the bigger values
 * for rows and cols and fill the unused positions with anything.
 * 
 */
#define MATRIX_ROWS 4
#define MATRIX_COLS 6

// Number of layers defined by default in keymap.c
#define LAYERS 3 

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

#define MAX_LAYOUT_NAME_LENGTH 15
#define KEYMAP_COLS MATRIX_COLS*KEYPADS


#define MACRO_LEN 3 //keys for macros

#define LAYERS_BASE_VAL 0xFF
#define LAYER_HOLD_BASE_VAL 0x123
#define LAYER_HOLD_MAX_VAL 0x134
#define MACRO_BASE_VAL 0x103


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

extern char default_layout_names[LAYERS][MAX_LAYOUT_NAME_LENGTH];





#endif /*  KEYBOARD_CONFIG_H */