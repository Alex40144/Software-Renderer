#ifndef vec3_h
#define vec3_h

template <typename T>
class Vec3
{
public:
    Vec3() = default;
    constexpr Vec3(T X, T Y, T Z) : X(X),
                                    Y(Y),
                                    Z(Z)
    {
    }

    T X;
    T Y;
    T Z;

public:
    bool operator==(const Vec3 &rhs)
    {
        return (X == rhs.X && Y == rhs.Y && Z == rhs.Z);
    }

    bool operator!=(const Vec3 &rhs)
    {
        return !(X == rhs.X && Y == rhs.Y && Z == rhs.Z);
    }

    constexpr Vec3 operator+(const Vec3 &rhs) const
    {
        return {X + rhs.X, Y + rhs.Y, Z + rhs.Z};
    }

    constexpr Vec3 operator+(const int rhs) const
    {
        return {X + rhs, Y + rhs, Z + rhs};
    }

    constexpr Vec3 operator+(const float rhs) const
    {
        return {X + rhs, Y + rhs, Z + rhs};
    }

    constexpr Vec3 operator+(const double rhs) const
    {
        return {X + rhs, Y + rhs, Z + rhs};
    }

    constexpr Vec3 &operator+=(const Vec3 &rhs)
    {
        return *this = *this + rhs;
    }

    constexpr Vec3 operator-(const Vec3 &rhs) const
    {
        return {X - rhs.x, Y - rhs.Y, Z - rhs.Z};
    }

    constexpr Vec3 operator-(const int rhs) const
    {
        return {X - rhs, Y - rhs, Z - rhs};
    }

    constexpr Vec3 &operator-=(const Vec3 &rhs)
    {
        return *this = *this - rhs;
    }

    constexpr Vec3 operator*(const Vec3 &rhs) const
    {
        return {X * rhs.x, Y * rhs.Y, Z * rhs.Z};
    }

    constexpr Vec3 operator*(const int rhs) const
    {
        return {X * rhs, Y * rhs, Z * rhs};
    }

    constexpr Vec3 &operator*=(const Vec3 &rhs)
    {
        return *this = *this * rhs;
    }
};

#endif