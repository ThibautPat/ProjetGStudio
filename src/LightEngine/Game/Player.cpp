#include "Player.h"

sf::Vector2f Player::Movement()
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

void Player::Move(sf::Vector2f movement, float dt, float runTime)
{
	float speed = 0;
	
	if (mSpeed <= 0)
	{
		float speedDecrement = mPData.mDeceleration;
		float realSpeed = mSpeed;
		mSpeed = realSpeed / 500 + speedDecrement * dt;
	}
	if (runTime > 0 && mSpeed < mPData.mMaxSpeed * 500)
	{
		time += dt;
		float acceleration = mPData.mAcceleration;
		speed += acceleration * time;
		if (mLastMovement != movement)
		{
			time = 0;
		}
	}
	else if (runTime == 0)
	{
		if (time > 0)
			time -= dt;
		float speedDecrement = mPData.mDeceleration;
		float realSpeed = mSpeed;

		speed = realSpeed / 500 - speedDecrement * dt;
		if (mSpeed <= 10)
		{
			speed = 0;
		}
	}
	else
	{
		speed = mPData.mMaxSpeed; 
	}
	
	mSpeed = speed * 500;

	if (!movement.x == 0)
	{
		mLastMovement = movement; 
	}
	
	SetDirection(mLastMovement.x * dt,0, mSpeed);
}

Player::~Player()
{
}
