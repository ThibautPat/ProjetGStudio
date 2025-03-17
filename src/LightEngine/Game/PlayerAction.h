#pragma once
#include "Player.h"

class ActionPlayer
{
public:
	virtual void OnStart(Player* pOwner) = 0;
	virtual void OnUpdate(Player* pOwner) = 0;
};

class PlayerAction_Jump : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Crouch : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
};

class PlayerAction_JumpOnCrouch : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Walk : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_Idle : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_OnJumpWalk : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_OnJumpIdle : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_OnJumpCrouch : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_FallWalk : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_FallIdle : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};

class PlayerAction_FallCrouch : public ActionPlayer
{
public:
	void OnStart(Player* pOwner) override;
	void OnUpdate(Player* pOwner) override;

};
