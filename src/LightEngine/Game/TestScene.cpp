#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"

void TestScene::OnInitialize()
{
	for (int i = 0; i <= ENTITY_NB; i++)
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

			Entity* p = mGm->GetEntity<Entity>(1);

			if (p->GetDirection().x > -p->mVelocityMax)
			{
				float dir = p->GetDirection().x;
				p->SetDirection(dir - 100, 0, 0);
			}
		}

		if (event.key.code == sf::Keyboard::Right)
		{

			Entity* p = mGm->GetEntity<Entity>(1);

			if (p->GetDirection().x < p->mVelocityMax)
			{
				float dir = p->GetDirection().x;
				p->SetDirection(dir + 100, 0, 0);
			}
		}

		if (event.key.code == sf::Keyboard::Space)
		{
			Entity* p = mGm->GetEntity<Entity>(1);

			if (p->mBoolGravity != true)
			{
			p->mBoolGravity = 1;
			p->mGravitySpeed = -500;
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

		if (co.y + entity->GetRadius() > 720 && entity->mGravitySpeed > 0)
		{
			entity->mBoolGravity = 0;
			entity->mGravitySpeed = 0;
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
