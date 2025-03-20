#include "Collider.h"

Collider::Collider(float xMin, float yMin, float xMax, float yMax) : mXMin(xMin), mYMin(yMin) {
	mHeight = yMax - yMin;
	mWidth = xMax - xMin;
}

Collider::Collider(float x, float y, float radius) : mX(x), mY(y), mRadius(radius) {
}

void Collider::SetRect(float xMin, float yMin, float width, float height)
{
	mXMin = xMin;
	mYMin = yMin;
	mWidth = width;
	mHeight = height;
}