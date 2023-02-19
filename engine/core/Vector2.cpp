#include "Vector2.h"

#include <math.h>

Vector2 Vector2::ZERO = Vector2(0, 0);

// code copied from here: https://codereview.stackexchange.com/questions/5856/mathematical-vector2-class-implementation

//CONSTRUCTORS
Vector2::Vector2(const Vector2 & v) : x(v.x), y(v.y) { }
Vector2::Vector2(const Vector2 * v) : x(v->x), y(v->y) { }

//METHODS
void Vector2::set(float xValue, float yValue) { x = xValue; y = yValue; }

float Vector2::length() const { return sqrt(x * x + y * y); }
float Vector2::lengthSquared() const { return x * x + y * y; }
float Vector2::distance(const Vector2 & v) const { return sqrt(((x - v.x) * (x -     v.x)) + ((y - v.y) * (y - v.y))); }
float Vector2::distanceSquared(const Vector2 & v) const { return ((x - v.x) * (x -     v.x)) + ((y - v.y) * (y - v.y)); }
float Vector2::dot(const Vector2 & v) const { return x * v.x + y * v.y; }
float Vector2::cross(const Vector2 & v) const { return x * v.y + y * v.x; }

Vector2 & Vector2::normal() { set(-y, x); return *this; }

Vector2 & Vector2::normalize()
{
    if(length() != 0)
    {
        float length = lengthSquared();
        x /= length; y /= length;
        return *this;
    }

    x = y = 0;
    return *this;
}