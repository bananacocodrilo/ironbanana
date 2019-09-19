#include "layouts.h"

uint8_t active_layer = DEFAULT_LAYER_INDEX;

uint16_t DEFAULT_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
  {  KC_B,   KC_A,    KC_N},
  { LOWER,  RAISE,  KC_ENT},
};

uint16_t RAISE_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
  {  KC_1 ,  KC_2 ,  KC_3 },
  {XXXXXXX,XXXXXXX,_______},
};

uint16_t LOWER_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
  {  KC_1 ,  KC_2 ,  KC_3 },
  {  LOWER,  RAISE,_______},
};

// This should be consistent with the order in "enum layer_positions"
uint16_t const (*LAYOUT[LAYERS_NUM])[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS]={
  &DEFAULT_LAYER,
  &RAISE_LAYER,
  &LOWER_LAYER
};
