#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Manager/GameManager.h"
#include "../Entity/RectangleEntity.h"
#include "../StateMachine/StateMachine.h"

class AnimationRender;
class ActionPlayer;
class TextureManager;

// Structure contenant les donn�es li�es au joueur, comme la hauteur du saut, les vitesses, etc.
struct PlayerData
{
    float mJumpHeight = 600.f;  // Hauteur du saut
    float mJumpTime = 0.3f;     // Dur�e du saut
    float pJumpDuration = 0;    // Dur�e actuelle du saut

    float mMinSpeed = 0.f;      // Vitesse minimale
    float mMaxSpeedWalk = 20000.f; // Vitesse maximale en marchant
    float mMaxSpeedCrouch = 10000.f; // Vitesse maximale en accroupi

    float mAcceleration = 700.f;  // Acc�l�ration du joueur
    float mDeceleration = 500.f;  // D�c�l�ration du joueur
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

        COUNT // Nombre total d'�tats
    };

    static constexpr int STATE_COUNT = static_cast<int>(PlayerStateList::COUNT);

private:
    // Gestionnaires de textures
    AnimationRender* mTextured;
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

    // Indicateur pour v�rifier si le joueur est au sol
    bool isGrounded = false;

public:
    // M�thodes pour d�placer le joueur
    void Move(sf::Vector2f movement, float dt);
    void OnUpdate() override;
    void FixedUpdate(float dt) override;

    // Gestion du rendu du joueur
    Render* GetRender() { 
        Render* Temporary = static_cast<Render*>(mTextured);
        return Temporary;
    }

    // M�thode pour initialiser le joueur
    void OnInitialize() override;

    // Gestion de l'�tat du joueur
    bool SetState(PlayerStateList newState);

    // Destructeur
    ~Player();
    Player();

    // Accesseurs pour les donn�es du joueur (PData)
    PlayerData* GetPlayerData() const { return mPData; }

    // Amis de la classe (acc�s � des m�thodes priv�es)
    friend class PlayerAction_Jump;
    friend class PlayerAction_Crouch;
    friend class PlayerAction_Walk;
    friend class PlayerAction_Idle;
};
