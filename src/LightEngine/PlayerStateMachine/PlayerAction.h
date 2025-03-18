#pragma once

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