#include <Windows.h>
#include <iostream>
#include <math.h>
#include "GameFuncs.h"

//2D simulation of how War Thunder simulated bullets with drag

int main()
{
	GameFuncs game;

	//Example of War thunders bullet coefficient
	float bc = -0.0005f;
	float gravity = -9.81f;
	//Degrees. Needed to create a velocity.
	float launch_angle = 45.f;
	float bullet_speed = 30.f;//m/s

	vec2 bullet_position = { 0,0 };
	vec2 bullet_fire_direction = { cos(DEG2RAD(launch_angle)), sin(DEG2RAD(launch_angle)) };
	vec2 bullet_velocity = bullet_fire_direction * bullet_speed;

	for (float t = 0; t < 5.f; t += game.time_step) {
		if (bullet_position.y < -0.f)
			break;

		printf("Time: %f\nPosition [X:%2.2f || Y:%2.2f]\n\n", t, bullet_position.x, bullet_position.y);

		game.ApplyDrag(bc, bullet_velocity, bullet_position);
	}

	printf("Finished\n");
}
