#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "../Game/Checkpoint.h"
#include "../Game/DeadlyObstacle.h"
#include "../Game/Moving_Platform.h"

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

	Checkpoint* Checkpoint2 = CreateRectEntity<Checkpoint>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint2->SetPosition(300, 670);
	Checkpoint2->SetRigidBody(false);
	Checkpoint2->SetIsKinematic(true);
	Checkpoint2->SetGravity(false);

	Checkpoint* Checkpoint1 = CreateRectEntity<Checkpoint>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint1->SetPosition(-100, 670);
	Checkpoint1->SetRigidBody(false);
	Checkpoint1->SetIsKinematic(true);
	Checkpoint1->SetGravity(false);

	DeadlyObstacle* DeadlyObstacle1 = CreateRectEntity<DeadlyObstacle>(100, 100, sf::Color::Red); // Ajout du DeadlyObstacle et setup
	DeadlyObstacle1->SetPosition(900, 670);
	DeadlyObstacle1->SetRigidBody(false);
	DeadlyObstacle1->SetIsKinematic(true);
	DeadlyObstacle1->SetGravity(false);

	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(100, 100);

	RectangleEntity* pEntity1 = CreateRectEntity<RectangleEntity>(50, 300, sf::Color::Cyan);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsKinematic(true);
	pEntity1->SetGravity(false);
	pEntity1->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Cyan);
	pEntity2->SetPosition(1200, 300);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);
	pEntity2->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity3 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Cyan);
	pEntity3->SetPosition(200, 100);
	pEntity3->SetRigidBody(true);
	pEntity3->SetIsKinematic(true);
	pEntity3->SetGravity(false);
	pEntity3->SetTag(Tag::OBSTACLE);

	RectangleEntity* Ground = CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3220);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);
	Ground->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity4 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::White);
	pEntity4->SetPosition(100, 260);
	pEntity4->SetRigidBody(true);
	pEntity4->SetIsKinematic(true);
	pEntity4->SetGravity(false);
	pEntity4->SetTag(Tag::METALIC_OBSTACLE);

	RectangleEntity* pEntity5 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::White);
	pEntity5->SetPosition(-400, 670);
	pEntity5->SetRigidBody(false);
	pEntity5->SetIsKinematic(true);
	pEntity5->SetGravity(false);
	pEntity5->SetTag(Tag::END_LEVEL);

	Moving_Platform* pEntity6 = CreateRectEntity<Moving_Platform>(100, 200, sf::Color::Cyan);
	pEntity6->SetPosition(-400, 0);
	pEntity6->SetRigidBody(true);
	pEntity6->SetIsKinematic(false);
	pEntity6->SetGravity(false);
	pEntity6->setMaxTravelDistance(300);
	pEntity6->SetStartPosition(pEntity6->GetPosition(0,0));
	pEntity6->SetTag(Tag::OBSTACLE);
}

void TestScene::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene::OnUpdate()
{
	//TODO remove if u want (for debug)
	std::cout << "Scene" << std::endl;

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
							if (!dynamic_cast<Player*>(entity3))
							entity3->Destroy(); // On d�truit toutes les entit�s
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
