#include "CircleCollider.h"
#include <SFML/System/Vector2.hpp>

CircleCollider::CircleCollider(float x, float y, float radius) : Collider(x, y, radius) {
}

bool CircleCollider::IsColliding(Collider* pOther)
{
	sf::Vector2f distance = sf::Vector2f(mX, mY) - sf::Vector2f(pOther->mX, pOther->mY);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float sqrRadius = (mRadius + pOther->mRadius) * (mRadius + pOther->mRadius);

	return sqrLength < sqrRadius;
}

void CircleCollider::Update(float newX, float newY) {
	mX = newX;
	mY = newY;
}
