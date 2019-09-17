#ifndef KEYPRESS_HANDLES_H
#define KEYPRESS_HANDLES_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "matrix.h"

#include "keymap.h"
#include "persisted_config.h"
#include "keyboard_config.h"

#include "../lib/plugin_manager/plugins.h"
#include "../lib/plugin_manager/plugin_manager.h"
#include "../lib/hal_ble/hal_ble.h"
#include "../lib/u8g2_OLED/oled_tasks.h"

#define KEY_PRESS_TAG "KEY_PRESS"



uint16_t check_modifier(uint16_t key);

uint16_t check_led_status(uint16_t key);

void media_control_send(uint16_t keycode);

void media_control_release(uint16_t keycode);

uint32_t millis();

void layer_adjust(uint16_t keycode);

uint8_t *check_key_state(uint16_t **keymap);


#endif