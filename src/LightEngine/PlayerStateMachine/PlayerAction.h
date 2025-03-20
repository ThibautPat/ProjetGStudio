#pragma once

class Player;

class ActionPlayer
{
public:
    virtual void OnStart(Player* pOwner) = 0;
    virtual void OnUpdate(Player* pOwner) = 0;
};

class PlayerAction_Idle : public ActionPlayer
{
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Jump : public ActionPlayer
{
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Crouch : public ActionPlayer
{
    bool onCrouch;

public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Walk : public ActionPlayer
{
	bool isIdle = false;
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Fall : public ActionPlayer
{
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Death : public ActionPlayer
{
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Respawn : public ActionPlayer
{
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};

class PlayerAction_Push : public ActionPlayer
{
    bool onPush;
public:
    void OnStart(Player* pOwner) override;
    void OnUpdate(Player* pOwner) override;
};