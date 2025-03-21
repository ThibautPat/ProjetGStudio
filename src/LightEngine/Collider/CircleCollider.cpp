#include "CircleCollider.h"
#include <SFML/System/Vector2.hpp>

CircleCollider::CircleCollider(float x, float y, float radius) : Collider(x, y, radius) {
}

bool CircleCollider::IsColliding(Collider* pOther, bool rigidBody)
{
	if (CircleCollider* pOtherCircleCollider = dynamic_cast<CircleCollider*>(pOther)) {
		sf::Vector2f distance = sf::Vector2f(mX, mY) - sf::Vector2f(pOtherCircleCollider->mX, pOtherCircleCollider->mY);

		float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

		float sqrRadius = (mRadius + pOtherCircleCollider->mRadius) * (mRadius + pOtherCircleCollider->mRadius);

		return sqrLength < sqrRadius;
	}
}

void CircleCollider::Update(float newX, float newY) {
	mX = newX;
	mY = newY;
}
