#ifndef IO_H
#define IO_H

#define FAN_PIN 12
#define HEATER_PIN 13
#define LED_PIN 14

#include <stdint.h>
#include <Arduino.h>

namespace IO {

uint8_t initialise(void);

}

#endif