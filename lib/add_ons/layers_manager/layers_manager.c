#include "layers_manager.h"

void update_layout_status(uint16_t keycode, uint8_t direction){

  switch (keycode){

    case DEFAULT:
      active_layer = DEFAULT_LAYER_INDEX;
      break;

    case RAISE:
      if(direction == PRESSED){
        active_layer = RAISE_LAYER_INDEX;
      }else{
        active_layer = DEFAULT_LAYER_INDEX;
      }
    break;

    case LOWER:
      if(direction == PRESSED){
        active_layer = LOWER_LAYER_INDEX;
      }else{
        active_layer = DEFAULT_LAYER_INDEX;
      }
    break;

    default:
      break;
  }

}
