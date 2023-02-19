#pragma once
#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2() {};
    Vector2(float _x, float _y) : x(_x), y(_y) {};
    Vector2(const Vector2 & v);
    Vector2(const Vector2 * v);
	

    static Vector2 ZERO;
    float x;
	float y;

    void set(float xValue, float yValue);

    float length() const;
    float lengthSquared() const;
    float distance(const Vector2 & v) const;
    float distanceSquared(const Vector2 & v) const;
    float dot(const Vector2 & v) const;
    float cross(const Vector2 & v) const;

    Vector2 & normal();
    Vector2 & normalize();    

    // Code from: https://codereview.stackexchange.com/questions/5856/mathematical-vector2-class-implementation
    //ASSINGMENT AND EQUALITY OPERATIONS
    inline Vector2 & operator = (const Vector2 & v) { x = v.x; y = v.y; return *this; }
    inline Vector2 & operator = (const float & f) { x = f; y = f; return *this; }
    inline Vector2 & operator - (void) { x = -x; y = -y; return *this; }
    inline bool operator == (const Vector2 & v) const { return (x == v.x) && (y == v.y); }
    inline bool operator != (const Vector2 & v) const { return (x != v.x) || (y != v.y); }

    //VECTOR2 TO VECTOR2 OPERATIONS
    inline const Vector2 operator + (const Vector2 & v) const { return Vector2(x + v.x, y + v.y); }
    inline const Vector2 operator - (const Vector2 & v) const { return Vector2(x - v.x, y - v.y); }
    inline const Vector2 operator * (const Vector2 & v) const { return Vector2(x * v.x, y * v.y); }
    inline const Vector2 operator / (const Vector2 & v) const { return Vector2(x / v.x, y / v.y); }

    //VECTOR2 TO THIS OPERATIONS
    inline Vector2 & operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
    inline Vector2 & operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
    inline Vector2 & operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
    inline Vector2 & operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

    //SCALER TO VECTOR2 OPERATIONS
    inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
    inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
    inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
    inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

    //SCALER TO THIS OPERATIONS
    inline Vector2 &  operator += (float v) { x += v; y += v; return *this; }
    inline Vector2 & operator -= (float v) { x -= v; y -= v; return *this; }
    inline Vector2 & operator *= (float v) { x *= v; y *= v; return *this; }
    inline Vector2 & operator /= (float v) { x /= v; y /= v; return *this; }

};

#endif //VECTOR2_H
