#include "Player.h"
#include "../Core/InputManager.h"
#include "../Core/Debug.h"
#include "../Core/TextureManager.h"
#include "../Game/PlayerAction.h"
#include "../Game/PlayerCondition.h"
#include "../Game/TestScene.h"
#include "../Core/AnimationRender.h"
#include <iostream>
#include "../Core/RectangleEntity.h"

void Player::Move(sf::Vector2f movement, float dt)
{
	if (mSpeed > mPData->mMaxSpeedWalk)
	{
		mSpeed = mPData->mMaxSpeedWalk;
	}
	if (mSpeed < -mPData->mMaxSpeedWalk)
	{
		mSpeed = -mPData->mMaxSpeedWalk;
	}

	SetDirection(dt, 0, mSpeed);
}

void Player::FixedUpdate(float dt)
{
	Fall(dt); // Appliquer la gravité

	// Si le joueur est en train de sauter
	if (mPData->pJumpDuration > 0.f && !isGrounded)
	{
		// Si le joueur est en l'air, il faut entrer en état de chute
		if (mState != FALL_WALK && mState != FALL_IDLE && mState != FALL_CROUCH)
		{
			if (mSpeed != 0.f)
				SetState(FALL_WALK);  // Transition vers la chute en marchant
			else
				SetState(FALL_IDLE);  // Transition vers la chute en étant immobile
		}
	}
	else
	{
		// Le joueur n'est plus en l'air, on peut peut-être marcher ou rester immobile
		if (isGrounded)
		{
			if (mState == FALL_WALK || mState == FALL_IDLE)
			{
				if (mSpeed != 0.f)
					SetState(WALK);  // Transition vers la marche
				else
					SetState(IDLE);  // Transition vers l'état inactif
			}
		}
	}

	mPData->pJumpDuration += dt; // Mise à jour du temps de saut
	Move(InputDirection(), dt); // Déplacer le joueur selon les entrées
}


bool Player::Jump() {
	if (SetState(JUMP)) {
		return true;
	}

	return false;
}

void Player::OnUpdate()
{
	IsCrouched();  // Vérifier si le joueur s'accroupit (mettre à jour l'état si nécessaire)

	mActions[(int)mState]->OnUpdate(this); // Exécuter l'action correspondant à l'état actuel

	mTextured->UpdateAnimation(); // Mettre à jour l'animation du joueur

	// Débogage : afficher l'état actuel et la vitesse du joueur
	const char* stateName = GetStateName(mState);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 30, stateName, sf::Color::White);

	std::string text2 = std::to_string((int)mSpeed);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);


}

void Player::OnCollision(Entity* collidedWith)
{
	if (static_cast<AABBCollider*>(this->GetCollider())->GetCollideFace()->y == -1)
	{
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}
}

void Player::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2); //WTF pourquoi l'h�ritage n'est pas fait ?!
	mPData = new PlayerData;
	
	mAs = GameManager::Get()->GetTextureManager();

	//Setup de la gestion de textures
	mAs->LoadTexture("../../../res/Assets/Tilemap/tilemap_packed.png", "tilemap");
	mTextured = new AnimationRender(8, "tilemap", sf::IntRect(0, 0, 18, 18));
	//mTextured->SelectTexture();
}

sf::Vector2f Player::InputDirection()
{
	float dir_x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		dir_x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		dir_x = 1.f;
	}

	if (dir_x != 0.f) {
		SetState(WALK);
	}
	else {
		SetState(IDLE);
	}

	return sf::Vector2f(dir_x, 0.f);
}

bool Player::SetState(PlayerStateList newState)
{
	if (mTransitions[(int)mState][(int)newState])
	{
		mActions[(int)newState]->OnStart(this);
		mState = newState;

		return true;
	}

	return false;
}

bool Player::IsCrouched() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
	{
		SetState(CROUCH);
		return true;
	}
	return false;
}

Player::~Player()
{
}

Player::Player()
{
	SetTag(TestScene::Tag::PLAYER); // Tag du joueur

	// Initialisation des transitions
	for (int i = 0; i < STATE_COUNT; i++)
	{
		for (int j = 0; j < STATE_COUNT; j++)
		{
			mTransitions[i][j] = false;  // Aucune transition par défaut
		}
	}

	// Actions associées aux états
	mActions[(int)PlayerStateList::IDLE] = new PlayerAction_Idle();
	mActions[(int)PlayerStateList::CROUCH] = new PlayerAction_Crouch();
	mActions[(int)PlayerStateList::WALK] = new PlayerAction_Walk();
	mActions[(int)PlayerStateList::JUMP] = new PlayerAction_Jump();
	mActions[(int)PlayerStateList::JUMP_ON_CROUCH] = new PlayerAction_JumpOnCrouch();
	mActions[(int)PlayerStateList::FALL_CROUCH] = new PlayerAction_FallCrouch();
	mActions[(int)PlayerStateList::FALL_WALK] = new PlayerAction_FallWalk();
	mActions[(int)PlayerStateList::FALL_IDLE] = new PlayerAction_FallIdle();
	mActions[(int)PlayerStateList::ON_JUMP_CROUCH] = new PlayerAction_OnJumpCrouch();
	mActions[(int)PlayerStateList::ON_JUMP_WALK] = new PlayerAction_OnJumpWalk();
	mActions[(int)PlayerStateList::ON_JUMP_IDLE] = new PlayerAction_OnJumpIdle();

	// Définition des transitions entre états
	SetTransition(PlayerStateList::IDLE, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP_ON_CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_WALK, true);

	// Transition des autres états...
	// Ajout des transitions de chute après un saut
	SetTransition(PlayerStateList::JUMP, PlayerStateList::FALL_WALK, true);
	SetTransition(PlayerStateList::JUMP, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::JUMP, PlayerStateList::FALL_CROUCH, true);

	// Transition vers le crouch
	SetTransition(PlayerStateList::WALK, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::CROUCH, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::CROUCH, PlayerStateList::JUMP_ON_CROUCH, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::CROUCH, true);

	// Les transitions liées aux changements d'état de saut
	SetTransition(PlayerStateList::JUMP, PlayerStateList::ON_JUMP_WALK, true);
	SetTransition(PlayerStateList::JUMP, PlayerStateList::ON_JUMP_IDLE, true);
}


const char* Player::GetStateName(PlayerStateList state) const
{
	switch (state)
	{
	case IDLE: return "IDLE";
	case WALK: return "WALK";
	case JUMP: return "JUMP";
	case CROUCH: return "CROUCH";
	case JUMP_ON_CROUCH: return "JUMP_ON_CROUCH";
	case FALL_CROUCH: return "FALL_CROUCH";
	case FALL_WALK: return "FALL_WALK";
	case FALL_IDLE: return "FALL_IDLE";
	case ON_JUMP_CROUCH: return "ON_JUMP_CROUCH";
	case ON_JUMP_WALK: return "ON_JUMP_WALK";
	case ON_JUMP_IDLE: return "ON_JUMP_IDLE";
	default: return "Unknown";
	}
}
