#include <iostream>
#include <cmath>
#include <iomanip> //For formatting output

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Sim {
    //Constants
    static constexpr float timeStep = 1.f / 96.f; //Simulation time step
    static constexpr float gravity = -9.81f;      //Gravitational acceleration

    //Utility functions
    static constexpr float DEG2RAD(float x) { return x * (static_cast<float>(M_PI) / 180.f); }
    static constexpr float RAD2DEG(float x) { return x * (180.f / static_cast<float>(M_PI)); }
};

class Vec2 {
public:
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
    Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator*(float rhs) const { return Vec2(x * rhs, y * rhs); }
    Vec2 operator/(float rhs) const { return Vec2(x / rhs, y / rhs); }
    Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vec2& operator*=(float rhs) { x *= rhs; y *= rhs; return *this; }
    Vec2& operator/=(float rhs) { x /= rhs; y /= rhs; return *this; }

    float Length() const { return std::sqrt(x * x + y * y); }
};

float CalcDragConst(float LocalPosY) {
    constexpr float maxAlt = 18300.0f;
    constexpr float altMult = 1.225f;
    constexpr float unk1 = 2.2871901e-19f, unk2 = 5.8355603e-14f,
        unk3 = 3.53118e-9f, unk4 = 9.5938703e-5f;

    float clampedAlt = std::min(LocalPosY, maxAlt);
    return altMult *
        ((maxAlt / std::max(LocalPosY, maxAlt)) *
            (((((unk1 * clampedAlt - unk2) * clampedAlt + unk3) * clampedAlt) - unk4) * clampedAlt + 1.0f));
}

float CalcBallisticCoeff(float BulletLength, float BulletMass, float BulletCaliber, float DragConstant) {
    if (BulletMass == 0) {
        std::cerr << "Error: Bullet mass cannot be zero.\n";
        return 0.0f;
    }
    float crossSectionalArea = static_cast<float>(M_PI) * std::pow(BulletCaliber * 0.5f, 2);
    return -1.0f * (DragConstant * crossSectionalArea * BulletLength) / BulletMass;
}

void ApplyDrag(float BallisticCoeff, Vec2& BulletVel, Vec2& BulletPos) {
    float deltaSpeed = (BallisticCoeff * Sim::timeStep) * BulletVel.Length();
    float velocityMult = (deltaSpeed < 1.0f || deltaSpeed > 1.0f)
        ? (deltaSpeed / (1.0f - deltaSpeed)) + 1.0f
        : 1.0f;

    BulletVel = Vec2(BulletVel.x * velocityMult,
        (Sim::gravity * Sim::timeStep) + (velocityMult * BulletVel.y));
    BulletPos += BulletVel * Sim::timeStep;
}

int main() {
    float bulletCoeff = -0.0005f;
    float launchAngle = 45.f;
    float bulletSpeed = 150.f;

    Vec2 bulletPosition(0, 0);
    Vec2 bulletFireDirection(std::cos(Sim::DEG2RAD(launchAngle)), std::sin(Sim::DEG2RAD(launchAngle)));
    Vec2 bulletVelocity = bulletFireDirection * bulletSpeed;

    std::cout << std::setw(10) << "Time"
        << std::setw(15) << "Position X"
        << std::setw(15) << "Position Y" << '\n';
    std::cout << std::string(40, '-') << '\n';

    //Simulate 5 seconds of projectile movement applying a tick of drag
    //In every simulation step
    for (float t = 0; t < 5.f; t += Sim::timeStep) {
        if (bulletPosition.y < 0.f) break;

        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << t
            << std::setw(15) << bulletPosition.x
            << std::setw(15) << bulletPosition.y << '\n';

        ApplyDrag(bulletCoeff, bulletVelocity, bulletPosition);
    }

    std::cout << "Simulation finished.\n";
    return 0;
}
