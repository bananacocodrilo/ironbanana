#ifndef LAYOUTS_H_
#define LAYOUTS_H_

#include "firmware_config.h"
#include "key_definitions.h"

// Fillers to make layouts easier to read
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// More than 3 layouts are not currently supported
#define LAYERS_NUM 3

/** 
 * Following defines are used to declare special keycodes for internal usage
 * 0x00-0xA4 hold the normal keys, 0xA4-0xDF are reserved on QMK so will be avoided
 * to help compatibility.
 * I'm going to follow the IP approach and reserve a chunk for myself
 * */ 
#define CUSTOM_KEYCODES_BASE 0xE0 
#define CUSTOM_KEYCODES_LIMIT 0xF0 
#define LAYER_KEYCODES_OFFSET 0

enum layer_codes {
  DEFAULT = CUSTOM_KEYCODES_BASE + LAYER_KEYCODES_OFFSET,
  RAISE,
  LOWER
};

enum layer_positions {
  DEFAULT_LAYER_INDEX = 0,
  RAISE_LAYER_INDEX,
  LOWER_LAYER_INDEX
};

extern uint8_t active_layer;
extern const uint16_t LAYOUT[LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS];
// extern uint16_t const (*LAYOUT[LAYERS_NUM])[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS];

#endif