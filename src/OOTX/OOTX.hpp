#pragma once
#include <Arduino.h>
#include <Emissions/Emissions.hpp>
#include <Lighthouse/LightHouse.hpp>
#include <Config.hpp>
#include <bitset>

class OOTX
{
public:
    OOTX() : m_hasPreambleStarted(false), m_bitIndex(0), basestationData(), m_stackIndex(0) {}
    void ResetState();
    void AppendDataBit(bool bit);
    LightHouseData basestationData;
protected:
    std::bitset<17> m_bitStack;
    // std::vector<std::bitset<8>> m_byteStack;
    std::bitset<8> m_byteStack[42];
    unsigned int m_stackIndex;
    bool m_hasPreambleStarted;
    unsigned int m_bitIndex;
};