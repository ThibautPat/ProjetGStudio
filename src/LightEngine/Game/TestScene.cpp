#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "../Core/InputManager.h"

void TestScene::OnInitialize()
{
	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue);
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);

	for (int i = 0; i <= ENTITY_NB; i++) 
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(500, 500, sf::Color::Red);
		pEntity->SetPosition(i*400 + 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetGravity(true);
	}

	mGm = GameManager::Get();
	mInp = GameManager::Get()->GetInputManager();
}

void TestScene::OnEvent(const sf::Event& event)
{
	//#TODO
}

void TestScene::OnUpdate()
{
	std::list<Entity*> entities = mGm->GetEntities<Entity>();

	for (Entity* entity : entities)
	{
		if (dynamic_cast<Player*>(entity))
		{
			if(mInp->GetInput().y == -1)
				dynamic_cast<Player*>(entity)->Jump(); 

			dynamic_cast<Player*>(entity)->Move(mInp->GetInput(), GetDeltaTime());
		}

		sf::Vector2f co = entity->GetPosition(0.f, 0.f);

		std::string grav = std::to_string(co.x) + " : x		" + std::to_string(co.y) + " : y";
		Debug::DrawText(co.x, co.y, grav, sf::Color::White);

		Debug::DrawCircle(co.x, co.y, 5, sf::Color::White);

		if (co.y + entity->GetShape()->getGlobalBounds().height * 0.5f > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(co.x, 720 - entity->GetShape()->getGlobalBounds().height * 0.5f, 0.f, 0.f);
		}
		else if (co.y + entity->GetShape()->getGlobalBounds().height * 0.5f < 720)
			entity->SetGravity(true);
	}


	//DEBUG
	//for (Entity* entity : entities)
	//{
	//	sf::Vector2f co = entity->GetPosition(0.5f, 0.5f);
	//	int lisibleSpeed = (int)entity->GetSpeed();
	//	lisibleSpeed = lisibleSpeed / 100;
	//	std::string gravsp = std::to_string((int)entity->GetGravitySpeed()) + " grav speed";
	//	Debug::DrawText(co.x, co.y , gravsp, sf::Color::White);
	//	std::string velo = std::to_string(lisibleSpeed) + " velo speed";
	//	Debug::DrawText(co.x, co.y + 20, velo, sf::Color::White);
	//	std::string grav = std::to_string(entity->IsOnGround()) + " on ground";
	//	Debug::DrawText(co.x, co.y + 40, grav, sf::Color::White);
	//}
	Debug::ShowFPS();
}
