#include "utils.h"

uint32_t millis() {
	return esp_timer_get_time() / 1000;
}


/**
 * Initializes the NVS
 * 
 */
void initialize_nvs(){
	esp_err_t err_stat = nvs_flash_init();
	if (err_stat == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK (nvs_flash_erase());
		err_stat = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err_stat);
}


/**
 * Loads the default configuration
 * 
 */
void load_default_config(config_data_t* config){
	ESP_LOGE("Utils", "Load default config");
	strcpy(config->bt_device_name, GATTS_TAG);
}


/**
 * Loads the configuration stored in memory
 * 
 */

esp_err_t load_stored_config(config_data_t* config, nvs_handle* memory_handle){
	size_t max_word_length = MAX_BT_DEVICENAME_LENGTH;
	esp_err_t ret = nvs_open("config_c", NVS_READWRITE, memory_handle);

	if (ret != ESP_OK){
		ESP_LOGE("Utils", "Error opening NVS");
		return ret;
	}

	ret = nvs_get_str(*memory_handle, 
		"btname", config->bt_device_name, &max_word_length);
	if (ret != ESP_OK){
		ESP_LOGE("Utils", "Error reading Bluetooth name from NVS. Will use default.");
		return ret;
	}

	return ret;
}



// //load the layouts from nvs
// void nvs_load_layouts(void){

// 	ESP_LOGI(NVS_TAG,"Loading layouts");
// 	nvs_read_keymap_cfg();

// 	if(layers_num!=0){

// 		// set keymap layouts
// 		ESP_LOGI(NVS_TAG,"Layouts found on NVS, loading layouts");
// 		layouts = malloc(layers_num*sizeof(uint16_t**));
// 		for(uint8_t i = 0;i < layers_num; i++){
// 			uint16_t layout_buff[MATRIX_ROWS][KEYMAP_COLS] = {0};
// 			nvs_read_layout(layer_names_arr[i],layout_buff);
// 			layouts[i] = malloc(sizeof(layout_buff));
// 			ESP_LOGI(NVS_TAG,"malloc");
// 			for(uint8_t row=0; row<MATRIX_ROWS;row++){
// 				layouts[i][row] = malloc(sizeof(layout_buff[row]));
// 				for(uint8_t col=0; col<KEYMAP_COLS;col++){
// 					layouts[i][row][col] = layout_buff[row][col];
// 				}
// 			}
// 		}
// 	}else{

// 		ESP_LOGI(NVS_TAG,"Layouts not found on NVS, loading default layouts");
// 		free(layer_names_arr);
// 		layouts = malloc(LAYERS*sizeof(uint16_t**));
// 		layer_names_arr = malloc(sizeof(default_layout_names));
// 		for(uint8_t i = 0;i < LAYERS; i++){
// 			layouts[i] = malloc(sizeof( (*default_layouts)[i]));
// 			layer_names_arr[i] = malloc(sizeof(default_layout_names[i]));
// 			strcpy(layer_names_arr[i],default_layout_names[i]);
// 			for(uint8_t row=0; row<MATRIX_ROWS;row++){
// 				layouts[i][row] = malloc(sizeof( (*default_layouts[i])[row]));
// 				for(uint8_t col=0; col<KEYMAP_COLS;col++){
// 					layouts[i][row][col] = (*default_layouts[i])[row][col];
// 				}
// 			}
// 		}
// 	}

// 	//set encoder layouts
// 	if(layers_num!=0){

// 		ESP_LOGI(NVS_TAG,"Encoder layouts found on NVS, loading layouts");
// 		encoder_map = malloc(layers_num*sizeof(uint16_t*));
// 		for(uint8_t i = 0;i < layers_num; i++){
// 			uint16_t encoder_layout_buff[ENCODER_SIZE] = {0};
// 			nvs_read_encoder_layout(layer_names_arr[i],encoder_layout_buff);
// 			encoder_map[i] = malloc(sizeof(encoder_layout_buff));
// 			ESP_LOGI(NVS_TAG,"malloc");
// 			for(uint8_t key=0; key<ENCODER_SIZE;key++){
// 				encoder_map[i][key] = encoder_layout_buff[key];
// 			}
// 		}
// 	}else{

// 		ESP_LOGI(NVS_TAG,"Encoder layouts not found on NVS, loading default layouts");
// 		free(layer_names_arr);
// 		encoder_map = malloc(LAYERS*sizeof(uint16_t*));
// 		layer_names_arr = malloc(sizeof(default_layout_names));
// 		for(uint8_t i = 0;i < LAYERS; i++){
// 			encoder_map[i] = malloc(sizeof((default_encoder_map)[i]));
// 			layer_names_arr[i] = malloc(sizeof(default_layout_names[i]));
// 			strcpy(layer_names_arr[i],default_layout_names[i]);
// 			for(uint8_t key=0; key<ENCODER_SIZE;key++){
// 				encoder_map[i][key] = default_encoder_map[i][key];
// 			}
// 		}
// 	}

// 	//set slave encoder layouts
// 	if(layers_num!=0){
// 		ESP_LOGI(NVS_TAG,"Slave Encoder layouts found on NVS, loading layouts");
// 		slave_encoder_map = malloc(layers_num*sizeof(uint16_t*));
// 		for(uint8_t i = 0;i < layers_num; i++){
// 			uint16_t encoder_layout_buff[ENCODER_SIZE] = {0};
// 			nvs_read_slave_encoder_layout(layer_names_arr[i],encoder_layout_buff);
// 			encoder_map[i] = malloc(sizeof(encoder_layout_buff));
// 			ESP_LOGI(NVS_TAG,"malloc");
// 			for(uint8_t key=0; key<ENCODER_SIZE;key++){
// 				slave_encoder_map[i][key] = encoder_layout_buff[key];
// 			}
// 		}
// 	}else{

// 		ESP_LOGI(NVS_TAG,"Slave encoder layouts not found on NVS, loading default layouts");
// 		free(layer_names_arr);
// 		slave_encoder_map = malloc(LAYERS*sizeof(uint16_t*));
// 		layer_names_arr = malloc(sizeof(default_layout_names));
// 		for(uint8_t i = 0;i < LAYERS; i++){
// 			slave_encoder_map[i] = malloc(sizeof((default_encoder_map)[i]));
// 			layer_names_arr[i] = malloc(sizeof(default_layout_names[i]));
// 			strcpy(layer_names_arr[i],default_layout_names[i]);
// 			for(uint8_t key=0; key<ENCODER_SIZE;key++){
// 				slave_encoder_map[i][key] = default_slave_encoder_map[i][key];
// 			}
// 		}
// 	}