#pragma once
#include <OOTX/OOTX.hpp>

// class LightHouse
// {
// public:
//     LightHouse() : currentOOTX(new OOTX()) {}
// protected:
//     OOTX* currentOOTX;
// };

struct LightHouseData
{
    uint16_t firmwareVersion;
    uint16_t protocolVersion;
    uint16_t hardwareVersion;
    uint32_t uuid;
    uint8_t mode;
    float_t phase0;
    float_t phase1;
    float_t tilt0;
    float_t tilt1;
    int8_t accelX;
    int8_t accelY;
    int8_t accelZ;
};
