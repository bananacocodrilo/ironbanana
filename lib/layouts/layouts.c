#include "layouts.h"

uint8_t active_layer = DEFAULT_LAYER_INDEX;

// This should be consistent with the order in "enum layer_positions"
const uint16_t LAYOUT[LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS]={
  {
    {  6,   2,    3},
    {  LOWER, RAISE, 4},
  },
  {
    {  7 ,  8,  9 },
    {XXXXXXX,XXXXXXX,_______},
  },
  {
    {  10 ,  11 ,  KC_3 },
    {  LOWER,  RAISE,_______},
  }
};
