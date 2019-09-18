#include "main_tasks.h"

uint8_t prev_keyboard_matrix[MATRIX_ROWS*NUM_KEYPADS][MATRIX_COLS] = { 0 }; 
uint8_t keyboard_holds[MATRIX_ROWS*NUM_KEYPADS][MATRIX_COLS] = { 0 }; 


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
  while(1){
    // Scan my matrix
    scan_matrix_pins();
    log_matrix_state();
    // Compose the complete matrix
    compose_keyboard_matrix();

    // For each key
    for (uint8_t row = 0; row < MATRIX_ROWS*NUM_KEYPADS; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        // Key didnt change -> skip
        if(keyboard_matrix[row][col] == prev_keyboard_matrix[row][col]){
          continue;
        
        // Key changed 0 -> 1
        }else if(keyboard_matrix[row][col]){
          // keycode = layout[active_layer][row][col]
          // if keycode == transparente
            // keycode == layout[active_layer][row][col]

          // if keycode == modifier
            // do modifier stuff

          // if keycode != transparente
            // if keyboard_holds[row][col] != null
              //send release keyboard_holds[row][col]
              //keyboard_holds[row][col] == null

            // keyboard_holds[row][col] = keycode 
            // send keycode press to queue        
        }else{

        }
      } 
    }
    vTaskDelay( 100 );
  }
}

