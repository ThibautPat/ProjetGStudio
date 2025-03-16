#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "../Core/AudioManager.h"

void TestScene::OnInitialize()
{
	AudioM = new AudioManager();
	std::string* word = new std::string("Test.Wav");
	m_MusicList.push_back(word);

	std::string* word2 = new std::string("Fin");
	m_MusicList.push_back(word2);

	AudioM->AddLevelMusic(m_MusicList);

	AudioM->PlayCurrentMusic();

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

	Debug::ShowFPS();
}
