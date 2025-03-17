#pragma once
#include "../Core/Condition.h"
#include "Player.h"
class PlayerCondition_IsJumping : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsCrouching : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsWalking : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_HasJump : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsGrounded : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_GravityPlus : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};