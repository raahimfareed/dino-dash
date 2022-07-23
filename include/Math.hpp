#pragma once
template <class T>
struct vector2 {
public:
    vector2();
    vector2(T x, T y);

    T getX() const;
    T getY() const;

    void setX(T x);
    void setY(T y);

private:
    T x;
    T y;
};