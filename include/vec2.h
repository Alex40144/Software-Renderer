#ifndef vec2_h
#define vec2_h

template <typename T>
class Vec2
{
public:
    Vec2() = default;
    constexpr Vec2(T X, T Y) : X(X), Y(Y)
    {
    }

    T X;
    T Y;

public:
    bool operator==(const Vec2 &rhs)
    {
        return (X == rhs.X && Y == rhs.Y);
    }

    bool operator!=(const Vec2 &rhs)
    {
        return !(X == rhs.X && Y == rhs.Y);
    }

    constexpr Vec2 operator+(const Vec2 &rhs) const
    {
        return {X + rhs.x, Y + rhs.Y};
    }

    constexpr Vec2 operator+(const int rhs) const
    {
        return {X + rhs, Y + rhs};
    }

    constexpr Vec2 &operator+=(const Vec2 &rhs)
    {
        return *this = *this + rhs;
    }

    constexpr Vec2 operator-(const Vec2 &rhs) const
    {
        return {X - rhs.x, Y - rhs.Y};
    }

    constexpr Vec2 operator-(const int rhs) const
    {
        return {X - rhs, Y - rhs};
    }

    constexpr Vec2 &operator-=(const Vec2 &rhs)
    {
        return *this = *this - rhs;
    }

    constexpr Vec2 operator*(const Vec2 &rhs) const
    {
        return {X * rhs.x, Y * rhs.Y};
    }

    constexpr Vec2 operator*(const int rhs) const
    {
        return {X * rhs, Y * rhs};
    }

    constexpr Vec2 &operator*=(const Vec2 &rhs)
    {
        return *this = *this * rhs;
    }
};

#endif