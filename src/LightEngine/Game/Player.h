#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/Entity.h"
#include "../Core/GameManager.h"

struct PlayerData
{
	float mJumpHeight = 500.f;
	float mJumpTime = 2.f;
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
	void Inertia(int key, sf::Vector2f movement, float dt);
	void Jump();
	void Move(sf::Vector2f movement, float dt, int key);
	bool Crouch();

	void OnUpdate() override;

	~Player();
};

