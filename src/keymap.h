/*
 * keymap.h
 *
 *  Created on: 20 Sep 2018
 *      Author: gal
 */

#ifndef MAIN_KEYMAP_H_
#define MAIN_KEYMAP_H_

#include "keyboard_config.h"
#include "key_definitions.h"
#include "keyboard_config.h"


/** 
 *  A bit different from QMK, default returns you to the first layer,
 *  LOWER and RAISE increase/lower layer by order.
 */

#define DEFAULT 0x100
#define LOWER 0x101
#define RAISE 0x102


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define MACROS_NUM 2

/* select a keycode for your macro
 * important - first macro must be initialized as MACRO_BASE_VAL
 * 
 * */

enum custom_macros {
	KC_CTRL_ALT_DELETE = MACRO_BASE_VAL, KC_ALT_F4,
};

extern uint16_t macros[MACROS_NUM][MACRO_LEN];
extern uint16_t _QWERTY[MATRIX_ROWS][KEYMAP_COLS];
extern uint16_t _NUM[MATRIX_ROWS][KEYMAP_COLS];
extern uint16_t _PLUGINS[MATRIX_ROWS][KEYMAP_COLS];




extern uint8_t current_layout;
extern uint16_t (*default_layouts[])[MATRIX_ROWS][KEYMAP_COLS];

#endif /* MAIN_KEYMAP_H_ */
