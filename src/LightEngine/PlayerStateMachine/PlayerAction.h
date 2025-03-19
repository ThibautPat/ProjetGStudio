#pragma once
#include "../StateMachine/Action.h"
#include "../GameEntity/Player.h"

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
	bool isIdle = false;
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_OnJumpWalk : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_OnJumpIdle : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_OnJumpCrouch : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_FallWalk : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_FallIdle : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};

class PlayerAction_FallCrouch : public Action<Player>
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
	void OnEnd(Player* pOwner) override;
};
