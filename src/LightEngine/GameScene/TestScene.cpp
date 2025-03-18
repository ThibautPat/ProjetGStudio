#include "TestScene.h"

#include "../Entity/Entity.h"
#include "../Other/Debug.h"
#include <iostream>
#include "../GameEntity/Player.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"

//TODO in player class ----------
void TestScene::PlayerDeath()
{
		RespawnClock.restart(); // On restart le timer de respawn
		playerIsDead = true;
		//m_InstanceGameManager->GetSceneManager()->SelectScene("testscene2");
}
//---------------------------------

//TODO in player class ----------
void TestScene::PlayerRespawn()
{

	if (playerIsDead) // Si le joueur est mort
	{
		mPlayer->SetSpeed(0); // On reset la vitesse du joueur
		mPlayer->SetGravitySpeed(0); // On reset la vitesse de gravit� du joueur
		mPlayer->SetPosition(mLastCheckPoint.x, mLastCheckPoint.y); // On respawn le joueur au dernier checkpoint
		if (RespawnClock.getElapsedTime().asSeconds() > 5) // Si le joueur est mort depuis plus de 5 seconde
		{
			mPlayer->SetGravity(true); // On r�active la gravit� 
			playerIsDead = false;
		}
	}
}
//---------------------------------


void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();
	
	RectangleEntity* Checkpoint2 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint2->SetPosition(300, 670);
	Checkpoint2->SetRigidBody(false);
	Checkpoint2->SetIsKinematic(true);
	Checkpoint2->SetGravity(false);
	Checkpoint2->SetTag(Tag::CHECKPOINT);

	RectangleEntity* Checkpoint1 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint1->SetPosition(-100, 670);
	Checkpoint1->SetRigidBody(false);
	Checkpoint1->SetIsKinematic(true);
	Checkpoint1->SetGravity(false);
	Checkpoint1->SetTag(Tag::CHECKPOINT);

	RectangleEntity* DeadlyObstacle1 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Green); // Ajout du DeadlyObstacle et setup
	DeadlyObstacle1->SetPosition(900, 670);
	DeadlyObstacle1->SetRigidBody(false);
	DeadlyObstacle1->SetIsKinematic(true);
	DeadlyObstacle1->SetGravity(false);
	DeadlyObstacle1->SetTag(Tag::DEADLYOBSTACLE);

	mPlayer = CreateRectEntity<Player>(100, 100, sf::Color::Blue); // Ajout du Player et setup
	mPlayer->SetGravity(true);
	mPlayer->SetRigidBody(true);
	mPlayer->SetIsKinematic(false);
	mPlayer->SetPosition(0, 0);
	mPlayer->SetTag(Tag::PLAYER);

	RectangleEntity* pEntity6 = CreateRectEntity<RectangleEntity>(150, 150, sf::Color::Magenta); // Ajout d'un obstacle à déplacer
	pEntity6->SetGravity(true);
	pEntity6->SetRigidBody(true);
	pEntity6->SetIsKinematic(false);
	pEntity6->SetPosition(350, -200);
	pEntity6->SetTag(Tag::OBSTACLE);

	RectangleEntity* pEntity1 = CreateRectEntity<RectangleEntity>(50, 300, sf::Color::Cyan);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsKinematic(true);
	pEntity1->SetGravity(false);
	pEntity1->SetTag(Tag::PLATFORM);

	RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Cyan);
	pEntity2->SetPosition(1200, 300);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);
	pEntity2->SetTag(Tag::PLATFORM);

	RectangleEntity* pEntity3 = CreateRectEntity<RectangleEntity>(50, 500, sf::Color::Cyan);
	pEntity3->SetPosition(200, 100);
	pEntity3->SetRigidBody(true);
	pEntity3->SetIsKinematic(true);
	pEntity3->SetGravity(false);
	pEntity3->SetTag(Tag::PLATFORM);

	RectangleEntity* Ground = CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3220);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);
	Ground->SetTag(Tag::PLATFORM);

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
}

void TestScene::OnEvent(const sf::Event& event)
{	
	//TODO Refaire la pause coter moteur
}

void TestScene::OnUpdate()
{
	int i = 0;
	PlayerRespawn();

	mView->setCenter(mPlayer->GetPosition(0.f, 0.f).x + 200, mPlayer->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame 
	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		i++;
		if (entity->IsTag(Tag::CHECKPOINT))
		{
			if (mPlayer->GetShape()->getGlobalBounds().intersects(entity->GetShape()->getGlobalBounds())) // Si le joueur touche le checkpoint
			{
				mLastCheckPoint = entity->GetPosition(0.f, 0.f); // On set le dernier checkpoint
			}
		}
		if (entity->IsTag(Tag::DEADLYOBSTACLE))
		{
			if (mPlayer->GetShape()->getGlobalBounds().intersects(entity->GetShape()->getGlobalBounds())) // Si le joueur touche le DeadlyObstacle
			{
				PlayerDeath(); // Le joueur meurt
			}
			//--------------------------------
		}
		if (entity->IsTag(Tag::END_LEVEL))
		{

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

		if (entity == mPlayer) {
			std::string textJump = std::to_string(mPlayer->GetSecondJump()) + " jumps";
			Debug::DrawText(cooEntity.x, cooEntity.y + 60, textJump, sf::Color::White);
		}
	}

	std::string entitynb = std::to_string(i) + "nb entity";
	Debug::DrawText(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 40, entitynb, sf::Color::White);
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);
	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
