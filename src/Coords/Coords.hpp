#pragma once
#include <Arduino.h>

class Vector3
{
public:
    static float AngleBetween(Vector3 *uVector, Vector3 *vVector);
    Vector3(float_t x, float_t y, float_t z) : m_x(x), m_y(y), m_z(z) {}
    float module();
    float operator*(Vector3 otherVector);

private:
    float_t m_x;
    float_t m_y;
    float_t m_z;
};