#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "../Manager/GameManager.h"
#include "../Entity/RectangleEntity.h"
#include "../StateMachine/StateMachine.h"

class AnimationRender;
class ActionPlayer;
class TextureManager;

// Structure contenant les données liées au joueur, comme la hauteur du saut, les vitesses, etc.
struct PlayerData
{
    float mJumpHeight = 600.f;  // Hauteur du saut
    float mJumpTime = 0.3f;     // Durée du saut
    float pJumpDuration = 0;    // Durée actuelle du saut

    float mMinSpeed = 0.f;      // Vitesse minimale
    float mMaxSpeedWalk = 20000.f; // Vitesse maximale en marchant
    float mMaxSpeedCrouch = 10000.f; // Vitesse maximale en accroupi

    float mAcceleration = 700.f;  // Accélération du joueur
    float mDeceleration = 500.f;  // Décélération du joueur
};

// Classe représentant un joueur, héritant de RectangleEntity
class Player : public RectangleEntity
{
public:
    // Énumération des états possibles du joueur
    enum PlayerStateList
    {
        IDLE,
        CROUCH,
        WALK,
        JUMP,

        COUNT // Nombre total d'états
    };

    static constexpr int STATE_COUNT = static_cast<int>(PlayerStateList::COUNT);

private:
    // Gestionnaires de textures
    AnimationRender* mTextured;
    TextureManager* mAs;

    // État actuel du joueur
    PlayerStateList mState = PlayerStateList::IDLE;
    PlayerData* mPData;
    sf::Vector2f mLastMovement;

    // Tableau des transitions d'état
    bool mTransitions[STATE_COUNT][STATE_COUNT];

    // Actions associées aux états
    ActionPlayer* mActions[STATE_COUNT];

    // Méthode pour définir une transition d'état
    void SetTransition(PlayerStateList from, PlayerStateList to, bool value) { mTransitions[(int)from][(int)to] = value; }

    // Indicateur pour vérifier si le joueur est au sol
    bool isGrounded = false;

public:
    // Méthodes pour déplacer le joueur
    void Move(sf::Vector2f movement, float dt);
    void OnUpdate() override;
    void FixedUpdate(float dt) override;

    // Gestion du rendu du joueur
    Render* GetRender() { 
        Render* Temporary = static_cast<Render*>(mTextured);
        return Temporary;
    }

    // Méthode pour initialiser le joueur
    void OnInitialize() override;

    // Gestion de l'état du joueur
    bool SetState(PlayerStateList newState);

    // Destructeur
    ~Player();
    Player();

    // Accesseurs pour les données du joueur (PData)
    PlayerData* GetPlayerData() const { return mPData; }

    // Amis de la classe (accès à des méthodes privées)
    friend class PlayerAction_Jump;
    friend class PlayerAction_Crouch;
    friend class PlayerAction_Walk;
    friend class PlayerAction_Idle;
};
