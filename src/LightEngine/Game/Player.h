#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/TexturedEntity.h"
#include "../Core/GameManager.h"
#include "../Core/RectangleEntity.h"

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

class Player : public RectangleEntity, public TexturedEntity
{
	PlayerData* mPData;
	sf::Vector2f mLastMovement;

protected:

	enum PlayerStateList
	{
		IDEL,
		CROUCH,
		WALK,
		JUMP
	};

	PlayerStateList PlayerState = WALK;

public: 

	void OnInitialize() override;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump(float dt);
	void Move(sf::Vector2f movement, float dt);
	void Crouch();

	void OnInitialize();
	void OnUpdate() override;
	void FixedUpdate(float dt) override; 
	
	~Player();
};

