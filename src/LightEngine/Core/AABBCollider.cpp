#include "AABBCollider.h"
#include "Entity.h"

AABBCollider::AABBCollider(float xMin, float yMin, float xMax, float yMax) : Collider(xMin, yMin, xMax, yMax) {
}

bool AABBCollider::IsColliding(Collider* pOther) {

	sf::Rect bound(mXMin, mYMin, mWidth, mHeight);
	sf::Rect otherBound(pOther->mXMin, pOther->mYMin, pOther->mWidth, pOther->mHeight);

	if (!bound.intersects(otherBound)) {
		return false;
	}

	//Colisions Verticales Top






	return true;
}

void AABBCollider::Update(float newX, float newY) {
	mXMin = newX;
	mYMin = newY;
}
