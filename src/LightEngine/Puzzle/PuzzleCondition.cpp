#include "PuzzleCondition.h"
#include "../GameScene/Scene.h"
#include "../GameEntity/Player.h"

bool PuzzleCondition_PlayerIsTouched::OnTest(RectangleEntity* owner)
{
    //--------------------------------
    //keep this
    if (mDoneOneTime)
        return true;
    //--------------------------------


    //Do want you want
    Player* p = GameManager::Get()->GetEntity<Player>(Scene::Tag::PLAYER);
    //...
    //Do verif here
    if (owner->IsColliding(p))


    //--------------------------------
    //keep this
    {
        if (mNeedToDoOneTime)
            mDoneOneTime = true;

        return true;
    }
      
    return false;
    //--------------------------------
}

bool PuzzleCondition_PlayerUpTo500y::OnTest(RectangleEntity* owner)
{
    if (mDoneOneTime)
        return true;


    Player* p = GameManager::Get()->GetEntity<Player>(Scene::Tag::PLAYER);
    if (p->GetPosition(0,0).y < -500) 
    
    
    {
        if (mNeedToDoOneTime)
            mDoneOneTime = true;

        return true;
    }

    return false;
}
