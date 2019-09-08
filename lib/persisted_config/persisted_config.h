#ifndef NVS_HANDLER_H_
#define NVS_HANDLER_H_

#include <nvs.h>
#include <nvs_flash.h>
#include <esp_log.h>

#include "utils.h"

#define CONFIG_TAG "CONFIG"
#define KEYMAP_NAMESPACE "keymap_config"
#define LAYOUT_NUM_KEY "layout_num"
#define LAYOUT_NAMES_KEY "layouts_name"

#define NVS_CONFIG_OK 1
#define NVS_CONFIG_ERR 0


/*
 * @initialize nvs
 */
void initialize_nvs();

/*
 * @load the keyboard config from nvs
 */
esp_err_t load_persisted_config(config_data_t* config);





#endif