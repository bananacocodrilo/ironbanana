#ifndef ARRAY_EXTRA_H_
#define ARRAY_EXTRA_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"

#include "keyboard_config.h"

/*
* @brief convert blob to keymap matrix, copy the data to the buffer
*/
void blob_to_key_mat(uint16_t layout_arr[MATRIX_ROWS*KEYMAP_COLS],uint16_t buffer[MATRIX_ROWS][KEYMAP_COLS]);

/*
* @brief convert keymap matrix to blob, copy the data to the buffer
*/
void key_mat_to_blob(uint16_t layout[MATRIX_ROWS][KEYMAP_COLS],uint16_t *buffer);

/*
* @brief convert string array to single string, copy the data to the buffer
*/
void str_arr_to_str(char (*layer_names)[MAX_LAYOUT_NAME_LENGTH], uint8_t layers, char **buffer);
/*
* @brief convert string to string array, copy the data to the buffer
*/
void str_to_str_arr(char *str, uint8_t layers,char ***buffer);

#endif