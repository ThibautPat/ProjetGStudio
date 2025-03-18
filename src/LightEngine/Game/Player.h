#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/GameManager.h"
#include "../Core/RectangleEntity.h"
#include "../Core/StateMachine.h"

class AnimationRender;
class ActionPlayer;

struct PlayerData
{
	float mJumpHeight = 600.f;
	float mJumpTime = 0.3f;
	float pJumpDuration = 0;

	float mMinSpeed = 0.f;
	float mMaxSpeedWalk = 20000.f;
	float mMaxSpeedCrouch= 10000.f;

	float mAcceleration = 700.f;
	float mDeceleration = 500.f;
};

class Player : public RectangleEntity
{
public:
	enum PlayerStateList
	{
		IDLE,
		CROUCH,
		WALK,
		JUMP,
		JUMP_ON_CROUCH,
		FALL_CROUCH,
		FALL_WALK,
		FALL_IDLE,
		ON_JUMP_CROUCH,
		ON_JUMP_WALK,
		ON_JUMP_IDLE,

		COUNT
	};
	static constexpr int STATE_COUNT = static_cast<int>(PlayerStateList::COUNT);

private:

	PlayerStateList mState = PlayerStateList::IDLE;

	bool mTransitions[STATE_COUNT][STATE_COUNT];

	ActionPlayer* mActions[STATE_COUNT];

	//Gestionnaire de texture de l'entity
	AnimationRender* mTextured;

	//Gestionnaire de texture de la scene
	TextureManager* mAs;

	void SetTransition(PlayerStateList from, PlayerStateList to, bool value) { mTransitions[(int)from][(int)to] = value; }

public: 
	PlayerData* mPData;
	sf::Vector2f mLastMovement;

	Render* GetRender() { return (Render*)mTextured; };

	void OnInitialize() override;
	sf::Vector2f InputDirection();

	bool SetState(PlayerStateList newState);

	bool IsCrouched();
	
	void Move(sf::Vector2f movement, float dt);
	
	///---------------------------------------------------------------------------------------
	//Ne pas override de Entity::Update(), car ne serait pas pris en compte par les colliders
	///---------------------------------------------------------------------------------------
	void OnUpdate() override; 
	void OnCollision(Entity* collidedWith) override;
	void FixedUpdate(float dt) override;
	bool Jump();
	
	~Player();
	Player();

	const char* GetStateName(PlayerStateList state) const;

	friend class PlayerAction_Jump;
	friend class PlayerAction_Crouch;
	friend class PlayerAction_JumpOnCrouch;
	friend class PlayerAction_Walk;
	friend class PlayerAction_Idle;
	friend class PlayerAction_OnJumpWalk;
	friend class PlayerAction_OnJumpIdle;
	friend class PlayerAction_OnJumpCrouch;
	friend class PlayerAction_FallWalk;
	friend class PlayerAction_FallIdle;
	friend class PlayerAction_FallCrouch;
};

