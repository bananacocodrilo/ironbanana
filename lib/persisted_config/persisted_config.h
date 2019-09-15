#ifndef NVS_HANDLER_H_
#define NVS_HANDLER_H_

#include <nvs.h>
#include <nvs_flash.h>
#include <esp_log.h>


#include "array_extra.h"
#include "keyboard_config.h"
#include "keymap.h"

#define CONFIG_TAG "CONFIG"
#define KEYMAP_NAMESPACE "keymap_config"
#define LAYOUT_NUM_KEY "layout_num"
#define LAYOUT_NAMES_KEY "layouts_name"

#define NVS_CONFIG_OK 1
#define NVS_CONFIG_ERR 0


extern uint8_t layers_num;
extern char **layer_names_arr;
extern uint16_t ***layouts;


/*
 * @initialize nvs
 */
void initialize_nvs();

/*
 * @load the keyboard config from nvs
 */
esp_err_t load_persisted_config(config_data_t* config);


void load_layers();
void load_layers_cfg();

void nvs_load_layouts(void);
void nvs_read_layout(const char* layout_name,uint16_t buffer[MATRIX_ROWS][KEYMAP_COLS]);

void load_bluetooth_name(config_data_t* config);



#endif