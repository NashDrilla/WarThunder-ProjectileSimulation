#include <Windows.h>
#include <iostream>
#include <math.h>
#include "GameFuncs.h"

//2D simulation of how War Thunder simulated bullets with drag

int main()
{
	GameFuncs game;
    // Example of War thunders bullet coefficient
    float bulletCoeff = -0.0005f;
    float gravity = -9.81f;
    // Degrees. Needed to create a velocity.
    float launchAngle = 45.f;
    float bulletSpeed = 30.f; // m/s

    vec2 bulletPosition = { 0,0 };
    vec2 bulletFireDirection = { cos(DEG2RAD(launchAngle)), sin(DEG2RAD(launchAngle)) };
    vec2 bulletVelocity = bulletFireDirection * bulletSpeed;

    for (float t = 0; t < 5.f; t += game.timeStep) {
        if (bulletPosition.y < -0.f)
            break;

        printf("Time: %f\nPosition [X:%2.2f || Y:%2.2f]\n\n", t, bulletPosition.x, bulletPosition.y);

        game.ApplyDrag(bulletCoeff, bulletVelocity, bulletPosition);
    }

    printf("Finished\n");
}
