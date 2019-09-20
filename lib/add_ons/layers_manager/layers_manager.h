#ifndef LAYERS_MANAGER_H_
#define LAYERS_MANAGER_H_

#include <stdint.h>

#include "firmware_config.h"
#include "layouts.h"
#include "matrix.h"

void update_layout_status(uint16_t keycode, uint8_t direction);

#endif