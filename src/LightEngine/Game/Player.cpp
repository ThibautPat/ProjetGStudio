#include "Player.h"
#include "../Core/InputManager.h"

void Player::Inertia(float dt, sf::Vector2f movement)
{
	if (!movement.x == 0)
	{
		mLastMovement = movement;
	}
	if (mLastMovement.x == -1 && mSpeed > 0)
	{
		mSpeed -= mPData.mDeceleration * 50 * dt;
	}
	if (mLastMovement.x == 1 && mSpeed < 0)
	{
		mSpeed += mPData.mDeceleration * 50 * dt;
	}
	if (movement.x == 0)
	{
		if (mSpeed > 100)
		{
			mSpeed -= mPData.mDeceleration * 50 * dt;
		}
		if (mSpeed < 100)
		{
			mSpeed += mPData.mDeceleration * 50 * dt;
		}
		if (mSpeed < 500 && mSpeed > -500)
		{
			mSpeed = 0;
		}
	}
}

void Player::Jump()
{
	
	if (mBoolGravity)
		return;

	mGravitySpeed = -mPData.mJumpHeight;
	mBoolGravity = true;
}

void Player::Move(sf::Vector2f movement, float dt)
{
	mSpeed += movement.x*50*dt*mPData.mAcceleration;

	Inertia(dt, movement);
	
	bool crouched = Crouch();
	if (crouched)
	{
		mSpeed = 10000*movement.x;
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

void Player::OnUpdate()
{
	float dt = GameManager::Get()->GetDeltaTime();
	InputManager* inp = GameManager::Get()->GetInputManager();

}

Player::~Player()
{
}
