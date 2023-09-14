#include "Emissions.hpp"

Pulse ParsePulse(uint32_t time)
{
    switch (time)
    {
    case 6000 ... 6500:
        return Pulse(false, false, false, LightEmmisions::J0);
    case 7000 ... 7500:
        return Pulse(false, false, true, LightEmmisions::K0);
    case 8000 ... 8500:
        return Pulse(false, true, false, LightEmmisions::J1);
    case 9000 ... 9500:
        return Pulse(false, true, true, LightEmmisions::K1);
    case 10000 ... 10800:
        return Pulse(true, false, false, LightEmmisions::J2);
    case 11200 ... 11800:
        return Pulse(true, false, true, LightEmmisions::K2);
    case 12200 ... 12800:
        return Pulse(true, true, false, LightEmmisions::J3);
    case 13200 ... 13800:
        return Pulse(true, true, true, LightEmmisions::K3);
    default:
        return Pulse(false, false, false, LightEmmisions::null);
    }
}