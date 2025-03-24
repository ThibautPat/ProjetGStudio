#include "Animator.h"
#include "../Renderer/AnimationRender.h"

void Animator::AddAnimation(const char* spritesheetname, const char* spritename)
{
    AnimationRender* anim = new AnimationRender(spritesheetname, spritename);
    const std::string name = anim->GetSpriteName();
    mAnimMap.insert({ spritename , anim });

    if (mCurrentAnim)
        return;

    mCurrentAnim = anim;
}

void Animator::SetCurrentAnimation(std::string& spritename)
{
    mCurrentAnim = mAnimMap.at(spritename);
    mCurrentAnim->SetIsFinished(false);
    mCurrentAnim->SetFrameCounter(0);
    mCurrentAnim->ResetRect();
}

void Animator::SetRatio(sf::Vector2f nratio)
{
    mRatio = nratio;
}

void Animator::UpdateCurrentAnimation()
{
    mCurrentAnim->SetRatio(mRatio);
    mCurrentAnim->UpdateAnimation();
}

Animator::~Animator() // Add the destructor
{
    for (auto const& [key, val] : mAnimMap)
    {
        delete val; // Delete each AnimationRender object
    }
    mAnimMap.clear(); // Clear the map after deleting
}