#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	CircleCollider(float x, float y, float radius);

	// Hérité via Collider
	bool IsColliding(Collider* pOther) override;
	void Update(float newX, float newY) override;
};

