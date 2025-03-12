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
	pJumpTime += dt;
	if (mBoolGravity && secondjump == 0)
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

Player::~Player()
{
}
