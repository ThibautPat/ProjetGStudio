#pragma once
#include "../Entity/RectangleEntity.h"

struct Data
{
	float mMovement = 1;
	sf::Vector2f mDirection = sf::Vector2f(0, 0);
};

class Moving_Platform : public RectangleEntity
{
	Data* mData;
	sf::Clock mClockMove;
	sf::Vector2f mStartPosition;
	int mMaxTravelDistance = 100;
	bool isMoving = true;
public :
	void OnUpdate() override;
	void OnInitialize() override;
	void setMaxTravelDistance(int distance = 100) { mMaxTravelDistance = distance; }
	void SetStartPosition(sf::Vector2f position) { mStartPosition = position; }
	void SetLinearDirection(sf::Vector2f direction) { mData->mDirection = direction; }
};

