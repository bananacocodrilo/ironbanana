#include "main_tasks.h"

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

}