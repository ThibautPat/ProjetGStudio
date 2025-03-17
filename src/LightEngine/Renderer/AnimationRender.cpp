#include "AnimationRender.h"

#include "../Manager/TextureManager.h"

#include <iostream>

AnimationRender::AnimationRender(int frameNb, const char* textName, sf::IntRect rect)
{
    mFrameNb = frameNb;
    SelectTexture(textName, rect);
    mTimePerFrame = 1.f / frameNb;
}

void AnimationRender::UpdateAnimation()
{
    float dt = GameManager::Get()->GetDeltaTime();
    mTimer += dt;

    if (mTimer >= mTimePerFrame) {


        mFrameCounter++;
        mTimer = 0.f;


        if (mTextRect.left + mTextRect.width > mTextRect.width * mFrameNb)
        {
            if (IsLoop()) {
                mFrameCounter = 0;
                mTextRect.left -= mTextRect.width * mFrameNb;
            }
            else {
                mFrameCounter = mFrameNb;
            }
               
        }

        sf::IntRect nrect =
        sf::IntRect(
            mTextRect.left + mTextRect.width, mTextRect.top, 
            mTextRect.width, mTextRect.height
        );
        SetTextureRect(nrect);

    }
}
