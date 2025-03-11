#include "Player.h"
#include "../Core/InputManager.h"

void Player::Inertia(int key, sf::Vector2f movement, float dt)
{
	float movX = 0;
	//InputManager::Key Key = InputManager::Key::MAJ;
	InputManager::Key nkey = (InputManager::Key)key;

	switch (nkey)
	{
	case InputManager::Key::Q:
		movX = -1;
		break;
	case InputManager::Key::D:
		movX = 1;
		break;
	default:
		break;
	}

	if (!movX == 0)
	{
		mLastMovement.x = movX;
	}
	if (mLastMovement.x == -1 && mSpeed > 0)
	{
		mSpeed -= mPData.mDeceleration * 50 * dt;
	}
	if (mLastMovement.x == 1 && mSpeed < 0)
	{
		mSpeed += mPData.mDeceleration * 50 * dt;
	}
	if (movX == 0)
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

void Player::Move(sf::Vector2f movement, float dt, int key)
{
	float movX = 0;
	//InputManager::Key Key = InputManager::Key::MAJ;
	InputManager::Key nkey = (InputManager::Key)key;

	switch (nkey)
	{
	case InputManager::Key::Q :
		movX = -1;
		break;
	case InputManager::Key::D:
		movX = 1;
		break;
	default:
		break;
	}

	mSpeed += movX*50*dt*mPData.mAcceleration;

	//Inertia(movement, dt);
	
	bool crouched = Crouch();
	if (crouched)
	{

		if (movX == 1)
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
		else if (movX == -1)
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

void Player::OnUpdate()
{
	float dt = GameManager::Get()->GetDeltaTime();
	InputManager* inp = GameManager::Get()->GetInputManager();

}

Player::~Player()
{
}
