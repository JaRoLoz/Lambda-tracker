#include "./Bitset.hpp"

template <size_t Size>
bitset<Size>::bitset(Endian endian, std::initializer_list<bool> initialBuffer)
{
    this->m_endian = endian;
    // check if the size of the given buffer is bigger that the size of the template
    if (initialBuffer.size() > Size)
        return;
    // copy all of the given buffer elements to the bitset buffer and set the buffer index accordingly
    std::copy(initialBuffer.begin(), initialBuffer.end(), this->m_buffer);
    this->m_bufferIndex = initialBuffer.size() - 1;
}

template <size_t Size>
bitset<Size>::bitset(Endian endian, String initialBuffer)
{
    this->m_endian = endian;
    if (initialBuffer.length() != Size)
        return;
    for (size_t i = 0; i < initialBuffer.length(); i++)
        this->m_buffer[i] = initialBuffer[i] == '1';
}

template <size_t Size>
String bitset<Size>::toString(Endian requestedEndian)
{
    String accumulator = "";
    // if the requested endian type order is the same as the buffer's one
    if (this->m_endian == requestedEndian)
        // we add it as is
        for (size_t i = 0; i < this->m_bufferSize; i++)
            accumulator += this->m_buffer[i] ? '1' : '0';
    // if it's different
    else
        // we add it in reverse to match the requested order
        for (size_t i = this->m_bufferSize; i > 0; i--)
            accumulator += this->m_buffer[i - 1] ? '1' : '0';
    return accumulator;
}

template <size_t Size>
template <typename T>
T bitset<Size>::getAs()
{
    size_t accumulator = 0;
    // if the buffer's order is big-endian
    if (this->m_endian == Endian::BigEndian)
    {
        bool *reversedBuffer = new bool[this->m_bufferSize];
        std::fill_n(reversedBuffer, this->m_bufferSize, false);
        // we first convert it into little-endian order
        for (size_t i = this->m_bufferSize; i > 0; i--)
            reversedBuffer[this->m_bufferSize - i] = this->m_buffer[i - 1];
        // then we elevate 2 to the power of the position of each bit
        for (size_t i = 0; i < this->m_bufferSize; i++)
            accumulator += reversedBuffer[i] ? pow(2, i) : 0;
        // finally we free the used memory
        delete[] reversedBuffer;
    }
    // if it is little-endian
    else
        // we elevate 2 to the power of the position of each bit
        for (size_t i = 0; i < this->m_bufferSize; i++)
            this->m_buffer[i] ? accumulator += pow(2, i) : 0;
    return static_cast<T>(accumulator);
}

template <size_t Size>
void bitset<Size>::push(bool bit)
{
    if ((this->m_bufferIndex + 1) == this->m_bufferSize)
        return;
    this->m_bufferIndex++;
    this->m_buffer[this->m_bufferIndex] = bit;
}

template <size_t Size>
bool bitset<Size>::at(size_t pos)
{
    return this->m_buffer[pos];
}

template <size_t Size>
void bitset<Size>::set(size_t position, bool value)
{
    this->m_buffer[position] = value;
}

template <size_t Size>
void bitset<Size>::clear()
{
    memset(this->m_buffer, false, sizeof(this->m_buffer));
    this->m_bufferIndex = 0;
}
