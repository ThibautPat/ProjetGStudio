#include "Player.h"

sf::Vector2f Player::Movement()
{
	mBoolGravity = true;
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
		if (mSpeed < 200 && mSpeed > -200)
		{
			mSpeed = 0;
		}
	}
}

bool Player::Jump(float dt, float pTime)
{
	pJumpTime += dt;
	if (pJumpTime > mPData.mJumpTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
		{
			mGravitySpeed = -mPData.mJumpHeight;
			
			return true;
		}
		else
		return false;
	}
	else
	return false;
}

void Player::Move(sf::Vector2f movement, float dt)
{
	float speed = 0;
	mSpeed += movement.x*50*dt*mPData.mAcceleration;

	Inertia(dt, movement);

	SetDirection(dt,0, mSpeed);
}

Player::~Player()
{
}
