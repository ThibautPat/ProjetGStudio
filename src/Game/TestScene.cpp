#include "TestScene.h"

#include "../LightEngine/Entity.h"
#include <iostream>
#include "../LightEngine/Debug.h"

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

	mGm = GameManager::Get();
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::KeyPressed) {

		//#TODO
		Entity* p = mGm->GetEntity<Entity>(1);


		if (event.KeyPressed == sf::Keyboard::Left)
		{
			p->SetPosition(p->GetPosition().x-10, p->GetPosition().y);
		}
	}
}

void TestScene::OnUpdate()
{
	std::list<Entity*> entities = mGm->GetEntities<Entity>();


	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();

		//#TODO def outoufbound
		if (co.y + entity->GetRadius() > 900) {
			entity->ResetGravity();
		}

		std::string speed = std::to_string((int)entity->mGravitySpeed) + " grav speed";
		Debug::DrawText(co.x - entity->GetRadius()/2, co.y , speed, sf::Color::White);
		std::string grav = std::to_string(entity->mGravity) + " grav";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 20, grav, sf::Color::White);
	}

	Debug::ShowFPS();
}
