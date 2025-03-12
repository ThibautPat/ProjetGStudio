#include "Player.h"
#include "../Core/InputManager.h"
#include "../Core/Debug.h"

void Player::Inertia(float dt, sf::Vector2f movement)
{
	if (movement.x != 0) // Mise à jour de mLastMovement si movement.x n'est pas nul
	{
		mLastMovement = movement;
	}
	if ((mLastMovement.x == -1 && mSpeed > 0) || (mLastMovement.x == 1 && mSpeed < 0)) // Gestion de la décélération si la direction du mouvement change
	{
		mSpeed += (mLastMovement.x == -1 ? -1 : 1) *mPData->mDeceleration * 50 * dt;
	}
	if (movement.x == 0) // Si aucun mouvement, on ajuste la vitesse vers 0
	{
		float decelerationAmount =mPData->mDeceleration * 50 * dt;

		if (std::abs(mSpeed) > 100)	// Décélérer ou accélérer vers zéro en fonction de la vitesse
		{
			mSpeed += (mSpeed > 0 ? -1 : 1) * decelerationAmount;
		}
		if (std::abs(mSpeed) < 500)	// Si la vitesse est proche de zéro, on la réinitialise
		{
			mSpeed = 0;
		}
	}
}

void Player::Jump(float dt)
{
	mPData->pJumpDuration += dt;
	if (mBoolGravity && secondjump == 0)
		return;
	if (mPData->pJumpDuration <mPData->mJumpTime)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
	{
		secondjump -=1;
		mPData->pJumpDuration = 0;
		mGravitySpeed = -mPData->mJumpHeight; // voir fonction ? 
		mBoolGravity = true;
	}
}

void Player::Move(sf::Vector2f movement, float dt)
{
	mSpeed += movement.x * 50 * dt * mPData->mAcceleration;

	Inertia(dt, movement);
	Crouch();

	if (PlayerState == CROUCH) //Possibilité de refacto 
	{
		if (movement.x == 1)
		{
			if (mSpeed > 0)
			{
				mSpeed -= mPData->mMaxSpeedWalk * dt;
			}
			if (mSpeed > mPData->mMaxSpeedCrouch)
			{
				mSpeed -= mPData->mMaxSpeedWalk * dt * 2;
			}
			if (mSpeed < 11000 && mSpeed > 9000)
			{
				mSpeed = mPData->mMaxSpeedCrouch;
			}
		}
		else if (movement.x == -1)
		{
			if (mSpeed < 0)
			{
				mSpeed += mPData->mMaxSpeedWalk * dt;
			}
			if (mSpeed < -mPData->mMaxSpeedCrouch)
			{
				mSpeed += mPData->mMaxSpeedWalk * dt * 2;
			}
			if (mSpeed > -11000 && mSpeed < -9000)
			{
				mSpeed = -mPData->mMaxSpeedCrouch;
			}
		}
	}
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
	PlayerState = IDEL;
	return;
}

void Player::FixedUpdate(float dt)
{
	Fall(dt);
	Jump(dt);
	Move(InputDirection(), dt);
}

void Player::OnUpdate()
{
	// Debug de valeur
	std::string text = std::to_string(PlayerState);
	Debug::DrawText(mShape.getPosition().x,mShape.getPosition().y - 30, text ,sf::Color::White);

	std::string text2 = std::to_string(mSpeed);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);
}

void Player::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2); //WTF pour quoi l'héritage n'est pas fait ?!
	mPData = new PlayerData;
}

sf::Vector2f Player::InputDirection()
{
	float dir_x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		dir_x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		dir_x = 1;
	}

	return sf::Vector2f(dir_x, 0);
}

Player::~Player()
{
}
