#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#define USB_VID 0x303a
#define USB_PID 0x1001

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t SDA = 8;
static const uint8_t SCL = 9;

static const uint8_t SS    = 17;
static const uint8_t MOSI  = 35;
static const uint8_t MISO  = 37;
static const uint8_t SCK   = 36;

#define TFT_BL 7
#define TFT_RST -1
#define TFT_DC 16
#define TFT_CS 17

#define TOUCH_CS 18

#define RADIO_SCK 12
#define RADIO_MOSI 11
#define RADIO_MISO 13

#define CC1101_CS 5
#define CC1101_GDO0 6
#define CC1101_GDO2 3

#define NRF24_1_CSN 4
#define NRF24_1_CE 15
#define NRF24_2_CSN 48
#define NRF24_2_CE 47
#define NRF24_3_CSN 21
#define NRF24_3_CE 14

#define SDCARD_CS 10

#define NEOPIXEL_PIN 1
#define BUZZER_PIN 2

#endif
