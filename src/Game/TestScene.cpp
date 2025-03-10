#include "TestScene.h"

#include "../LightEngine/Entity.h"
#include <iostream>
#include "../LightEngine/Debug.h"

void TestScene::OnInitialize()
{
	for (int i = 0; i < ENTITY_NB; i++)
	{
		Entity* pEntity = CreateEntity<Entity>(100, sf::Color::Red);
		pEntity->SetPosition(i*100 + 100, i*500 + 500);
		pEntity->SetRigidBody(true);

	}

	mGm = GameManager::Get();
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::KeyPressed) {

		//#TODO
		if (event.KeyPressed == sf::Keyboard::Left)
		{

		}
	}
}

void TestScene::OnUpdate()
{
	std::list<Entity*> entities = mGm->GetEntities<Entity>();


	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();

		//#TODo def outoufbound
		if (co.y + entity->GetRadius() > 800) {
			entity->ResetGravity();
		}

		std::string msg = std::to_string((int)entity->mGravitySpeed) + " pixel/s";
		Debug::DrawText(co.x - entity->GetRadius()/2, co.y , msg, sf::Color::White);
	}

	Debug::ShowFPS();
}
