#pragma once
#include <Arduino.h>

enum LightEmmisions
{
    J0,
    K0,
    J1,
    K1,
    J2,
    K2,
    J3,
    K3,
    null
};

struct Pulse
{
    bool skip;
    bool data;
    bool axis;
    LightEmmisions emissionType;

    Pulse(bool _skip, bool _data, bool _axis, LightEmmisions _emissionType) : skip(_skip), data(_data), axis(_axis), emissionType(_emissionType) {}
};

Pulse ParsePulse(uint32_t time);