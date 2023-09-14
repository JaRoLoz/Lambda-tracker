#pragma once
#include <Arduino.h>

#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(message) Serial.println("[#] - " + (String) message)
#else
    #define DEBUG_PRINT(message)
#endif