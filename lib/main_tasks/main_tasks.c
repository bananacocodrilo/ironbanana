#include "main_tasks.h"

// Used to compare against current matrix state and detect changes
uint8_t prev_keyboard_matrix[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = { 0 }; 
// Stores keycodes held by each key in order to send the correct release if the layer changes
uint16_t keyboard_holds[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = { KC_UNDEFINED }; 


/**
 * Adds the keypresses to the reports queues (master pad task)
 * Function flow:
 *  - Get complete matrix
 *    - Scan matrix
 *    - TODO: Mix with last slave report 
 * 
 *  - For each key: Compare if status changed 
 *    - Didnt change: Skip
 *    - 0 to 1: 
 *      - Convert to keycode taking layer and transparencies 
 *        into account. 
 *      - Check for layer modifications (? break?)
 *      - Add keycode to held keys on position (was something there? release and print error)
 *      - Add keycode to next report
 *    - 1 to 0:
 *      - Retrieve keycode from held
 *      - Add keycode(release) to next report
 *
 */
void keypress_reports(void *pvParameters) {
  uint16_t keycode;

  while(1){
    // Scan my matrix
    scan_matrix_pins();
    log_matrix_state();
    // Compose the complete matrix
    compose_keyboard_matrix();

    // For each key
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS*NUM_KEYPADS; col++) {

        // Key didnt change -> skip
        if(keyboard_matrix[row][col] == prev_keyboard_matrix[row][col]){
          continue;
        
        // Key changed 0 -> 1
        }else if(keyboard_matrix[row][col] == 1){
          keycode = LAYOUT[active_layer][row][col];
           
          // See through transparent keys
          if(keycode == KC_TRANSPARENT){
            keycode == LAYOUT[DEFAULT_LAYER_INDEX][row][col];
          }

          // Check for special functions
          if( keycode >= CUSTOM_KEYCODES_BASE && 
              keycode <= CUSTOM_KEYCODES_LIMIT){
            // do modifier stuff

          /** Never trust final user, 
           * Check in case there are transparents in default layer.
           * TODO: Test settings on boot (layout, split keyboard ...)
           * */
          }else if(keycode != KC_TRANSPARENT){

            if(keyboard_holds[row][col] == KC_UNDEFINED){
              keyboard_holds[row][col] = keycode;
            // send keycode press to queue   

            //Detect a second press before releasing the key. Just in case since this should never happen.
            }else{
              //send release keyboard_holds[row][col]
              //keyboard_holds[row][col] == null

            }

          } 


        // Key changed 1 -> 0
        }else{

        }
      } 
    }
    vTaskDelay( 100 );
  }
}

