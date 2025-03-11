#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
void TestScene::OnInitialize()
{
	mView = sf::View(sf::FloatRect(0, 0, 1280, 720));
	
	

	Player* pEntity = CreateEntity<Player>(100, sf::Color::Red);
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetPosition(600, 100);

	Entity* pEntity2 = CreateEntity<Entity>(100, sf::Color::Green);
	pEntity2->SetGravity(true);
	pEntity2->SetRigidBody(true);
	pEntity2->SetPosition(300, 100);

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
				
			}
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			std::list<Entity*> entities = mGm->GetEntities<Entity>();

			for (Entity* entity : entities)
			{
				
			}
		}
	}
}

void TestScene::OnUpdate()
{
	std::list<Entity*> entities = mGm->GetEntities<Entity>();

	for (Entity* entity : entities)
	{
		if (dynamic_cast<Player*>(entity))
		{
			mView.setCenter(entity->GetPosition());
			dynamic_cast<Player*>(entity)->Jump(GetDeltaTime()); 
			dynamic_cast<Player*>(entity)->Move(dynamic_cast<Player*>(entity)->InputDirection(), GetDeltaTime()); 
		}
	}

	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();
		if (co.y + entity->GetRadius() > 720)
		{
			entity->mBoolGravity = 0;
			entity->SetPosition(co.x, 720 - entity->GetRadius() - 1);
			(entity)->secondjump = 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			entity->mBoolGravity = 1;
			entity->mGravitySpeed = -500;
		}
		int lisibleSpeed = (int)entity->mSpeed;
		lisibleSpeed = lisibleSpeed / 100;
		std::string gravsp = std::to_string((int)entity->mGravitySpeed) + " grav speed";
		Debug::DrawText(co.x - entity->GetRadius()/2, co.y , gravsp, sf::Color::White);
		std::string velo = std::to_string(lisibleSpeed) + " velo speed";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 20, velo, sf::Color::White);
		std::string grav = std::to_string(entity->mBoolGravity) + " grav";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 40, grav, sf::Color::White);
	}
	mGm->GetWindow()->setView(mView);
	Debug::ShowFPS(mView.getCenter().x - GetWindowWidth()/2 + 10, mView.getCenter().y - GetWindowHeight()/2+10);
}
