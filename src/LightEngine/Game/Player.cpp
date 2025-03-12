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
	mDirection.x = movement.x;
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
	float y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		x = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		x = 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10)
	{
		y = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10)
	{
		y = 100;
	}

	if (x > -10 && x < 10)
		x = 0;
	if (y > -10 && y < 10)
		y = 0;
	if (x < 0)
		x = -1;
	if (x > 0)
		x = 1;
	if (y < 0)
		y = -1;
	if (y > 0)
		y = 1;

	return sf::Vector2f(x, y);
}

Player::~Player()
{
}
