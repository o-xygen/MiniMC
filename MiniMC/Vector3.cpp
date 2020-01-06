#include "Vector3.h"

namespace GameLogic
{
    Vector3::Vector3() :x(0), y(0), z(0)
    {

    }
    Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
    {

    }
    Vector3 Vector3::operator+(const Vector3& a)const
    {
        return Vector3{ x + a.x,y + a.y,z + a.z };
    }
    Vector3 Vector3::operator-(const Vector3& a)const
    {
        return Vector3{ x - a.x,y - a.y,z - a.z };
    }
    bool Vector3::operator==(const Vector3& a)const
    {
        return x == a.x && y == a.y && z == a.z;
    }
    bool Vector3::operator<=(const Vector3& a)const
    {
        return x <= a.x && y <= a.y && z <= a.z;
    }
    bool Vector3::operator<(const Vector3& a)const
    {
        return x < a.x || y < a.y || z < a.z;
    }
    inline double Vector3::operator[](int index)const
    {
        return index == 0 ? x : index == 1 ? y : z;
    }
    double Vector3::sqrLength(const Vector3& a)
    {
        return a.x * a.x + a.y * a.y + a.z * a.z;
    }
    double Vector3::sqrDistance(const Vector3& a, const Vector3& b)
    {
        double sqrtX = a.x - b.x;
        double sqrtY = a.y - b.y;
        double sqrtZ = a.z - b.z;
        return sqrtX * sqrtX + sqrtY * sqrtY + sqrtZ * sqrtZ;
    }

}
