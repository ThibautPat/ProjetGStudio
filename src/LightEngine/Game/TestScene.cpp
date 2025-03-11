#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "../Core/InputManager.h"

void TestScene::OnInitialize()
{
	
	Player* pEntity = CreateEntity<Player>(100, sf::Color::Red);
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);

	for (int i = 0; i <= ENTITY_NB; i++) 
	{
		Entity* pEntity = CreateEntity<Entity>(100, sf::Color::Red);
		pEntity->SetPosition(i*200 + 200, 0);
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
			Player* p = dynamic_cast<Player*>(entity);
			if(mInp->GetInput() == InputManager::Key::Espace)
				p->Jump();

			if(mInp->GetInput() == InputManager::Key::Q || mInp->GetInput() == InputManager::Key::D)
				p->Move(sf::Vector2f(), GetDeltaTime(), (int)mInp->GetInput());

			p->Inertia((int)mInp->GetInput(), sf::Vector2f(), GetDeltaTime());


		}

		sf::Vector2f co = entity->GetPosition();
		if (co.y + entity->GetRadius() > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(co.x, 720 - entity->GetRadius() - 1);
		}
	}


	//DEBUG
	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();
		int lisibleSpeed = (int)entity->GetSpeed();
		lisibleSpeed = lisibleSpeed / 100;
		std::string gravsp = std::to_string((int)entity->GetGravitySpeed()) + " grav speed";
		Debug::DrawText(co.x - entity->GetRadius()/2, co.y , gravsp, sf::Color::White);
		std::string velo = std::to_string(lisibleSpeed) + " velo speed";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 20, velo, sf::Color::White);
		std::string grav = std::to_string(entity->IsOnGround()) + " on ground";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 40, grav, sf::Color::White);
	}
	Debug::ShowFPS();
}
