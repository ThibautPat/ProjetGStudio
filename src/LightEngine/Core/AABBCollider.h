#pragma once
#include "Collider.h"

class AABBCollider : public Collider
{
public:
	AABBCollider(float xMin, float yMin, float xMax, float yMax);

	// Hérité via Collider
	bool IsColliding(Collider* pOther) override;
	void Update(float newX, float newY) override;
};

