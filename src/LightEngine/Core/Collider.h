#pragma once
class Collider {
public:
	Collider(float xMin, float yMin, float xMax, float yMax);
	Collider(float x, float y, float radius);

	//Pk pas un sf::Rect ici ?
	float mXMin = 0.f, mYMin = 0.f;
	float mWidth = 0.f, mHeight = 0.f;
	//---------------------------
	float mX = 0.f, mY = 0.f;
	float mRadius = 0.f;

	virtual bool IsColliding(Collider* pOther) = 0;
	virtual void Update(float newX, float newY) = 0;
};

