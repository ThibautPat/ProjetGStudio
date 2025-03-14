#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
#include "SFML/Graphics.hpp"

void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();
	
	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(false);
	pEntity->SetPosition(100, 100);


	for (int i = 0; i <= ENTITY_NB; i++)
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(300, 300, sf::Color::Red);
		pEntity->SetPosition(i * 400 + 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetIsKinematic(true);
		pEntity->SetGravity(true);
	}

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
			sf::Vector2f notcenter = m_InstanceGameManager->GetScene()->GetView()->getSize();
			notcenter.x /= 5;
			notcenter.y /= 10;
			sf::Vector2f pos = sf::Vector2f(entity->GetPosition(0.f, 0.f).x + notcenter.x, entity->GetPosition(0.f, 0.f).y - notcenter.y);
			mCam->GoTo(pos);
			//mView->setRotation(90);
			//mView->setCenter(entity->GetPosition(0.f, 0.f).x + 200, entity->GetPosition(0.f, 0.f).y - 115); //Ancien repositionnement de la cam�ra sur le joueur chaque frame 
			//mCam->Zoom(0.99, 0.99); //Test avec le zoom (ne pas utiliser à chaque frame)
			//mCam->SetZoom(1, 1); //Test avec le zoom et le notcenter (decalage du personnage pour qu'il ne soit pas centre) VALIDE
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
	}
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);
	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
