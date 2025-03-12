#include "Collider.h"

Collider::Collider(float xMin, float yMin, float xMax, float yMax) : mXMin(xMin), mYMin(yMin) {
	mHeight = yMax - yMin;
	mWeight = xMax - xMin;
}

Collider::Collider(float x, float y, float radius) : mX(x), mY(y), mRadius(radius) {
}