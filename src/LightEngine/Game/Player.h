#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/DummyEntity.h"
#include "../Core/GameManager.h"



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
	void FixedUpdate(float dt) override; 
	

	~Player();
};

