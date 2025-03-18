#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Manager/GameManager.h"
#include "../Entity/RectangleEntity.h"
#include "../StateMachine/StateMachine.h"

class AnimationRender;

struct PlayerData
{
	int mSecondJump = 2;
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
	StateMachine<Player> mStateMachine;

	//Gestionnaire de texture de l'entity
	AnimationRender* mTextured;

	//Gestionnaire de texture de la scene
	TextureManager* mAs;

protected:
	
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

public: 
	PlayerData* mPData;
	sf::Vector2f mLastMovement;

	Render* GetRender() { return (Render*)mTextured; };

	void OnInitialize() override;
	sf::Vector2f InputDirection();
	int GetSecondJump() { return mPData->mSecondJump; }
	void AddSecondJump(int nb) { mPData->mSecondJump += nb; }
	void SetSecondJump(int nb) { mPData->mSecondJump = nb; }
	void Move(sf::Vector2f movement, float dt);
	
	///---------------------------------------------------------------------------------------
	//Ne pas override de Entity::Update(), car ne serait pas pris en compte par les colliders
	///---------------------------------------------------------------------------------------
	void OnUpdate() override; 
	void FixedUpdate(float dt) override; 
	
	const char* GetStateName(PlayerStateList state) const;	
	~Player();
	Player();
};

