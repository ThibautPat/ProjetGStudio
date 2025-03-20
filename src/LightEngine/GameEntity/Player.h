#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Manager/GameManager.h"
#include "../Entity/RectangleEntity.h"
#include "../Renderer/Animator.h"

class AnimationRender;
class TextureRender;
class ActionPlayer;
class TextureManager;

// Structure contenant les donn�es li�es au joueur, comme la hauteur du saut, les vitesses, etc.
struct PlayerData
{
    float mJumpHeight = 600.f;  // Hauteur du saut
    float mJumpTime = 0.8f;     // Dur�e du saut
    float pJumpDuration = 0.f;    // Dur�e actuelle du saut

    float mMinSpeed = 0.f;      // Vitesse minimale
    float mMaxSpeedWalk = 20000.f; // Vitesse maximale en marchant
    float mMaxSpeedCrouch = 10000.f; // Vitesse maximale en accroupi
    float mMaxSpeedPush = 15000.f; // Vitesse maximale en accroupi

    float mAcceleration = 700.f;  // Acc�l�ration du joueur
    float mDeceleration = 500.f;  // D�c�l�ration du joueur

    float mMaxBatteryDuration = 5.f;
    float mCurrentBatteryDuration = 0.f;

    sf::Vector2f mDirection = sf::Vector2f(0.f, 0.f);

    bool isGrounded = false;
    bool isCrouching = false;
    bool isBackward = false;
    bool playerIsDead = false;
    
	sf::Vector2f nratioTexture = sf:: Vector2f(1,1);

    sf::Clock RespawnClock;
    sf::Vector2f mLastCheckPoint;

    sf::FloatRect mHitboxCrouch = {0.f, 0.f, 115.f, 180.f} ;
    sf::FloatRect mHitboxNotCrouch = { 0.f, 0.f, 110.f, 230.f };
};

// Classe repr�sentant un joueur, h�ritant de RectangleEntity
class Player : public RectangleEntity
{
public:
    // �num�ration des �tats possibles du joueur
    enum PlayerStateList
    {
        IDLE,
        CROUCH,
        WALK,
        JUMP,
        FALL,
        DEAD,
        RESPAWN,
        PUSH,

        COUNT // Nombre total d'�tats
    };

    static constexpr int STATE_COUNT = static_cast<int>(PlayerStateList::COUNT);

private:
    // Gestionnaires de textures
    Animator* mAnimator;
    TextureManager* mAs;

    // �tat actuel du joueur
    PlayerStateList mState = PlayerStateList::IDLE;
    PlayerData* mPData;
    sf::Vector2f mLastMovement;

    // Tableau des transitions d'�tat
    bool mTransitions[STATE_COUNT][STATE_COUNT];

    // Actions associ�es aux �tats
    ActionPlayer* mActions[STATE_COUNT];
   
    // M�thode pour d�finir une transition d'�tat
    void SetTransition(PlayerStateList from, PlayerStateList to, bool value) { mTransitions[(int)from][(int)to] = value; }

public: 

    // M�thodes pour d�placer le joueur
    void Move(sf::Vector2f movement, float dt);
    bool Movement();
    void OnUpdate() override;
    void FixedUpdate(float dt) override;

    void HandleBattery();

    Collider* GetCollider() override;

    //Au moment d'une collision
    void OnCollision(Entity* other) override;

    void PlayerRespawn();

    void PlayerDeath();

    // M�thode pour initialiser le joueur
    void OnInitialize() override;

    // Gestion de l'�tat du joueur
    bool SetState(PlayerStateList newState);

    // Destructeur
    ~Player();
    Player();

    // Accesseurs pour les donn�es du joueur (PData)
    PlayerData* GetPlayerData() const { return mPData; }
    TextureRender* GetTextureRender() override;
    void InitRender(const char* spritesheetname, const char* spritename) override { mAnimator = new Animator(); }

    // Amis de la classe (acc�s � des m�thodes priv�es)
    friend class PlayerAction_Jump;
    friend class PlayerAction_Crouch;
    friend class PlayerAction_Walk;
    friend class PlayerAction_Idle;
    friend class PlayerAction_Fall;
    friend class PlayerAction_Death;
    friend class PlayerAction_Respawn;
    friend class PlayerAction_Push;
};
