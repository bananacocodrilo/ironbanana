#ifndef MAIN_TASKS_H_
#define MAIN_TASKS_H_


// Config for keypress_reports
#define KP_REPORTS_TAG  "Keypress reports task"
#define KP_REPORTS_STACK_DEPTH  8192 //8KB
#define KP_REPORTS_PRIORITY 10  
#define KP_REPORTS_CORE 0

// Adds the keypresses to the reports queues
void keypress_reports(void *pvParameters);




#endif