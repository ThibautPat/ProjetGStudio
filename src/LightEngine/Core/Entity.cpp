#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"
#include "CircleCollider.h"
#include "AABBCollider.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	x -= mSizeX * ratioX;
	y -= mSizeY * ratioY;

	GetShape()->setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.f, 0.f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY)
{
	sf::Vector2f position = GetShape()->getPosition();

	position.x += mSizeX * ratioX;
	position.y += mSizeY * ratioY;

	return position;
}

void Entity::Fall(float dt)
{
	if (mBoolGravity == false)
		return;

	if (mGravitySpeed >= 2000.f)
		return;

	if (sf::Joystick::isButtonPressed(0, 4))
	{
		mGravitySpeed -= GRAVITYACCEL + dt;
	}
	else
	{
		mGravitySpeed += GRAVITYACCEL + dt;
	}


	sf::Vector2f co = GetShape()->getPosition();
	co.y += mGravitySpeed * dt;
	GetShape()->setPosition(co);
}


bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.f, 0.f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.f, 0.f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{
	sf::Vector2f oldPos = GetPosition(0.f, 0.f);

	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	GetShape()->move(translation);

	if (mTarget.isSet) 
	{
		


		float x1 = GetPosition(0.f, 0.f).x;
		float y1 = GetPosition(0.f, 0.f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		//TODO : enlever les draws

		//Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		//Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 1.f, 1.f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	/*
	for (Entity* entity : GameManager::Get()->GetEntities<Entity>())
	{
		if (entity == this)
			continue;

		if (IsColliding(entity))
		{
			SetPosition(oldPos.x, oldPos.y, 0.f, 0.f);
			mSpeed = 0.f;
			mDirection.x = 0.f;
			std::cout << "COLLISION PREV" << std::endl;
			break;
		}
	}
	*/

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}