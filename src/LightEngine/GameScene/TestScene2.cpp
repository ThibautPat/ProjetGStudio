#include "TestScene2.h"

#include "../Entity/Entity.h"
#include "../Other/Debug.h"
#include <iostream>
#include "../GameEntity/Player.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"

//TODO in player class ----------
void TestScene2::PlayerDeath()
{
		RespawnClock.restart();
		playerIsDead = true;
		m_InstanceGameManager->GetSceneManager()->SelectScene("testscene");
}
//---------------------------------

//TODO in player class ----------
void TestScene2::PlayerRespawn()
{

	if (playerIsDead) // Si le joueur est mort
	{
		for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
		{
			if (dynamic_cast<Player*>(entity))
			{
				entity->SetSpeed(0); // On reset la vitesse du joueur
				entity->SetGravitySpeed(0); // On reset la vitesse de gravit� du joueur
				entity->SetPosition(mLastCheckPoint.x, mLastCheckPoint.y); // On respawn le joueur au dernier checkpoint
				if (RespawnClock.getElapsedTime().asSeconds() > 5) // Si le joueur est mort depuis plus de 5 seconde
				{
					entity->SetGravity(true); // On r�active la gravit� 
					playerIsDead = false;
				}
			}
		}
	}
}
//---------------------------------


void TestScene2::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();

	//Checkpoint* Checkpoint2 = CreateRectEntity<Checkpoint>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	//Checkpoint2->SetPosition(300, 670);
	//Checkpoint2->SetRigidBody(false);
	//Checkpoint2->SetIsKinematic(true);
	//Checkpoint2->SetGravity(false);

	//Checkpoint* Checkpoint1 = CreateRectEntity<Checkpoint>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	//Checkpoint1->SetPosition(-100, 670);
	//Checkpoint1->SetRigidBody(false);
	//Checkpoint1->SetIsKinematic(true);
	//Checkpoint1->SetGravity(false);

	//DeadlyObstacle* DeadlyObstacle1 = CreateRectEntity<DeadlyObstacle>(100, 100, sf::Color::Green); // Ajout du DeadlyObstacle et setup
	//DeadlyObstacle1->SetPosition(900, 670);
	//DeadlyObstacle1->SetRigidBody(false);
	//DeadlyObstacle1->SetIsKinematic(true);
	//DeadlyObstacle1->SetGravity(false);

	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(100, 100);
}

void TestScene2::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene2::OnUpdate()
{
	int i = 0;
	PlayerRespawn();
	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		i++;
		if (dynamic_cast<Player*>(entity))
		{
			mView->setCenter(entity->GetPosition(0.f, 0.f).x + 200, entity->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame

			//TODO in player class ----------
			for (Entity* entity2 : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
			{
				if (dynamic_cast<Checkpoint*>(entity2))
				{
					if (entity->GetShape()->getGlobalBounds().intersects(entity2->GetShape()->getGlobalBounds())) // Si le joueur touche le checkpoint
					{
						mLastCheckPoint = entity2->GetPosition(0.f, 0.f); // On set le dernier checkpoint
					}
				}
				if (dynamic_cast<DeadlyObstacle*>(entity2))
				{
					if (entity->GetShape()->getGlobalBounds().intersects(entity2->GetShape()->getGlobalBounds())) // Si le joueur touche le DeadlyObstacle
					{
						PlayerDeath(); // Le joueur meurt
					}
				}
			}
			//--------------------------------
		}

		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		if (cooEntity.y + entity->GetShape()->getGlobalBounds().height * 0.5f > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(cooEntity.x, 720 - entity->GetShape()->getGlobalBounds().height * 0.5f, 0.f, 0.f);
		}

		// Affichage de quelque informations
		std::string textCox = std::to_string((int)cooEntity.x) + " x ";
		std::string textCoy = std::to_string((int)cooEntity.y) + " y";
		std::string textgrav = std::to_string((int)entity->GetGravitySpeed()) + " grav";
		Debug::DrawText(cooEntity.x, cooEntity.y, textCox, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 20, textCoy, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 40, textgrav, sf::Color::White);
		Debug::DrawCircle(cooEntity.x, cooEntity.y, 5, sf::Color::White);

		std::string entitynb = std::to_string(i) + "nb entity";
		Debug::DrawText(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 40, entitynb, sf::Color::White);
		Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);
	}
	
	m_InstanceGameManager->GetWindow()->setView(*mView);
}
