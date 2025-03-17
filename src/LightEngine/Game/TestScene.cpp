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

	// Accéder aux données JSON
	for (int i = 0; i < donnees["Rows"]; i++) {
		for (int j = 0; j < donnees["Columns"]; j++)
			if (donnees["Cases"][i][j] == "PL") { // Si la case est un Player
				Player* pEntity1 = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
				pEntity1->SetGravity(true);
				pEntity1->SetRigidBody(true);
				pEntity1->SetIsKinematic(false);
				pEntity1->SetPosition(100, 100);
			}
	}



	for (int i = 0; i < donnees["Rows"]; i++) {
		for (int j = 0; j < donnees["Columns"]; j++) {
			if (donnees["Cases"][i][j] == "P") { 
				RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Red); // Ajout du DeadlyObstacle et setup
				pEntity->SetGravity(false);
				pEntity->SetRigidBody(true);
				pEntity->SetIsKinematic(true);
				pEntity->SetPosition(j * 100, i * 100);
				pEntity->SetTag(Tag::METALIC_OBSTACLE);
			}

			if (donnees["Cases"][i][j] == "C") { // Si la case est un Checkpoint
				Checkpoint* pEntity = CreateRectEntity<Checkpoint>(i * 100, j * 100, sf::Color::Green); // Ajout du Checkpoint et setup
				pEntity->SetGravity(false);
				pEntity->SetRigidBody(false);
				pEntity->SetIsKinematic(false);
				pEntity->SetPosition(i * 100, j * 100);
			}

			std::cout << donnees["Cases"][i][j] << std::endl;
		}
		//if (donnees["Cases"][i] == "PL") {
		//	Player* pEntity = CreateRectEntity<Player>(donnees["Cases"][i] * 100, donnees["Cases"][i] * 100, sf::Color::Blue); // Ajout du Player et setup
		//	pEntity->SetGravity(true);
		//	pEntity->SetRigidBody(true);
		//	pEntity->SetIsKinematic(false);
		//	pEntity->SetPosition(donnees["Cases"][i] * 100, donnees["Cases"][i] * 100);
		//}
		//else if (donnees["Cases"][i] == "C") {
		//	Checkpoint* pEntity = CreateRectEntity<Checkpoint>(donnees["Cases"][i] * 100, donnees["Cases"][i] * 100, sf::Color::Green); // Ajout du Checkpoint et setup
		//	pEntity->SetGravity(false);
		//	pEntity->SetRigidBody(false);
		//	pEntity->SetIsKinematic(false);
		//	pEntity->SetPosition(donnees["Cases"][i] * 100, donnees["Cases"][i] * 100);
		//}
		//else {
		//	std::cerr << "Erreur : impossible de trouver le type de l'entit�." << std::endl;
		//}
	}
	RectangleEntity* Ground = CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3220);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);
	Ground->SetTag(Tag::OBSTACLE);
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
							//if (!dynamic_cast<Player*>(entity3))
							//entity3->Destroy(); // On d�truit toutes les entit�s
						}
					}
				}
			}
			//--------------------------------
		}

		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		// Affichage de quelque informations
		std::string textCox = std::to_string((int)cooEntity.x) + " x ";
		std::string textCoy = std::to_string((int)cooEntity.y) + " y";
		std::string textgrav = std::to_string((int)entity->GetGravitySpeed()) + " grav";
		Debug::DrawText(cooEntity.x, cooEntity.y, textCox, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 20, textCoy, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 40, textgrav, sf::Color::White);
		Debug::DrawCircle(cooEntity.x, cooEntity.y, 5, sf::Color::White);

	}
	std::string entitynb = std::to_string(i) + "nb entity";
	Debug::DrawText(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 40, entitynb, sf::Color::White);
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);
	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
