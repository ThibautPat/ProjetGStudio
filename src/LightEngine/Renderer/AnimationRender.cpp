#include "../Renderer/AnimationRender.h"
#include "../Manager/TextureManager.h"
#include <iostream>
#include <fstream>
#include "../Library/json.hpp"
#include "../Other/Utils.h"

using json = nlohmann::json;

AnimationRender::AnimationRender(const char* spritesheetname, const char* spritename) : TextureRender(spritesheetname, spritename)
{
    TextureManager* tm = GameManager::Get()->GetTextureManager();
    json* njson = tm->GetJson(mSpriteSheetName);

    mFrameNb = Utils::GetInfoFromArray<int>(njson, spritename, "frames");
    mIsLoop = Utils::GetInfoFromArray<bool>(njson, spritename, "loop");

    mTimePerFrame = 1.f / (mFrameNb * mAnimSpeed);
}

void AnimationRender::UpdateAnimation()
{
    mRenderSprite->setScale(mRenderRatio);

    if (mIsFinished || mPaused)
        return;

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

            SetSpriteRect(nrect);
        }

        if (mFrameCounter >= mFrameNb)
        {

            if (IsLoop()) {
                mFrameCounter = 0;
                mTextRect.left -= mTextRect.width * (mFrameNb);
                SetSpriteRect(mTextRect);

            }
            else {
                sf::IntRect nrect =
                    sf::IntRect(
                        mTextRect.left - mTextRect.width, mTextRect.top,
                        mTextRect.width, mTextRect.height
                    );

                SetSpriteRect(nrect);
                mIsFinished = true;
            }
               
        }
    }
}
