#include "Math.hpp"

template <class T>
vector2<T>::vector2() = default;

template <class T>
vector2<T>::vector2(T x, T y)
    : x(x), y(y)
{}

template <class T>
T vector2<T>::getX() const {
    return x;
}

template <class T>
T vector2<T>::getY() const {
    return y;
}

template <class T>
void vector2<T>::setX(T x) {
    this->x = x;
}

template <class T>
void vector2<T>::setY(T y) {
    this->y = y;
}

template struct vector2<float>;
template struct vector2<int>;
