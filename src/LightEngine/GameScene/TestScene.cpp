#include "TestScene.h"

#include "../Entity/Entity.h"
#include "../Other/Debug.h"
#include <iostream>
#include "../GameEntity/Player.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"
#include "../GameEntity/BackGround.h"

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
	mView = new sf::View(sf::FloatRect(0, -340, GetWindowWidth()+56.25f, GetWindowHeight()+100)); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();


	BackGround* pEntity7 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity7->SetPosition(0, 205); 
	pEntity7->SetRigidBody(false);
	pEntity7->SetIsKinematic(true);
	pEntity7->SetGravity(false);
	pEntity7->SetBackGroundTexture("..//..//..//res//Assets//Background//sky_mercure.png");
	pEntity7->SetTag(Tag::BACK_GROUND1);

	BackGround* pEntity8 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity8->SetPosition(mView->getCenter().x, 205);
	pEntity8->SetRigidBody(false);
	pEntity8->SetIsKinematic(true);
	pEntity8->SetGravity(false);
	pEntity8->SetBackGroundTexture("..//..//..//res//Assets//Background//upsky_background_mercure.png");
	pEntity8->SetTag(Tag::BACK_GROUND2BIS);

	BackGround* pEntity9 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity9->SetPosition(mView->getCenter().x-30, 205);
	pEntity9->SetRigidBody(false);
	pEntity9->SetIsKinematic(true);
	pEntity9->SetGravity(false);
	pEntity9->SetBackGroundTexture("..//..//..//res//Assets//Background//upsky_background_mercure.png");
	pEntity9->SetTag(Tag::BACK_GROUND2);

	Player* pEntity = CreateRectEntity<Player>(256, 128, sf::Color::Transparent); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(0, 0);

	RectangleEntity* Ground = CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3250);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);



	RectangleEntity* pEntity3 = CreateRectEntity<RectangleEntity>(2000, 100, sf::Color::Transparent);
	pEntity3->SetPosition(-3300, 0);
	pEntity3->SetRigidBody(true);
	pEntity3->SetIsKinematic(true);
	pEntity3->SetGravity(false);
	pEntity3->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity4 = CreateRectEntity<RectangleEntity>(2000, 200, sf::Color::Transparent);
	pEntity4->SetPosition(4850, 0);
	pEntity4->SetRigidBody(true);
	pEntity4->SetIsKinematic(true);
	pEntity4->SetGravity(false);
	pEntity4->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity6 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::White);
	pEntity6->SetPosition(-400, 0);
	pEntity6->SetRigidBody(true);
	pEntity6->SetIsKinematic(true);
	pEntity6->SetGravity(false); 
	pEntity6->SetTag(Tag::BOUCING_OBSTACLE);

	RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Green);
	pEntity2->SetPosition(100, 0);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);
	pEntity2->SetTag(Tag::METALIC_OBSTACLE);

}

void TestScene::OnEvent(const sf::Event& event)
{	
	
}

void TestScene::OnUpdate()
{
	

	int i = 0;
	PlayerRespawn();
	bool screenTouched = false;
	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		i++;
		if (dynamic_cast<Player*>(entity))
		{
			if (entity->GetPosition(0.f, 0.f).x > -2450 && entity->GetPosition(0.f, 0.f).x < 3550)
			{
				mView->setCenter(entity->GetPosition(0.f, 0.f).x + 200, mView->getCenter().y); //Repositionnement de la cam�ra sur le joueur chaque frame

			}
			else
			{
				screenTouched = true;
			}
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
				if (dynamic_cast<BackGround*>(entity2))
				{

					if (entity2->IsTag(Tag::BACK_GROUND1)&& !screenTouched) 
						entity2->SetPosition(mView->getCenter().x - entity->GetPosition(0,0).x/8 -100, 205);
					for (Entity* entity3 : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
					{
						if (entity2->IsTag(Tag::BACK_GROUND2BIS) && entity->GetPosition(0, 0).x > entity3->GetPosition(0, 0).x && entity3->IsTag(Tag::BACK_GROUND2) && !screenTouched)
							entity2->SetPosition(mView->getCenter().x - entity->GetPosition(0, 0).x + entity2->GetShape()->getGlobalBounds().width*1.227f, 205);
						else if (entity2->IsTag(Tag::BACK_GROUND2BIS) && entity->GetPosition(0, 0).x < entity3->GetPosition(0, 0).x && entity3->IsTag(Tag::BACK_GROUND2) && !screenTouched)
							entity2->SetPosition(mView->getCenter().x - entity->GetPosition(0, 0).x - entity2->GetShape()->getGlobalBounds().width/1.294f, 205);
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
