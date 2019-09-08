
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <esp_log.h>
#include <esp_timer.h>
#include "keyboard_config.h"

#define SET_BIT(var,pos) (var |= 1UL << pos);
uint32_t millis();


