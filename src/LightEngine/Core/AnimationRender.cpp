#include "AnimationRender.h"
#include "TextureManager.h"

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

//AnimationRender::AnimationRender(std::string& spritesheetname, std::string& spritename)
//{
//    mSpriteName = spritename;
//    mSpriteSheetName = spritesheetname;
//
//    TextureManager* tm = GameManager::Get()->GetTextureManager();
//    tm->FindTexture(mSpriteSheetName, mSpriteName, &mTextRect);
//
//    //sf::IntRect renderRect = mTextRect;
//
//
//    std::string xinfo = "x";
//    mTextRect.left = tm->GetSpriteInfo<int>(mSpriteSheetName, mSpriteName, xinfo);
//    std::string yinfo = "y";
//    mTextRect.top = tm->GetSpriteInfo<int>(mSpriteSheetName, mSpriteName, yinfo);
//
//    std::string frameinfo = "frame_size";
//    std::string width = "width";
//    std::string height = "height";
//    mTextRect.width = tm->GetSpriteSheetInfo<int>(mSpriteSheetName, frameinfo, width);
//    mTextRect.height = tm->GetSpriteSheetInfo<int>(mSpriteSheetName, frameinfo, width);
//
//    std::string framenb = "frames";
//    mFrameNb = tm->GetSpriteInfo<int>(mSpriteSheetName, mSpriteName, framenb);
//    mTimePerFrame = 1.f / mFrameNb;
//    
//}
//
//void AnimationRender::Update()
//{
//    TextureManager* tm = GameManager::Get()->GetTextureManager();
//}

AnimationRender::AnimationRender(int frameNb, const char* textName, sf::IntRect rect)
{

    mFrameNb = frameNb;
    SelectTexture(textName, rect);

    //TODO with a speed anim
    mTimePerFrame = 1.f / (frameNb*2);
}

void AnimationRender::UpdateAnimation()
{
    float dt = GameManager::Get()->GetDeltaTime();
    mTimer += dt;

    if (mTimer >= mTimePerFrame) {


        mFrameCounter++;
        mTimer = 0.f;

        {
            sf::IntRect nrect =
                sf::IntRect(
                    mTextRect.left + mTextRect.width, mTextRect.top,
                    mTextRect.width, mTextRect.height
                );

            SetTextureRect(nrect);
        }

        if ( mTextRect.left + mTextRect.width > mTextRect.width * mFrameNb )
        {
            if (IsLoop()) {
                mFrameCounter = 0;
                mTextRect.left -= mTextRect.width * (mFrameNb);
            }
            else {
                mFrameCounter = mFrameNb;
            }
               
        }

        //if (mFrameCounter == 0) {
        //    //SetTextureRect(mTextRect);
        //}
        //else

    }
}
