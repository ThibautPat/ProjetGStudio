#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/DummyEntity.h"
#include "../Core/GameManager.h"
struct PlayerData
{
	float mJumpHeight = 600.f; // #TODO: Change to jump force
	float mJumpTime = 0.3f; 
	float mMinSpeed = 0.f;
	float mMaxSpeed = 20000.f;
	float mAcceleration = 700.f; 
	float mDeceleration = 500.f;
};


class Player : public Entity
{
	PlayerData mPData;
	sf::Vector2f mLastMovement;
public: 
	int test = 0; // test variable
	float pJumpTime = 0;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump(float dt);
	void Move(sf::Vector2f movement, float dt);
	bool Crouch();


	~Player();
};

