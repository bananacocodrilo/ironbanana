#include "layouts.h"

uint8_t active_layer = DEFAULT_LAYER_INDEX;

// uint16_t DEFAULT_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
//   {  1,   2,    3},
//   { LOWER,  RAISE,  6},
// };

// uint16_t RAISE_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
//   {  7 ,  8,  9 },
//   {XXXXXXX,XXXXXXX,_______},
// };

// uint16_t LOWER_LAYER[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = {
//   {  10 ,  11 ,  KC_3 },
//   {  LOWER,  RAISE,_______},
// };

// This should be consistent with the order in "enum layer_positions"
// const uint16_t *(LAYOUT[LAYERS_NUM])[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS]={
//   DEFAULT_LAYER,
//   RAISE_LAYER,
//   LOWER_LAYER,
// };

// This should be consistent with the order in "enum layer_positions"
const uint16_t LAYOUT[LAYERS_NUM][MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS]={
  {
    {  22,   2,    3},
    { DEFAULT, LOWER, RAISE},
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
