
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <esp_log.h>
#include <esp_timer.h>
#include <nvs.h>
#include <nvs_flash.h>

#include "keyboard_config.h"

#define SET_BIT(var,pos) (var |= 1UL << pos);
uint32_t millis();

void initialize_nvs(nvs_handle memory_handle);
void load_default_config(config_data_t* config);
void load_stored_config(config_data_t* config, nvs_handle memory_handle);

