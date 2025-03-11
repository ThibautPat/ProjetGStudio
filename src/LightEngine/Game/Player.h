#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/DummyEntity.h"

struct PlayerData
{
	float mJumpHeight = 700.f;
	float mJumpTime = 2.f;
	float mMinSpeed = 0.f;
	float mMaxSpeed = 50.f;
	float mAcceleration = 30.f; 
	float mDeceleration = 70.f;
};

class Player : public DummyEntity
{

	float time = 0;
	PlayerData mPData;
	sf::Vector2f mLastMovement;
public: 
	float pJumpTime = 0;
	sf::Vector2f Movement();
	bool Jump(float dt, float pTime);
	void Move(sf::Vector2f movement, float dt, float runTime); 
	~Player();
};

