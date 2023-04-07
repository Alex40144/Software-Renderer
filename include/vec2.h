#ifndef vec2_h
#define vec2_h

template <typename T>
class Vec2
{
public:
    Vec2() = default;
    constexpr Vec2(T x, T y)
        :
        x(x),
        y(y)
    {}

    T GetX() const {return x;};
    T GetY() const {return y;};
    constexpr void SetX(T x_in) {x=x_in;};
    constexpr void SetY(T y_in) {y=y_in;};
public:
    bool operator==(const Vec2& rhs){
        return (x == rhs.x && y == rhs.y);
    }

    bool operator!=(const Vec2& rhs){
        return !(x == rhs.x && y == rhs.y);
    }

    constexpr Vec2 operator+(const Vec2& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    constexpr Vec2 operator+(const int rhs) const{
        return {x + rhs, y + rhs};
    }

    constexpr Vec2& operator+=(const Vec2& rhs){
        return *this = *this + rhs;
    }

    constexpr Vec2 operator-(const Vec2& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    constexpr Vec2 operator-(const int rhs) const {
        return {x - rhs, y - rhs};
    }

    constexpr Vec2& operator-=(const Vec2& rhs){
        return *this = *this - rhs;
    }

    constexpr Vec2 operator*(const Vec2& rhs) const{
        return {x * rhs.x, y * rhs.y};
    }

    constexpr Vec2 operator*(const int rhs) const{
        return {x * rhs, y * rhs};
    }

    constexpr Vec2& operator*=(const Vec2& rhs){
        return *this = *this * rhs;
    }
private:
    T x;
    T y;
};

#endif