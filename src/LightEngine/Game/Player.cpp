#include "Player.h"
#include "../Core/InputManager.h"
#include "../Core/Debug.h"
#include "../Core/TextureManager.h"
#include "TestScene.h"

void Player::Inertia(float dt, sf::Vector2f movement)
{
	if (movement.x != 0) // Mise � jour de mLastMovement si movement.x n'est pas nul
	{
		mLastMovement = movement;
	}
	if ((mLastMovement.x == -1 && mSpeed > 0) || (mLastMovement.x == 1 && mSpeed < 0)) // Gestion de la d�c�l�ration si la direction du mouvement change
	{
		mSpeed += (mLastMovement.x == -1 ? -1 : 1) *mPData->mDeceleration * 50 * dt;
	}
	if (movement.x == 0) // Si aucun mouvement, on ajuste la vitesse vers 0
	{
		float decelerationAmount =mPData->mDeceleration * 50 * dt;

		if (std::abs(mSpeed) > 100)	// D�c�l�rer ou acc�l�rer vers z�ro en fonction de la vitesse
		{
			mSpeed += (mSpeed > 0 ? -1 : 1) * decelerationAmount;
		}
		if (std::abs(mSpeed) < 500)	// Si la vitesse est proche de z�ro, on la r�initialise
		{
			mSpeed = 0;
		}
	}
}

void Player::Jump(float dt)
{
	mPData->pJumpDuration += dt;
	if (mBoolGravity && GetSecondJump() <= 0)
		return;
	if (mPData->pJumpDuration <mPData->mJumpTime)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
	{
		AddSecondJump(-1);
		mPData->pJumpDuration = 0;
		mGravitySpeed = -mPData->mJumpHeight; // voir fonction ? 
		mBoolGravity = true;
	}
}

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

void Player::Crouch()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
	{
		PlayerState = CROUCH;
		return;
	}
	PlayerState = IDLE;
	return;
}

void Player::FixedUpdate(float dt)
{
	Fall(dt); 
	mPData->pJumpDuration += dt;
	Move(InputDirection(), dt); 
}

bool Player::Jump() {
	if (SetState(JUMP)) {
		return true;
	}

	return false;
}

void Player::OnUpdate()
{
	mActions[(int)mState]->OnUpdate(this);

	mTextured->UpdateAnimation();

	// Debug de valeur
	const char* stateName = GetStateName(mState);
	Debug::DrawText(mShape.getPosition().x,mShape.getPosition().y - 30, stateName ,sf::Color::White);

	std::string text2 = std::to_string((int)mSpeed);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);

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
		return true;
	}
	return false;
}

Player::~Player()
{
}

Player::Player()
{
	SetTag(TestScene::Tag::PLAYER); 

	for (int i = 0; i < STATE_COUNT; i++)
	{
		for (int j = 0; j < STATE_COUNT; j++)
		{
			mTransitions[i][j] = false;
		}
	}

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

	SetTransition(PlayerStateList::IDLE, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP_ON_CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL_WALK, true);

	SetTransition(PlayerStateList::CROUCH, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::CROUCH, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::CROUCH, PlayerStateList::JUMP_ON_CROUCH, true);

	SetTransition(PlayerStateList::JUMP, PlayerStateList::ON_JUMP_WALK, true);
	SetTransition(PlayerStateList::JUMP, PlayerStateList::ON_JUMP_CROUCH, true);
	SetTransition(PlayerStateList::JUMP, PlayerStateList::ON_JUMP_IDLE, true);

	SetTransition(PlayerStateList::WALK, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::WALK, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::WALK, PlayerStateList::CROUCH, true);	
	SetTransition(PlayerStateList::WALK, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::WALK, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::WALK, PlayerStateList::FALL_WALK, true);

	SetTransition(PlayerStateList::JUMP_ON_CROUCH, PlayerStateList::ON_JUMP_CROUCH, true);
	SetTransition(PlayerStateList::JUMP_ON_CROUCH, PlayerStateList::ON_JUMP_IDLE, true);
	SetTransition(PlayerStateList::JUMP_ON_CROUCH, PlayerStateList::ON_JUMP_WALK, true);

	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::FALL_WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::ON_JUMP_CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_WALK, PlayerStateList::ON_JUMP_IDLE, true);

	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::FALL_WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::ON_JUMP_CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_IDLE, PlayerStateList::ON_JUMP_WALK, true);

	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::FALL_WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::ON_JUMP_WALK, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::ON_JUMP_IDLE, true);
	SetTransition(PlayerStateList::ON_JUMP_CROUCH, PlayerStateList::JUMP_ON_CROUCH, true);

	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::FALL_CROUCH, PlayerStateList::FALL_WALK, true);

	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::FALL_CROUCH, true);
	SetTransition(PlayerStateList::FALL_IDLE, PlayerStateList::FALL_WALK, true);

	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::WALK, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::JUMP, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::IDLE, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::CROUCH, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::FALL_IDLE, true);
	SetTransition(PlayerStateList::FALL_WALK, PlayerStateList::FALL_CROUCH, true);
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
