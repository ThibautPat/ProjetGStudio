#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"

void TestScene::OnInitialize()
{
	for (int i = 0; i < ENTITY_NB; i++)
	{
		Entity* pEntity = CreateEntity<Entity>(100, sf::Color::Red);
		pEntity->SetPosition(i*200 + 200, 720);
		pEntity->SetRigidBody(true);
		pEntity->SetGravity(false);

	}

	Entity* pEntity = CreateEntity<Entity>(100, sf::Color::Red);
	pEntity->SetPosition(300, 500);
	pEntity->SetRigidBody(true);
	pEntity->SetTag(1);
	pEntity->mVelocityMax = 500;

	mGm = GameManager::Get();
}

void TestScene::OnEvent(const sf::Event& event)
{
	//#TODO

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			std::list<Entity*> entities = mGm->GetEntities<Entity>();

			for (Entity* entity : entities)
			{
				/*
				if (entity->GetDirection().x > mVelocityMax)

				float dir = entity->GetDirection().x;
				entity->SetDirection(dir - 100, 0, 0);

				
				if(entity->GetDirection().x == 1)
					entity->mVelocitySpeed = 0;

				sf::Vector2f co = entity->GetPosition();
				if (entity->mVelocitySpeed < entity->mVelocityMax) {
					entity->mVelocitySpeed += 100;
				}
				
				entity->SetDirection(-1, 0, 0);
				*/
			}
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			std::list<Entity*> entities = mGm->GetEntities<Entity>();

			for (Entity* entity : entities)
			{
				/*
				float dir = entity->GetDirection().x;
				entity->SetDirection(dir + 100, 0, 0);

				
				if (entity->GetDirection().x == -1)
					entity->mVelocitySpeed = 0;

				sf::Vector2f co = entity->GetPosition();
				if (entity->mVelocitySpeed < entity->mVelocityMax) {
					entity->mVelocitySpeed += 100;
				}
				entity->SetDirection(1, 0, 0);
				*/
			}
		}
	}
}

void TestScene::OnUpdate()
{
	std::list<Entity*> entities = mGm->GetEntities<Entity>();

	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();

		if (co.y + entity->GetRadius() > 720)
		{
			entity->mBoolGravity = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			entity->mBoolGravity = 1;
			entity->mGravitySpeed = -500;
		}

		std::string gravsp = std::to_string((int)entity->mGravitySpeed) + " grav speed";
		Debug::DrawText(co.x - entity->GetRadius()/2, co.y , gravsp, sf::Color::White);
		std::string velo = std::to_string((int)entity->GetDirection().x) + " velo speed";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 20, velo, sf::Color::White);
		std::string grav = std::to_string(entity->mBoolGravity) + " grav";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 40, grav, sf::Color::White);
	}

	Debug::ShowFPS();
}
