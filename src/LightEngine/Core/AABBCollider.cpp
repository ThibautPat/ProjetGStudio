#include "AABBCollider.h"
#include "Entity.h"
#include <iostream>

AABBCollider::AABBCollider(float xMin, float yMin, float xMax, float yMax) : Collider(xMin, yMin, xMax, yMax) {
	mCollideFace = sf::Vector2f(0, 0);
}

bool AABBCollider::IsColliding(Collider* pOther) {
	int gap = 0;
	if (mCollidingFace.y == 1) {
		gap = 1;
	}
	sf::Rect bound(mXMin, mYMin+gap, mWidth, mHeight);
	sf::Rect otherBound(pOther->mXMin, pOther->mYMin, pOther->mWidth, pOther->mHeight);

	if (bound.intersects(otherBound)) {
		std::cout << "Collision Detected" << std::endl;

		
		//Decting the side of the collision
		sf::Vector2f coOther = sf::Vector2f(pOther->mXMin + pOther->mWidth/2, pOther->mYMin + pOther->mHeight/2);
		sf::Vector2f co = sf::Vector2f(mXMin + mWidth / 2, mYMin + mHeight / 2);

		float width1 = mWidth / 2;
		float width2 = pOther->mWidth / 2;
		float width = width1 + width2;
		float height1 = mHeight / 2;
		float height2 = pOther->mHeight / 2;
		float height = height1 + height2;

		
		if (co.x < coOther.x)
			mCollideFace.x = 1;
			
		if (co.x > coOther.x) 
			mCollideFace.x = -1;

		if (co.y < coOther.y)
			mCollideFace.y = 1;
			
		if (co.y > coOther.y)
			mCollideFace.y = -1;
		
		float diffx = abs(coOther.x - co.x);
		float diffy = abs(coOther.y - co.y);
		float penetrationx = width - diffx;
		float penetrationy = height - diffy;

		//Collision on y axe
		if (penetrationx > penetrationy) {
			std::cout << "penetration Y on ";
			if (mCollideFace.y < 0)
			{
				mCollidingFace = sf::Vector2f(0, -1);
				std::cout << "Top : " << penetrationx << " " << penetrationy << std::endl;
			}
			if (mCollideFace.y > 0)
			{
				mCollidingFace = sf::Vector2f(0, 1);
				std::cout << "Bottom : " << penetrationx << " " << penetrationy << std::endl;
			}
		}
		//Collision on x axe
		if (penetrationx < penetrationy) {
			std::cout << "penetration X on ";
			if (mCollideFace.x < 0)
			{
				mCollidingFace = sf::Vector2f(-1, 0); 
				std::cout << "Left : " << penetrationx << " " << penetrationy << std::endl;
			}
			if (mCollideFace.x > 0)
			{
				mCollidingFace = sf::Vector2f(1, 0); 
				std::cout << "Right : " << penetrationx << " " << penetrationy << std::endl;
			}
		}
		//--------------------------------------------------------------
		

		return true;
	}
	return false;
}

void AABBCollider::Update(float newX, float newY) {
	mXMin = newX;
	mYMin = newY;
	mCollideFace = sf::Vector2f(0, 0);
}
