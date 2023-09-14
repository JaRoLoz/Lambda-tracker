#pragma once
#include <bitset>
#include <Arduino.h>

template <size_t Size>
class bitset
{
public:
    bitset() {}
protected:
    bool m_buffer[Size] = {};
};