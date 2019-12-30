#pragma once
namespace DataType
{
    class Vector3
    {
    public:
        double x, y, z;
        Vector3();
        Vector3(double x, double y, double z);
        Vector3 operator+(const Vector3& a);
        Vector3 operator-(const Vector3& a);
        static double sqrDistance(const Vector3& a, const Vector3& b);
    };
}