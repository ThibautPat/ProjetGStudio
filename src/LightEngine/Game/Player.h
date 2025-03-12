#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/Entity.h"
#include "../Core/GameManager.h"
#include "../Core/RectangleEntity.h"


struct PlayerData
{
	float mJumpHeight = 500.f;
	float mJumpTime = 2.f;
	float mMinSpeed = 0.f;
	float mMaxSpeed = 20000.f;
	float mAcceleration = 700.f; 
	float mDeceleration = 500.f;
};

class Player : public RectangleEntity
{
	PlayerData mPData;
	sf::Vector2f mLastMovement;
public: 
	int test = 0; // test variable
	float pJumpTime = 0;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump();
	void Move(sf::Vector2f movement, float dt);
	bool Crouch();

	void OnUpdate() override;
	void FixedUpdate(float dt) override; 
	

	~Player();
};

