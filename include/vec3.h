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
        return (X == rhs.X && Y == rhs.Y);
    }

    bool operator!=(const Vec3 &rhs)
    {
        return !(X == rhs.X && Y == rhs.Y);
    }

    constexpr Vec3 operator+(const Vec3 &rhs) const
    {
        return {X + rhs.x, Y + rhs.Y};
    }

    constexpr Vec3 operator+(const int rhs) const
    {
        return {X + rhs, Y + rhs};
    }

    constexpr Vec3 &operator+=(const Vec3 &rhs)
    {
        return *this = *this + rhs;
    }

    constexpr Vec3 operator-(const Vec3 &rhs) const
    {
        return {X - rhs.x, Y - rhs.Y};
    }

    constexpr Vec3 operator-(const int rhs) const
    {
        return {X - rhs, Y - rhs};
    }

    constexpr Vec3 &operator-=(const Vec3 &rhs)
    {
        return *this = *this - rhs;
    }

    constexpr Vec3 operator*(const Vec3 &rhs) const
    {
        return {X * rhs.x, Y * rhs.Y};
    }

    constexpr Vec3 operator*(const int rhs) const
    {
        return {X * rhs, Y * rhs};
    }

    constexpr Vec3 &operator*=(const Vec3 &rhs)
    {
        return *this = *this * rhs;
    }
};

#endif