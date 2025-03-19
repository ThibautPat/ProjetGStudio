#include "TestScene.h"

#include <fstream>
#include "../nlohmann/json.hpp"
#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "../Game/Checkpoint.h"
#include "../Game/DeadlyObstacle.h"
#include "../nlohmann/json_fwd.hpp"


using json = nlohmann::json;
//TODO in player class ----------
void TestScene::PlayerDeath()
{
		RespawnClock.restart(); // On restart le timer de respawn
		playerIsDead = true;
		m_InstanceGameManager->GetSceneManager()->SelectScene("testscene2");
}
//---------------------------------

//TODO in player class ----------
void TestScene::PlayerRespawn()
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


void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();

	std::ifstream fichier("..//..//..//src//LightEngine//nlohmann//map.json");
	if (!fichier.is_open()) {
		std::cerr << "Erreur : impossible d'ouvrir le fichier JSON." << std::endl;
		return;
	}

	json donnees;
	fichier >> donnees;
	for (int i = 0; i < donnees["Rows"]; i++) {
		for (int j = 0; j < donnees["Columns"]; j++) {

			std::string tmp = donnees["MapPhysics"][i][j];
			int colorR = (int)donnees["Physics"][tmp]["Color"][0];
			int colorG = (int)donnees["Physics"][tmp]["Color"][1];
			int colorB = (int)donnees["Physics"][tmp]["Color"][2];
			int colorA = (int)donnees["Physics"][tmp]["Color"][3];
			if (tmp == "1")
			{
				Player* pEntity1 = CreateRectEntity<Player>(230, 110, sf::Color(colorR, colorG, colorB, colorA));
				pEntity1->SetGravity((bool)donnees["Physics"][tmp]["Gravity"]);
				pEntity1->SetRigidBody((bool)donnees["Physics"][tmp]["RigidBody"]);
				pEntity1->SetIsKinematic((bool)donnees["Physics"][tmp]["IsKinematic"]);
				pEntity1->SetPosition(128 * j, 128 * i);
				pEntity1->SetTag((int)donnees["Physics"][tmp]["Tag"]);
			}
		}
	}
	// Accéder aux données JSON
	for (int i = 0; i < donnees["Rows"]; i++) {
		for (int j = 0; j < donnees["Columns"]; j++) {

			std::string tmp = donnees["MapPhysics"][i][j];
			int colorR = (int)donnees["Physics"][tmp]["Color"][0];
			int colorG = (int)donnees["Physics"][tmp]["Color"][1];
			int colorB = (int)donnees["Physics"][tmp]["Color"][2];
			int colorA = (int)donnees["Physics"][tmp]["Color"][3];
			
			
			if (tmp == "2" || tmp == "7" || tmp == "10" || tmp == "6" || tmp == "8" || tmp == "9" || tmp == "11") // "7" "10" "6" "8" "9" "11
			{
				RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(128, 128, sf::Color(colorR,colorG,colorB,colorA)); 
				pEntity2->SetGravity((bool)donnees["Physics"][tmp]["Gravity"]);
				pEntity2->SetRigidBody((bool)donnees["Physics"][tmp]["RigidBody"]);
				pEntity2->SetIsKinematic((bool)donnees["Physics"][tmp]["IsKinematic"]);
				pEntity2->SetPosition(128 * j, 128 * i);
				pEntity2->SetTag((int)donnees["Physics"][tmp]["Tag"]);
			}
			if (tmp == "0")
			{
				
			}
			if (tmp == "3")
			{
				Checkpoint* pEntity4 = CreateRectEntity<Checkpoint>(128, 128, sf::Color(colorR, colorG, colorB, colorA));
				pEntity4->SetGravity((bool)donnees["Physics"][tmp]["Gravity"]);
				pEntity4->SetRigidBody((bool)donnees["Physics"][tmp]["RigidBody"]);
				pEntity4->SetIsKinematic((bool)donnees["Physics"][tmp]["IsKinematic"]);
				pEntity4->SetPosition(128 * j, 128 * i);
				pEntity4->SetTag((int)donnees["Physics"][tmp]["Tag"]);
			}
			if (tmp == "5")
			{
				DeadlyObstacle* pEntity5 = CreateRectEntity<DeadlyObstacle>(128, 128, sf::Color(colorR, colorG, colorB, colorA));
				pEntity5->SetGravity((bool)donnees["Physics"][tmp]["Gravity"]);
				pEntity5->SetRigidBody((bool)donnees["Physics"][tmp]["RigidBody"]);
				pEntity5->SetIsKinematic((bool)donnees["Physics"][tmp]["IsKinematic"]);
				pEntity5->SetPosition(128 * j, 128 * i);
				pEntity5->SetTag((int)donnees["Physics"][tmp]["Tag"]);
			}

		}
	}	
}

void TestScene::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene::OnUpdate()
{
	//TODO remove if u want (for debug)

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
				if (entity2->IsTag(Tag::END_LEVEL))
				{
					if (entity->GetShape()->getGlobalBounds().intersects(entity2->GetShape()->getGlobalBounds())) // Si le joueur touche la fin du niveau
					{
						for (Entity* entity3 : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
						{
							entity3->Destroy(); // On d�truit toutes les entit�s

						}
						m_InstanceGameManager->GetSceneManager()->SelectScene("testscene2");
					}
				}
			}
			//--------------------------------
		}

		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		// Affichage de quelque informations


	}
	std::string entitynb = std::to_string(i) + "nb entity";
	Debug::DrawText(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 40, entitynb, sf::Color::White);
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);
	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
