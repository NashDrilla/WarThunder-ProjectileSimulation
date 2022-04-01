#pragma once
#include <iostream>
#include <math.h>

#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )

class vec2
{
public:
    float x, y;

    vec2() { x = y = 0; }
    vec2(const float x, const float y) : x(x), y(y) {}
    vec2 operator + (const vec2& rhs) const { return vec2(x + rhs.x, y + rhs.y); }
    vec2 operator - (const vec2& rhs) const { return vec2(x - rhs.x, y - rhs.y); }
    vec2 operator * (const float& rhs) const { return vec2(x * rhs, y * rhs); }
    vec2 operator / (const float& rhs) const { return vec2(x / rhs, y / rhs); }
    vec2& operator += (const vec2& rhs) { return *this = *this + rhs; }
    vec2& operator -= (const vec2& rhs) { return *this = *this - rhs; }
    vec2& operator *= (const float& rhs) { return *this = *this * rhs; }
    vec2& operator /= (const float& rhs) { return *this = *this / rhs; }
    float operator[](int i) const {
        return ((float*)this)[i];
    }

    float& operator[](int i);
    float dot() const { return x * x + y * y; }
    float Length() const { return sqrtf(dot()); }
};

class GameFuncs
{
public:
    
    float GetDragConstant(float LocalPosY);
    
    float GetBallisticCoeff(float BulletLength, float BulletMass, float BulletCaliber, float DragConstant);

    //Apply a tick of drag to the projectile and return the new position
    void ApplyDrag(float BallisticCoeff, vec2& BulletVel, vec2& BulletPos);

    //War thunders tick rate
    float time_step = 1.f / 96.f;
    float gravity = -9.81;
private:
    
};