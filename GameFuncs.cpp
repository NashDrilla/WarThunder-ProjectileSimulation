#include "GameFuncs.h"

float GameFuncs::GetDragConstant(float LocalPosY)
{
    const auto max_alt = 18300.0f;
    const auto alt_mult = 1.225f;
    const auto clamped_alt = fmin(LocalPosY, max_alt);
    const auto unk_1 = 2.2871901e-19f, unk_2 = 5.8355603e-14f,
        unk_3 = 0.00000000353118f, unk_4 = 0.000095938703f;


    return alt_mult *
        ((max_alt / std::fmax(LocalPosY, max_alt)) *
            ((((((unk_1 * clamped_alt) - unk_2) * clamped_alt) + unk_3) *
                clamped_alt) -
                unk_4) *
            clamped_alt +
            1.0f);
}

float GameFuncs::GetBallisticCoeff(float BulletLength, float BulletMass, float BulletCaliber, float DragConstant)
{
    return -1.0f *
        (DragConstant * static_cast<float>(M_PI) * 0.5f *
            std::pow(BulletCaliber * 0.5f, 2.0f) *
            BulletLength) /
        BulletMass;
}

void GameFuncs::ApplyDrag(float BallisticCoeff, vec2& BulletVel, vec2& BulletPos)
{
    float delta_speed = (BallisticCoeff * this->time_step) * BulletVel.Length();
    float velocityMult = 1.0f;
    if (delta_speed < 1.0f || delta_speed > 1.0f) {
        velocityMult = (delta_speed / (1.0f - delta_speed)) + 1.0f;
    }

    vec2 dragged{
        BulletVel.x * velocityMult,
        (this->gravity * this->time_step) + (velocityMult * BulletVel.y)
        //BulletVel.z * velocityMult                                            //Z for when you transition to the game's 3D coords
    };

    BulletVel = dragged;

    vec2 new_pos{
        (dragged.x * this->time_step) + BulletPos.x,
        (dragged.y * this->time_step) + BulletPos.y
        //(dragged.z * this->time_step) + BulletPos.z                           //Z for when you transition to the game's 3D coords
    };

    BulletPos = new_pos;
}