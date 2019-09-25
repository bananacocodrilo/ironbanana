#include "layouts.h"

uint8_t active_layer = DEFAULT_LAYER_INDEX;

// This should be consistent with the order in "enum layer_positions"
const uint16_t LAYOUT[LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS]={
  {
    {  KC_LCTL , KC_TAB , KC_LSFT  },
    {  KC_I    , KC_I   , KC_I     },
  },
  {
    {  KC_R ,XXXXXXX,  KC_I },
    {XXXXXXX,XXXXXXX,  KC_L },
  },
  {
    {XXXXXXX,  KC_C,   KC_O },
    {XXXXXXX,XXXXXXX,  KC_D },
  }
};