#include "TestScene.h"

#include "../Entity/Entity.h"
#include "../Other/Debug.h"
#include <iostream>
#include "../GameEntity/Player.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"
#include "../GameEntity/BackGround.h"
#include "../GameEntity/Teleporter.h"
#include "../GameEntity/Moving_Platform.h"

//TODO in player class ----------
void TestScene::PlayerDeath()
{
	RespawnClock.restart(); // On restart le timer de respawn
	playerIsDead = true;
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
	Ground->SetTag(Tag::OBSTACLE);

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

	//RectangleEntity* pEntity6 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::White);
	//pEntity6->SetPosition(1200, 200);
	//pEntity6->SetRigidBody(true);
	//pEntity6->SetIsKinematic(true);
	//pEntity6->SetGravity(false); 
	//pEntity6->SetTag(Tag::BOUCING_OBSTACLE);

	RectangleEntity* pEntity2 = CreateRectEntity<RectangleEntity>(100, 100, sf::Color::Green);
	pEntity2->SetPosition(100, 0);
	pEntity2->SetRigidBody(true);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);
	pEntity2->SetTag(Tag::METALIC_OBSTACLE);

	Teleporter* Teleporter1 = CreateRectEntity<Teleporter>(100, 100, sf::Color::Magenta); // Ajout du Teleporter et setup
	Teleporter1->SetPosition(1200, -200);
	Teleporter1->SetRigidBody(false);
	Teleporter1->SetIsKinematic(true);
	Teleporter1->SetGravity(false);
	Teleporter1->SetTag(Tag::TELEPORTER);

	Teleporter* Teleporter2 = CreateRectEntity<Teleporter>(100, 100, sf::Color::Magenta); // Ajout du Teleporter et setup
	Teleporter2->SetPosition(1200, 600);
	Teleporter2->SetRigidBody(false);
	Teleporter2->SetIsKinematic(true);
	Teleporter2->SetGravity(false);
	Teleporter2->SetTag(Tag::TELEPORTER);

	Checkpoint* Checkpoint2 = CreateRectEntity<Checkpoint>(100, 100, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint2->SetPosition(300, 670);
	Checkpoint2->SetRigidBody(false);
	Checkpoint2->SetIsKinematic(true);
	Checkpoint2->SetGravity(false);
	Checkpoint2->SetTag(Tag::CHECKPOINT);

	Moving_Platform* pEntity5 = CreateRectEntity<Moving_Platform>(100, 100, sf::Color::White);
	pEntity5->SetPosition(1000, 200);
	pEntity5->SetRigidBody(true);
	pEntity5->SetIsKinematic(true);
	pEntity5->SetGravity(false);
	pEntity5->setMaxTravelDistance(200);
	pEntity5->SetStartPosition(pEntity5->GetPosition(0,0));
	pEntity5->SetLinearDirection(true);
	pEntity5->SetTag(Tag::BOUCING_OBSTACLE); 

	DeadlyObstacle* pEntity10 = CreateRectEntity<DeadlyObstacle>(100, 100, sf::Color::Red); // Ajout du DeadlyObstacle et setup
	pEntity10->SetPosition(1000, 0);
	pEntity10->SetRigidBody(true);
	pEntity10->SetIsKinematic(true);
	pEntity10->SetGravity(false);
	pEntity10->SetTag(Tag::DEADLYOBSTACLE);


}

void TestScene::OnEvent(const sf::Event& event)
{	
}

void TestScene::HandleConsoleEvent()
{
	// Manette
	if (sf::Joystick::isButtonPressed(0, 0)) // Bouton de saut sur la manette (par exemple, A)
	{
		if (mPlayer->mReverse)
		{
			mPlayer->SetState(Player::PlayerStateList::FALL);
			mPlayer->SetPosition(mPlayer->GetPosition(0.f, 0.f).x, mPlayer->GetPosition(0.f, 0.f).y + 5);
			mPlayer->mReverse = false;
			mPlayer->GetPlayerData()->isGrounded = false;
		}
		else if (mPlayer->GetPlayerData()->isGrounded) {
			mPlayer->SetState(Player::PlayerStateList::JUMP);
		}
	}

	if (sf::Joystick::isButtonPressed(0, 1)) { // Bouton de crouch sur la manette (par exemple, B)
		mPlayer->SetState(Player::PlayerStateList::CROUCH);
		mPlayer->GetPlayerData()->isCrouching = true;
		mPlayer->GetPlayerData()->mDirection.x = 0;
	}
	else {
		mPlayer->GetPlayerData()->isCrouching = false;
	}

	// Gestion des axes X pour le mouvement gauche/droite (axe horizontal sur la manette)
	float joystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

	// Si le joystick se penche à gauche (axe < -10)
	if (joystickX < -10) {
		mPlayer->GetPlayerData()->mDirection.x = -1; // Déplacement vers la gauche
		if (!mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::WALK);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
	}
	// Si le joystick se penche à droite (axe > 10)
	else if (joystickX > 10) {
		mPlayer->GetPlayerData()->mDirection.x = 1; // Déplacement vers la droite
		if (!mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::WALK);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
	}
	else {
		mPlayer->GetPlayerData()->mDirection.x = 0; // Aucun mouvement horizontal
		if (mPlayer->GetPlayerData()->isGrounded && !mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::IDLE); // Si au sol, état "IDLE"
		}
		else if (!mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::FALL); // Sinon, état "FALL"
		}
	}
}

void TestScene::HandleKeyboardEvent()
{
	//Clavier
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		if (mPlayer->mReverse) 
		{
			mPlayer->SetState(Player::PlayerStateList::FALL);
			mPlayer->SetPosition(mPlayer->GetPosition(0.f, 0.f).x, mPlayer->GetPosition(0.f, 0.f).y + 5);
			mPlayer->mReverse = false;
			mPlayer->GetPlayerData()->isGrounded = false;
		}
		else if (mPlayer->GetPlayerData()->isGrounded) {
			mPlayer->SetState(Player::PlayerStateList::JUMP);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		mPlayer->SetState(Player::PlayerStateList::CROUCH);
		mPlayer->GetPlayerData()->isCrouching = true;
		mPlayer->GetPlayerData()->mDirection.x = 0;
	}
	else {
		mPlayer->GetPlayerData()->isCrouching = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mPlayer->GetPlayerData()->mDirection.x = 0;
		if (mPlayer->GetPlayerData()->isGrounded) {
			mPlayer->SetState(Player::PlayerStateList::IDLE);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::FALL);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::WALK);
		}
		mPlayer->GetPlayerData()->mDirection.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::WALK);
		}
		mPlayer->GetPlayerData()->mDirection.x = 1;
	}
	else if (!mPlayer->GetPlayerData()->isCrouching) {
		mPlayer->GetPlayerData()->mDirection.x = 0;
		if (mPlayer->GetPlayerData()->isGrounded) {
			mPlayer->SetState(Player::PlayerStateList::IDLE);
		}
		else {
			mPlayer->SetState(Player::PlayerStateList::FALL);
		}
	}
}

void TestScene::OnUpdate()
{
	HandleConsoleEvent();
	//HandleKeyboardEvent();

	int i = 0;
	PlayerRespawn();

	mView->setCenter(mPlayer->GetPosition(0.f, 0.f).x + 200, mPlayer->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame 
	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		//TODO : NE PAS REFAIRE DES TESTS DE COLLISION QUAND ON PEUT JUSTE ULTILISER LE "OnCollision" DES ENTITIES !!!!!!
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
	}

	std::string entitynb = std::to_string(i) + "nb entity";
	Debug::DrawText(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 40, entitynb, sf::Color::White);
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);

	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
