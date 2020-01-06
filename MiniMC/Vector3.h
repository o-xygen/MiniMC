#pragma once
namespace GameLogic
{
    class Vector3
    {
    public:
        double x, y, z;
        Vector3();
        Vector3(double x, double y, double z);
        Vector3 operator+(const Vector3& a)const;
        Vector3 operator-(const Vector3& a)const;
        bool operator==(const Vector3& a)const;
        bool operator<=(const Vector3& a)const;
        bool operator<(const Vector3& a)const;
        double operator[](int index)const;
        static double sqrLength(const Vector3& a);
        static double sqrDistance(const Vector3& a, const Vector3& b);
    };
}