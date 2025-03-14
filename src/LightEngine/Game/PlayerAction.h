#pragma once
#include "../Core/Action.h"
#include "Player.h"
class PlayerAction_Jump : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_Crouch : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_JumpOnCrouch : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_Walk : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};