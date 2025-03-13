#pragma once
#include "Collider.h"
#include "SFML/System/Vector2.hpp"

class AABBCollider : public Collider
{
protected:
	sf::Vector2f mCollideFace;

public:
	AABBCollider(float xMin, float yMin, float xMax, float yMax);

	sf::Vector2f* GetCollideFace() { return &mCollideFace; }

	// Hérité via Collider
	bool IsColliding(Collider* pOther) override;
	void Update(float newX, float newY) override; //override
};

