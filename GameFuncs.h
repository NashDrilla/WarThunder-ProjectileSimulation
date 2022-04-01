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
    
    float GetDragConstant(float localPlayerPosY)
    {
        const auto max_alt = 18300.0f;
        const auto alt_mult = 1.225f;
        const auto clamped_alt = fmin(localPlayerPosY, max_alt);
        const auto unk_1 = 2.2871901e-19f, unk_2 = 5.8355603e-14f,
            unk_3 = 0.00000000353118f, unk_4 = 0.000095938703f;


        return alt_mult *
            ((max_alt / std::fmax(localPlayerPosY, max_alt)) *
                ((((((unk_1 * clamped_alt) - unk_2) * clamped_alt) + unk_3) *
                    clamped_alt) -
                    unk_4) *
                clamped_alt +
                1.0f);
    }

    
    float GetBallisticCoeff(float bulletLength, float bulletMass, float bulletCaliber, float DragConstant)
    {
        return -1.0f *
            (DragConstant * static_cast<float>(M_PI) * 0.5f *
                std::pow(bulletCaliber * 0.5f, 2.0f) *
                bulletLength) /
            bulletMass;
    }

    //Apply a tick of drag to the projectile and return the new position
    void ApplyDrag(float BallisticCoeff, vec2& BulletVel, vec2& BulletPos);

    //War thunders tick rate
    float time_step = 1.f / 96.f;
    float gravity = -9.81;
private:
    
};