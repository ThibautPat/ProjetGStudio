#pragma once
#include "../Core/RectangleEntity.h"

struct Data
{
	
	float mMovement = 1;
};

class Moving_Platform : public RectangleEntity
{
	Data* mData;
	sf::Clock mClockMove;
	sf::Vector2f mStartPosition;
	int mMaxTravelDistance = 100;
public :
	void OnUpdate() override;
	void OnInitialize() override;
	void setMaxTravelDistance(int distance) { mMaxTravelDistance = distance; }
	void SetStartPosition(sf::Vector2f position) { mStartPosition = position; }
};

