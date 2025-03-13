#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/TextureRender.h"
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

class Player : public RectangleEntity
{
	PlayerData* mPData;
	sf::Vector2f mLastMovement;

	//Gestionnaire de texture de l'entity
	TextureRender* mTextured;

	//Gestionnaire de texture de la scene
	TextureManager* mAs;

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

	TextureRender* GetTextured() { return mTextured; }

	void OnInitialize() override;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump(float dt);
	void Move(sf::Vector2f movement, float dt);
	void Crouch();
	///---------------------------------------------------------------------------------------
	//Ne pas override de Entity::Update(), car ne serait pas pris en compte par les colliders
	///---------------------------------------------------------------------------------------
	void OnUpdate() override; 
	void FixedUpdate(float dt) override; 
	
	~Player();
};

