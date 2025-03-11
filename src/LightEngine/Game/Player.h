#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/DummyEntity.h"

struct PlayerData
{
	float mJumpHeight = 500.f;
	float mJumpTime = 2.f;
	float mMinSpeed = 0.f;
	float mMaxSpeed = 50.f;
	float mAcceleration = 600.f; 
	float mDeceleration = 300.f;
};

class Player : public DummyEntity
{

	float time = 0;
	PlayerData mPData;
	sf::Vector2f mLastMovement;
public: 
	float pJumpTime = 0;
	sf::Vector2f Movement();
	void Inertia(float dt, sf::Vector2f movement);
	bool Jump(float dt, float pTime);
	void Move(sf::Vector2f movement, float dt); 
	bool Crouch();
	~Player();
};

