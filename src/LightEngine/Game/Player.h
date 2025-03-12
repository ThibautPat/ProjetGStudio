#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Core/Entity.h"
#include "../Core/GameManager.h"
#include "../Core/RectangleEntity.h"




class Player : public RectangleEntity
{
	PlayerData mPData;

	sf::Vector2f mLastMovement;
public: 
	float pJumpTime = 0;
	sf::Vector2f InputDirection();
	void Inertia(float dt, sf::Vector2f movement);
	void Jump(float dt);
	void Move(sf::Vector2f movement, float dt);
	bool Crouch();

	void OnUpdate() override;
	void FixedUpdate(float dt) override; 
	

	~Player();
};

