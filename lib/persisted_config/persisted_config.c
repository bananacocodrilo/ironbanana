#include "persisted_config.h"

nvs_handle config_handle;
nvs_handle keymap_handle;
nvs_handle encoder_handle;
nvs_handle slave_encoder_handle;


char **layer_names_arr;
uint8_t layers_num=0;
uint16_t ***layouts;


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
 * Load the keyboard configuration from nvs. 
 * 
 * If some configuration is not found on nvs the default value is loaded instead.
*/

esp_err_t load_persisted_config(config_data_t* config){
	esp_err_t ret = nvs_open("config_c", NVS_READWRITE, &config_handle);

	if (ret != ESP_OK){
		ESP_LOGE("Utils", "Error opening NVS");
		return ret;
	}

	load_bluetooth_name(config);

	load_layers_cfg();
	load_layers();
	
	return ret;
}



/**
 * If there are layers stored on memory loads them. 
 * If there aren't any, load the default layers.
 * 
*/

void load_layers(){
	if(layers_num > 0){
		ESP_LOGI(CONFIG_TAG, "Loading layouts found on NVS");
		
		layouts = malloc(layers_num*sizeof(uint16_t**));
		// For each layout		
		for(uint8_t i = 0;i < layers_num; i++){
			uint16_t layout_buff[MATRIX_ROWS][KEYMAP_COLS] = {0};
		
			nvs_read_layout(layer_names_arr[i],layout_buff);
			
			layouts[i] = malloc(sizeof(layout_buff));
			
			// For each row
			for(uint8_t row=0; row<MATRIX_ROWS; row++){
				layouts[i][row] = malloc(sizeof(layout_buff[row]));
				
				// For each key	
				for(uint8_t col=0; col<KEYMAP_COLS;col++){
					layouts[i][row][col] = layout_buff[row][col];
				}
			}
		}

	}else{

		ESP_LOGI(CONFIG_TAG, "No layouts found on NVS, loading default.");

		layouts = malloc(LAYERS*sizeof(uint16_t**));
		layer_names_arr = malloc(sizeof(default_layout_names));

		for(uint8_t i = 0;i < LAYERS; i++){

			layouts[i] = malloc(sizeof( (*default_layouts)[i]));
			layer_names_arr[i] = malloc(sizeof(default_layout_names[i]));
			strcpy(layer_names_arr[i],default_layout_names[i]);

			for(uint8_t row=0; row<MATRIX_ROWS;row++){
				layouts[i][row] = malloc(sizeof( (*default_layouts[i])[row]));
				
				for(uint8_t col=0; col<KEYMAP_COLS;col++){
					layouts[i][row][col] = (*default_layouts[i])[row][col];
				}
			}
		}
	}
}


/**
 * Loads the number of layer and its names.
 * 
*/

void load_layers_cfg(){
	esp_err_t err;

	uint8_t layers;
	size_t str_size;
	char* layer_names;

	// Clean current layers	
	free(layer_names_arr);

	// Open the memory handle
	ESP_LOGI(CONFIG_TAG,"Opening keymap handle");
	err = nvs_open(KEYMAP_NAMESPACE, NVS_READWRITE, &keymap_handle);
 
	if (err != ESP_OK) {
		ESP_LOGE(CONFIG_TAG,"Error (%s) opening keymap handle!\n", esp_err_to_name(err));
	} else {
		ESP_LOGI(CONFIG_TAG,"Keymap Handle opened successfully");
	}

	// Get the number of layouts
	err = nvs_get_u8(keymap_handle, LAYOUT_NUM_KEY, &layers);
	if (err != ESP_OK) {
		ESP_LOGE(CONFIG_TAG, "Error getting layout num: %s", esp_err_to_name(err));
	} else{
		ESP_LOGI(CONFIG_TAG, "Success getting layout num");
	}

	// Get the length of the layouts' names
	err = nvs_get_str(keymap_handle, LAYOUT_NAMES_KEY, NULL, &str_size);
	if (err != ESP_OK) {
		ESP_LOGI(CONFIG_TAG, "Error getting layout names size: %s", esp_err_to_name(err));
	}

	// Alloc space for the names and read them
	layer_names = (char *)malloc(str_size);
	err = nvs_get_str(keymap_handle, LAYOUT_NAMES_KEY, layer_names, &str_size);
	
	if (err != ESP_OK) {
		ESP_LOGE(CONFIG_TAG, "Error getting layout name: %s", esp_err_to_name(err));
	} else{
		ESP_LOGI(CONFIG_TAG, "Success getting layout name");
		
		// Save amount of layers and its names to global
		layers_num=layers;
		str_to_str_arr(layer_names,layers,&layer_names_arr);

		for(uint8_t i=0;i<layers_num;i++){
			ESP_LOGI(CONFIG_TAG,"\nLayer %d:  %s",i,layer_names_arr[i]);
		}
	}
	nvs_close(keymap_handle);
}



/**
 * Try to load device's bt name from nvs, if it fails it loads the default instead
 * 
 */
void load_bluetooth_name(config_data_t* config){
	size_t max_word_length = MAX_BT_DEVICENAME_LENGTH;

	esp_err_t ret = nvs_get_str(config_handle, 
		"btname", config->bt_device_name, &max_word_length);
	
	if (ret != ESP_OK){
		ESP_LOGE("Utils", "Error reading Bluetooth name from NVS. Will use default.");
		strcpy(config->bt_device_name, GATTS_TAG);
	}
}




/**
 * Loads the layouts stored in memory
 * 
 */
void nvs_load_layouts(void){

	ESP_LOGI(CONFIG_TAG,"Loading layouts");
	load_layers_cfg();

	if(layers_num!=0){

		// set keymap layouts
		ESP_LOGI(CONFIG_TAG,"Layouts found on NVS, loading layouts");
		layouts = malloc(layers_num*sizeof(uint16_t**));
		for(uint8_t i = 0;i < layers_num; i++){
			uint16_t layout_buff[MATRIX_ROWS][KEYMAP_COLS] = {0};
			nvs_read_layout(layer_names_arr[i],layout_buff);
			layouts[i] = malloc(sizeof(layout_buff));
			ESP_LOGI(CONFIG_TAG,"malloc");
			for(uint8_t row=0; row<MATRIX_ROWS;row++){
				layouts[i][row] = malloc(sizeof(layout_buff[row]));
				for(uint8_t col=0; col<KEYMAP_COLS;col++){
					layouts[i][row][col] = layout_buff[row][col];
				}
			}
		}
	}else{

		ESP_LOGI(CONFIG_TAG,"Layouts not found on NVS, loading default layouts");
		free(layer_names_arr);
		layouts = malloc(LAYERS*sizeof(uint16_t**));
		layer_names_arr = malloc(sizeof(default_layout_names));
		for(uint8_t i = 0;i < LAYERS; i++){
			layouts[i] = malloc(sizeof( (*default_layouts)[i]));
			layer_names_arr[i] = malloc(sizeof(default_layout_names[i]));
			strcpy(layer_names_arr[i],default_layout_names[i]);
			for(uint8_t row=0; row<MATRIX_ROWS;row++){
				layouts[i][row] = malloc(sizeof( (*default_layouts[i])[row]));
				for(uint8_t col=0; col<KEYMAP_COLS;col++){
					layouts[i][row][col] = (*default_layouts[i])[row][col];
				}
			}
		}
	}
}




/**
 * Reads a layout stored in memory
 * 
 */
void nvs_read_layout(const char* layout_name,uint16_t buffer[MATRIX_ROWS][KEYMAP_COLS]){
	size_t arr_size;
	uint16_t layout[MATRIX_ROWS][KEYMAP_COLS] = {0};
	uint16_t layout_arr[MATRIX_ROWS*KEYMAP_COLS] = {0};
	esp_err_t err = nvs_open(KEYMAP_NAMESPACE, NVS_READWRITE, &keymap_handle);

	if (err != ESP_OK) {
		ESP_LOGE(CONFIG_TAG,"Error (%s) opening NVS handle!\n", esp_err_to_name(err));
	} else {
		ESP_LOGI(CONFIG_TAG,"NVS Handle opened successfully");
	}
	
	//get blob array size
	err = nvs_get_blob(keymap_handle, layout_name, NULL, &arr_size);
	err = nvs_get_blob(keymap_handle,layout_name,layout_arr,&arr_size);
	if (err != ESP_OK) {
		ESP_LOGE(CONFIG_TAG, "Error getting layout: %s", esp_err_to_name(err));
	}else{
		ESP_LOGI(CONFIG_TAG, "Success getting layout");
		blob_to_key_mat(layout_arr,layout);
	}

	memcpy(buffer, layout, sizeof(layout) );
	ESP_LOGI(CONFIG_TAG, "Layout copied to buffer");
	nvs_close(keymap_handle);
}