#include "../../src/interface.h"
#include <Arduino.h>
#include "pins_arduino.h"

void _setup_gpio() {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

int getBattery() {
    return 100;
}

bool isCharging() { return false; }

void _setBrightness(uint8_t brightval) {
    analogWrite(TFT_BL, (brightval * 255) / 100);
}

void InputHandler(void) {
}

void powerOff() {}
void checkReboot() {}
