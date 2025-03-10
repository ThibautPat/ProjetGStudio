#include "AABBCollider.h"
#include "../Entity.h"

AABBCollider::AABBCollider(float xMin, float yMin, float xMax, float yMax) : Collider(xMin, yMin, xMax, yMax) {
}

bool AABBCollider::IsColliding(Collider* pOther) {

	sf::Rect bound(mXMin, mYMin, mWeight, mHeight);
	sf::Rect otherBound(pOther->mXMin, pOther->mYMin, pOther->mWeight, pOther->mHeight);

	return bound.intersects(otherBound);
}

void AABBCollider::Update(float newX, float newY) {
	mXMin = newX;
	mYMin = newY;
}
