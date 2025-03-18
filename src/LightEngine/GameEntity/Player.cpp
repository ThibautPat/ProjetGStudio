#include "Player.h"
#include "../Other/Debug.h"
#include "../Manager/TextureManager.h"
#include "../PlayerStateMachine/PlayerAction.h"
#include "../PlayerStateMachine/PlayerCondition.h"
#include "../GameScene/TestScene.h"
#include "../Renderer/AnimationRender.h"
#include "../Collider/AABBCollider.h"

bool Player::SetState(PlayerStateList newState)
{
	if (mTransitions[(int)mState][(int)newState]) {
		mState = newState;
		return true;
	}
	return false;
}

Player::Player()
{
    SetTag(TestScene::Tag::PLAYER);

    for (int i = 0; i < STATE_COUNT; i++)
    {
        for (int j = 0; j < STATE_COUNT; j++)
        {
            mTransitions[i][j] = false;
        }
    }

    mActions[(int)PlayerStateList::IDLE] = new PlayerAction_Idle();  
    mActions[(int)PlayerStateList::CROUCH] = new PlayerAction_Crouch(); 
    mActions[(int)PlayerStateList::WALK] = new PlayerAction_Walk();  
    mActions[(int)PlayerStateList::JUMP] = new PlayerAction_Jump(); 

    SetTransition(PlayerStateList::IDLE, PlayerStateList::WALK, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::CROUCH, true);

    SetTransition(PlayerStateList::CROUCH, PlayerStateList::WALK, true);
    SetTransition(PlayerStateList::CROUCH, PlayerStateList::IDLE, true);

    SetTransition(PlayerStateList::WALK, PlayerStateList::JUMP, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::IDLE, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::CROUCH, true);