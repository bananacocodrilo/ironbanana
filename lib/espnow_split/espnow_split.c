#include "espnow_split.h"

//Mac adress of the main device (only mac address needed for ESP-NOW)
static uint8_t master_mac_adr[6]= {0x30,0xAE,0xA4,0x5D,0xBE,0x54};

// Queue for sending esp-now reports
QueueHandle_t espnow_matrix_send_q;

QueueHandle_t espnow_recieve_q;

static esp_now_peer_info_t Peer;
static esp_now_peer_info_t *pPeer=&Peer;