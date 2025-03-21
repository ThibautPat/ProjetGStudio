#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:

	CircleCollider(float x, float y, float radius);
	bool IsColliding(Collider* pOther, bool rigidBody = true) override;
	void Update(float newX, float newY) override;
};
