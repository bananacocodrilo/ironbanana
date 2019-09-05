
#include <stdint.h>
#include <esp_log.h>
#include <esp_timer.h>

#define SET_BIT(var,pos) (var |= 1UL << pos);

uint32_t millis();
