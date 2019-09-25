#include "main_tasks.h"

// Used to compare against current matrix state and detect changes
uint8_t prev_keyboard_matrix[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = { 0 }; 
// Stores keycodes held by each key in order to send the correct release if the layer changes
uint16_t keyboard_holds[MATRIX_ROWS][MATRIX_COLS*NUM_KEYPADS] = { 0 }; 
// Stores the report send via ble
uint8_t current_report[KEYBOARD_REPORT_LENGTH] = { 0 };
uint16_t test_current_report[KEYBOARD_REPORT_LENGTH] = { 0 };

/**
 * Sends keypress report over ble
 * TODO: Doing it
*/
void send_keypress_report(uint16_t keycode, keyboard_action type){
  keyboard_command_t cmd;
  cmd.keycode = keycode;
  cmd.type = type;
  xQueueSend(keyboard_q, &cmd, (TickType_t) 0);
  
  log_matrix_state();
}



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
 *  - Lastly update prev status
 * 
 */
void keypress_reports(void *pvParameters) {
  uint16_t keycode;

  while(1){
    uint8_t i = 0;
    
    // Scan my matrix
    scan_matrix_pins();
    // Compose the complete matrix
    compose_keyboard_matrix();

    // For each key
    for (uint8_t row = 0; row < MATRIX_ROWS && i < KEYBOARD_REPORT_LENGTH; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS*NUM_KEYPADS && i < KEYBOARD_REPORT_LENGTH; col++) {

        // Key didnt change -> skip
        if(keyboard_matrix[row][col] == prev_keyboard_matrix[row][col]){
          continue;
        
        // Key changed RELEASED -> PRESSED 
        }else if(keyboard_matrix[row][col] == PRESSED){
          keycode = LAYOUT[active_layer][row][col];
          
          // See through transparent keys
          if(keycode == KC_TRANSPARENT){
            keycode = LAYOUT[DEFAULT_LAYER_INDEX][row][col];
          }

          // Check for special functions
          if( keycode >= CUSTOM_KEYCODES_BASE && keycode <= CUSTOM_KEYCODES_LIMIT){
            custom_keycode_manager(keycode, PRESSED);

          /** Never trust final user, 
           * Check in case there are transparents in default layer.
           * TODO: Test settings on boot (layout, split keyboard ...)
           * */
          }else if(keycode != KC_TRANSPARENT){
            // This should never happen. It means I detect a second press on a key without releasing it.
            // Send a release just in case.
            if(keyboard_holds[row][col] != KC_NO){
              send_keypress_report(keyboard_holds[row][col], RELEASE);
            }
            // Send the report
            send_keypress_report(keycode, PRESS);
          } 
          // Update the hold matrix
          keyboard_holds[row][col] = keycode;

        // Key changed PRESSED -> RELEASED
        }else{
          keycode = keyboard_holds[row][col];
          keyboard_holds[row][col] = KC_NO;

          // Check for special functions
          if( keycode >= CUSTOM_KEYCODES_BASE && keycode <= CUSTOM_KEYCODES_LIMIT){
            custom_keycode_manager(keycode, RELEASED);

          // Send report and clean matrix
          }else{
            send_keypress_report(keycode, RELEASE);
          }
        }
        
        // Lastly update prev status
        prev_keyboard_matrix[row][col] = keyboard_matrix[row][col];
      } 
    }

    vTaskDelay(10);
  }
}
