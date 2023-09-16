#pragma once
#include <Arduino.h>
#include <initializer_list>
#include <algorithm>

enum Endian
{
    BigEndian,
    LittleEndian
};

template <size_t Size>
class bitset
{
public:
    bitset(Endian endian) : m_endian(endian) {}
    bitset(Endian endian, std::initializer_list<bool> initialBuffer);
    bitset(Endian endian, String initialBuffer);

    String toString(Endian requestedEndian);
    template <typename T>
    T getAs();
    void push(bool bit);
    bool at(unsigned int pos);
    String slice(unsigned int startPos, unsigned int endPos);
    void clear();

protected:
    size_t m_bufferIndex = 0;
    size_t m_bufferSize = Size;
    bool m_buffer[Size] = {};
    Endian m_endian;
};
