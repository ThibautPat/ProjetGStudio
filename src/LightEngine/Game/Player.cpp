#include "Player.h"
#include "../Core/InputManager.h"

void Player::Inertia(float dt, sf::Vector2f movement)
{
	// Mise à jour de mLastMovement si movement.x n'est pas nul
	if (movement.x != 0) {
		mLastMovement = movement;
	}

	// Gestion de la décélération si la direction du mouvement change
	if ((mLastMovement.x == -1 && mSpeed > 0) || (mLastMovement.x == 1 && mSpeed < 0)) {
		mSpeed += (mLastMovement.x == -1 ? -1 : 1) * mPData.mDeceleration * 50 * dt;
	}

	// Si aucun mouvement, on ajuste la vitesse vers 0
	if (movement.x == 0) {
		float decelerationAmount = mPData.mDeceleration * 50 * dt;

		// Décélérer ou accélérer vers zéro en fonction de la vitesse
		if (std::abs(mSpeed) > 100) {
			mSpeed += (mSpeed > 0 ? -1 : 1) * decelerationAmount;
		}

		// Si la vitesse est proche de zéro, on la réinitialise
		if (std::abs(mSpeed) < 500) {
			mSpeed = 0;
		}
	}
}

void Player::Jump(float dt)
{
	pJumpTime += dt;
	if (mBoolGravity && secondjump <= 0)
		return;
	if (pJumpTime < mPData.mJumpTime)
		return;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
		{
			secondjump -=1;
			pJumpTime = 0;
			mGravitySpeed = -mPData.mJumpHeight;
			mBoolGravity = true;
		}
}

void Player::Move(sf::Vector2f movement, float dt)
{
	mMove.x = movement.x;
	mSpeed += movement.x*50*dt*mPData.mAcceleration;

	Inertia(dt, movement);
	
	bool crouched = Crouch();
	if (crouched)
	{

		if (movement.x == 1)
		{
			if (mSpeed > 0)
			{
				mSpeed -= mPData.mMaxSpeed * dt;
			}
			if (mSpeed > 10000)
			{
				mSpeed -= mPData.mMaxSpeed* dt*2;
			}
			if (mSpeed < 11000 && mSpeed > 9000)
			{
				mSpeed = 10000;
			}
		}
		else if (movement.x == -1)
		{
			if (mSpeed < 0)
			{
				mSpeed += mPData.mMaxSpeed * dt;
			}
			if (mSpeed < -10000)
			{
				mSpeed += mPData.mMaxSpeed * dt*2;
			}
			if (mSpeed > -11000 && mSpeed < -9000)
			{
				mSpeed = -10000;
			}
		}
		
	}
	

	if (mSpeed > 20000)
	{
		mSpeed = 20000;
	}
	if (mSpeed < -20000)
	{
		mSpeed = -20000;
	}
	float speed = mSpeed;

	SetDirection(dt,0, speed);
}

bool Player::Crouch()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
	{
		return true;
	}
		return false;
}

void Player::FixedUpdate(float dt)
{
	Fall(dt);
	Jump(dt);
	Move(InputDirection(), dt);
}

void Player::OnUpdate()
{

}

sf::Vector2f Player::InputDirection()
{
	float x = 0;
	bool qPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10;
	bool dPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10;

	if (dPressed && !qPressed)
	{
		x = 1;
	}
	else if (qPressed && !dPressed)
	{
		x = -1;
	}
	else
	{
		x = 0;
	}
	return sf::Vector2f(x, 0); 
}

Player::~Player()
{
}
