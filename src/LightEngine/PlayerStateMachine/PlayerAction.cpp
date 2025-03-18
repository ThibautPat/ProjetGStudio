#pragma once
#include "PlayerAction.h"
#include "../GameEntity/Player.h"

void PlayerAction_Idle::OnStart(Player* pOwner)
{
}

void PlayerAction_Idle::OnUpdate(Player* pOwner)
{
	std::cout << "IDLE" << std::endl;
}

void PlayerAction_Jump::OnStart(Player* pOwner)
{
}

void PlayerAction_Jump::OnUpdate(Player* pOwner)
{
	std::cout << "JUMP" << std::endl;
}

void PlayerAction_Crouch::OnStart(Player* pOwner)
{
}

void PlayerAction_Crouch::OnUpdate(Player* pOwner)
{
	std::cout << "CROUCH" << std::endl;
}

void PlayerAction_Walk::OnStart(Player* pOwner)
{
}

void PlayerAction_Walk::OnUpdate(Player* pOwner)
{
	std::cout << "WALK" << std::endl;
}
