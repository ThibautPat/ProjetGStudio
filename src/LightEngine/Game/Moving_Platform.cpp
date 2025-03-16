#include "Moving_Platform.h"

void Moving_Platform::OnUpdate()
{

	float linearMove = 0;
	if (mData->mMovement == 1 || mData->mMovement == -1)
		linearMove = mData->mMovement * 50;
	if (mShape.getPosition().x > mStartPosition.x + mMaxTravelDistance)
	{
		mClockMove.restart();
		mData->mMovement = -1;
	}
	if (mShape.getPosition().x < mStartPosition.x - mMaxTravelDistance)
	{
		mClockMove.restart();
		mData->mMovement = 1;
	}

	SetDirection(linearMove, 0,1);
	SetPosition(GetPosition(0, 0).x +mData->mMovement, GetPosition(0, 0).y);
}

void Moving_Platform::OnInitialize()
{
	mData = new Data(); 
	mShape.setOrigin(mShape.getSize().x / 2, mShape.getSize().y / 2);
}
