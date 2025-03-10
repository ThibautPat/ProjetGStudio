#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "DummyEntity.h"

struct PlayerData
{
	float mJumpHeight = 100.f;
	float mJumpTime = 2.f;
	float mMinSpeed = 20.f;
	float mMaxSpeed = 100.f;
	float mAcceleration = 10.f; 
};

class Player : public DummyEntity
{
	PlayerData mPData;

public: 
	
	sf::Vector2f Movement();
	bool Jump(float dt, float pTime);
	void Move(sf::Vector2f movement, float dt, float runTime); 
	~Player();
};

