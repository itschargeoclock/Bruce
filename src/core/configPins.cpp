#include "configPins.h"
#include "esp_mac.h"
#include "sd_functions.h"
#include <globals.h>
String getMacAddress() {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);