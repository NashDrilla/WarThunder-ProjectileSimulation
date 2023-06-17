#include "GameFuncs.h"

float GameFuncs::GetDragConstant(float LocalPosY)
{
	const auto maxAlt = 18300.0f;
	const auto altMult = 1.225f;
	const auto clampedAlt = fmin(LocalPosY, maxAlt);
	const auto unk1 = 2.2871901e-19f, unk2 = 5.8355603e-14f,
		unk3 = 0.00000000353118f, unk4 = 0.000095938703f;
	return altMult *
		((maxAlt / std::fmax(LocalPosY, maxAlt)) *
			((((((unk1 * clampedAlt) - unk2) * clampedAlt) + unk3) *
				clampedAlt) -
				unk4) *
			clampedAlt +
			1.0f);
}

loat GameFuncs::GetBallisticCoeff(float BulletLength, float BulletMass, float BulletCaliber, float DragConstant)
{
	return -1.0f *
		(DragConstant * static_cast<float>(M_PI) * 0.5f *
			std::pow(BulletCaliber * 0.5f, 2.0f) *
			BulletLength) /
		BulletMass;
}

void GameFuncs::ApplyDrag(float BallisticCoeff, vec2& BulletVel, vec2& BulletPos)
{
	float deltaSpeed = (BallisticCoeff * this->timeStep) * BulletVel.Length();
	float velocityMult = 1.0f;
	if (deltaSpeed < 1.0f || deltaSpeed > 1.0f) {
		velocityMult = (deltaSpeed / (1.0f - deltaSpeed)) + 1.0f;
	}

	vec2 draggedVel{
	BulletVel.x * velocityMult,
	(this->gravity * this->timeStep) + (velocityMult * BulletVel.y)
	//BulletVel.z * velocityMult                                            //Z for when you transition to the game's 3D coords
	};

	BulletVel = draggedVel;

	vec2 newPos{
		(draggedVel.x * this->timeStep) + BulletPos.x,
		(draggedVel.y * this->timeStep) + BulletPos.y
		//(dragged.z * this->timeStep) + BulletPos.z                           //Z for when you transition to the game's 3D coords
	};

	BulletPos = newPos;
}
