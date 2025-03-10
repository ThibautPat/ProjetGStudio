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
	
	if (pTime > mPData.mJumpTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
		{
			std::cout << "Jump" << std::endl; //#TODO add jump with gravity
			
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
	if (runTime > 0 && mSpeed < mPData.mMaxSpeed*500) 
	{
		float acceleration = mPData.mAcceleration;
		float minSpeed = mPData.mMinSpeed;
		speed = minSpeed + acceleration * runTime;
	}
	else if (runTime == 0)
	{
		speed = mPData.mMinSpeed;
	}
	else
	{
		speed = mPData.mMaxSpeed; 
	}
	

	mSpeed = speed * 500 ;
	SetDirection(movement.x * dt, movement.y * dt, mSpeed);
}

Player::~Player()
{
}
