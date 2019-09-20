#include "add_ons.h"


void custom_keycode_manager(uint16_t keycode, uint8_t direction){

  if(keycode > CUSTOM_KEYCODES_BASE + LAYER_KEYCODES_OFFSET){ // && keycode < next chunk of special codes
    update_layout_status(keycode, direction);
  }
  
}