#include "GameFuncs.h"

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