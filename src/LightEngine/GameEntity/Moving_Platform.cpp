#include "Moving_Platform.h"

void Moving_Platform::OnUpdate()
{
	if (isMoving)
	{
		if (mData->mDirection.x != 0)
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

			SetDirection(linearMove, 0, 1);
			SetPosition(GetPosition(0, 0).x + mData->mMovement, GetPosition(0, 0).y);
		}
		if (mData->mDirection.y != 0)
		{
			float linearMove = 0;
			if (mData->mMovement == 1 || mData->mMovement == -1)
				linearMove = mData->mMovement * 50;
			if (mShape.getPosition().y > mStartPosition.y + mMaxTravelDistance)
			{
				mClockMove.restart();
				mData->mMovement = -1;
			}
			if (mShape.getPosition().y < mStartPosition.y - mMaxTravelDistance)
			{
				mClockMove.restart();
				mData->mMovement = 1;
			}

			SetDirection(0, linearMove, 1);
			SetPosition(GetPosition(0, 0).x, GetPosition(0, 0).y + mData->mMovement);
		}
	}
}

void Moving_Platform::OnInitialize()
{
	mData = new Data(); 
	mShape.setOrigin(mShape.getSize().x / 2, mShape.getSize().y / 2);
	mStartPosition = mShape.getPosition(); 
}
