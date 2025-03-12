#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"

void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la caméra
	m_InstanceGameManager = GameManager::Get();
	
	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(100, 100);

	for (int i = 0; i <= ENTITY_NB; i++) 
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(400, 400, sf::Color::Red); // Ajout d'autre entité et setup
		pEntity->SetPosition(i*400 + 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetIsKinematic(true);
		pEntity->SetGravity(true);
	}
}

void TestScene::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene::OnUpdate()
{

	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilité de ne pas call la view chaque frame

	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entités du gameManager
	{
		if (dynamic_cast<Player*>(entity))
		{
			mView->setCenter(entity->GetPosition(0.f, 0.f).x + 200, entity->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la caméra sur le joueur chaque frame 
		}

		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		if (cooEntity.y + entity->GetShape()->getGlobalBounds().height * 0.5f > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(cooEntity.x, 720 - entity->GetShape()->getGlobalBounds().height * 0.5f, 0.f, 0.f);
		}

		// Affichage de quelque informations
		std::string textCox = std::to_string(cooEntity.x) + " x ";
		std::string textCoy = std::to_string(cooEntity.y) + " : y";
		Debug::DrawText(cooEntity.x, cooEntity.y, textCox, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 20, textCoy, sf::Color::White);
		Debug::DrawCircle(cooEntity.x, cooEntity.y, 5, sf::Color::White);
	}
	Debug::ShowFPS(mView->getCenter().x - GetWindowWidth() / 2 + 10, mView->getCenter().y - GetWindowHeight() / 2 + 10);
}
