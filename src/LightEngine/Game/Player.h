#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/DummyEntity.h"
#include "../Core/GameManager.h"
struct PlayerData
{
	float mJumpHeight = 500.f;
	float mJumpTime = 2.f;
	float mMinSpeed = 0.f;
	float mMaxSpeed = 50.f;
	float mAcceleration = 100.f; 
	float mDeceleration = 500.f;
};


class Player : public Entity
{

	float time = 0;
	PlayerData mPData;
	sf::Vector2f mLastMovement;
public: 
	float pJumpTime = 0;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump(float dt);
	void Move(sf::Vector2f movement, float dt); 
	~Player();
};

