#include "Player.h"
#include "../Core/InputManager.h"
#include "../Core/AssetsManager.h"

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
	if (IsOnGround() == false)
		return;

	mGravitySpeed = -mPData.mJumpHeight;
	mBoolGravity = true;
}

void Player::Move(sf::Vector2f movement, float dt)
{
	mSpeed += movement.x*50*dt*mPData.mAcceleration;

	Inertia(dt, movement);
	
	if (Crouch())
	{

		if (movement.x == 1)
		{
			if (mSpeed > 0)
				mSpeed -= mPData.mMaxSpeed * dt;

			if (mSpeed > 10000)
				mSpeed -= mPData.mMaxSpeed* dt*2;

			if (mSpeed < 11000 && mSpeed > 9000)
				mSpeed = 10000;
		}
		else if (movement.x == -1)
		{
			if (mSpeed < 0)
				mSpeed += mPData.mMaxSpeed * dt;

			if (mSpeed < -10000)
				mSpeed += mPData.mMaxSpeed * dt*2;

			if (mSpeed > -11000 && mSpeed < -9000)
				mSpeed = -10000;
		}
		
	}

	if (mSpeed > 20000)
		mSpeed = 20000;

	if (mSpeed < -20000)
		mSpeed = -20000;

	SetDirection(dt,0, mSpeed);
}

bool Player::Crouch()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
		return true;

	return false;
}

void Player::OnInitialize()
{
	AssetsManager* assetsManager = GameManager::Get()->mAs;
	std::string tmName = "tilemap";
	mText = assetsManager->Load("../../../res/Assets/Tilemap/tilemap_packed.png", tmName);

	assetsManager->SetTexture(tmName, this, sf::IntRect(0, 0, 18*4, 18*4));
}

void Player::OnUpdate()
{
	int rdm_x = std::rand() % (18 * 9) + 0;
	int rdm_y = std::rand() % (18 * 3) + 0;

	AssetsManager* assetsManager = GameManager::Get()->mAs;
	std::string tmName = "tilemap";
	//assetsManager->SetTexture(tmName, this, sf::IntRect(18 * rdm_x, 18 * rdm_y, 18 * 4, 18 * 4));
}

void Player::SetTexture(sf::Texture* text)
{
	mText = text;
}

Player::~Player()
{
}
