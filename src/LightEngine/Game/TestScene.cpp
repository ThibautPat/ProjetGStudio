#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"

void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();
	
	Player* pEntity = CreateRectEntity<Player>(150, 50, sf::Color::Blue); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(100, 100);

	RectangleEntity* pEntity1 = CreateRectEntity<RectangleEntity>(50, 300, sf::Color::Red);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsKinematic(true);
	pEntity1->SetGravity(false);

	RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Red);
	pEntity2->SetPosition(1200, 300);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);

	RectangleEntity* pEntity3 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Red);
	pEntity3->SetPosition(200, 100);
	pEntity3->SetRigidBody(true);
	pEntity3->SetIsKinematic(true);
	pEntity3->SetGravity(false);

	/*
	for (int i = 0; i <= ENTITY_NB; i++) 
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(400, 400, sf::Color::Red); // Ajout d'autre entit� et setup
		pEntity->SetPosition(i*400 + 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetIsKinematic(true);
		pEntity->SetGravity(true);
	}

	for (int i = 0; i <= ENTITY_NB; i++)
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(100, 500, sf::Color::Red);
		pEntity->SetPosition(i * -400 - 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetIsKinematic(false);
		pEntity->SetGravity(true);
	}
	*/
}

void TestScene::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene::OnUpdate()
{

	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		if (dynamic_cast<Player*>(entity))
		{
			mView->setCenter(entity->GetPosition(0.f, 0.f).x + 200, entity->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame 
		}

		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		if (cooEntity.y + entity->GetShape()->getGlobalBounds().height * 0.5f > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(cooEntity.x, 720 - entity->GetShape()->getGlobalBounds().height * 0.5f, 0.f, 0.f);
		}

		// Affichage de quelque informations
		std::string textCox = std::to_string(cooEntity.x) + " x ";
		std::string textCoy = std::to_string(cooEntity.y) + " y";
		Debug::DrawText(cooEntity.x, cooEntity.y, textCox, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 20, textCoy, sf::Color::White);
		Debug::DrawCircle(cooEntity.x, cooEntity.y, 5, sf::Color::White);

		std::string textSpeed = std::to_string(entity->GetGravitySpeed());		
		Debug::DrawText(cooEntity.x, cooEntity.y + 50, textSpeed, sf::Color::White);
	}
	Debug::ShowFPS(mView->getCenter().x - GetWindowWidth() / 2 + 10, mView->getCenter().y - GetWindowHeight() / 2 + 10);
	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
