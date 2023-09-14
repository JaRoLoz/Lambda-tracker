#include "Coords.hpp"

float Vector3::AngleBetween(Vector3 *uVector, Vector3 *vVector)
{
    return acosf(((*uVector) * (*vVector)) / (uVector->module() * vVector->module()));
}

float Vector3::module()
{
    return sqrt(
        powf(this->m_x, 2) + powf(this->m_y, 2) + powf(this->m_z, 2));
}

float Vector3::operator*(Vector3 otherVector)
{
    return (this->m_x * otherVector.m_x) + (this->m_y * otherVector.m_y) + (this->m_z * otherVector.m_z);
}