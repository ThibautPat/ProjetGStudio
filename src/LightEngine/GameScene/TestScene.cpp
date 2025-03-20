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
#include "../Renderer/TextureRender.h"

void TestScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, -340, GetWindowWidth() + 56.25f, GetWindowHeight() + 100)); // Ajout de la cam�ra
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
	pEntity9->SetPosition(mView->getCenter().x - 30, 205);
	pEntity9->SetRigidBody(false);
	pEntity9->SetIsKinematic(true);
	pEntity9->SetGravity(false);
	pEntity9->SetBackGroundTexture("..//..//..//res//Assets//Background//upsky_background_mercure.png");
	pEntity9->SetTag(Tag::BACK_GROUND2);

	Checkpoint* Checkpoint1 = CreateRectEntity<Checkpoint>(256, 128, sf::Color::Yellow); // Ajout du Checkpoint et setup
	Checkpoint1->SetPosition(-100, 620);

	DeadlyObstacle* DeadlyObstacle1 = CreateRectEntity<DeadlyObstacle>(100, 100, sf::Color::Red); // Ajout du DeadlyObstacle et setup
	DeadlyObstacle1->SetPosition(900, 670);

	mPlayer = CreateRectEntity<Player>(256, 128, sf::Color::Transparent); // Ajout du Player et setup
	mPlayer->SetGravity(true);
	mPlayer->SetRigidBody(true);
	mPlayer->SetIsKinematic(false);
	mPlayer->SetPosition(0, 0);

	RectangleEntity* Ground = CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3250);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);
	Ground->SetTag(Tag::PLATFORM);
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
		else if (!mPlayer->GetPlayerData()->isCrouching && mPlayer->GetGravitySpeed() > 0) {
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
		else if (mPlayer->GetGravitySpeed() > 0) {
			mPlayer->SetState(Player::PlayerStateList::FALL);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {	
		if (mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
		mPlayer->GetPlayerData()->mDirection.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (mPlayer->GetPlayerData()->isCrouching) {
			mPlayer->SetState(Player::PlayerStateList::CROUCH);
		}
		mPlayer->GetPlayerData()->mDirection.x = 1;
	}
	else if (!mPlayer->GetPlayerData()->isCrouching) {
		mPlayer->GetPlayerData()->mDirection.x = 0;
		if (mPlayer->GetPlayerData()->isGrounded) {
			mPlayer->SetState(Player::PlayerStateList::IDLE);
		}
		else if (mPlayer->GetGravitySpeed() > 0) {
			mPlayer->SetState(Player::PlayerStateList::FALL);
		}
	}
}

void TestScene::OnUpdate()
{
	//HandleConsoleEvent();
	HandleKeyboardEvent();

	mView->setCenter(mPlayer->GetPosition(0.f, 0.f).x + 200, mPlayer->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame 
	for (Entity* entity : m_InstanceGameManager->GetEntities<Entity>()) // Parcours des entit�s du gameManager
	{
		sf::Vector2f cooEntity = entity->GetPosition(0.f, 0.f);

		std::string textCox = std::to_string((int)cooEntity.x) + " x ";
		std::string textCoy = std::to_string((int)cooEntity.y) + " y";
		std::string textgrav = std::to_string((int)entity->GetGravitySpeed()) + " grav";
		Debug::DrawText(cooEntity.x, cooEntity.y, textCox, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 20, textCoy, sf::Color::White);
		Debug::DrawText(cooEntity.x, cooEntity.y + 40, textgrav, sf::Color::White);
		Debug::DrawCircle(cooEntity.x, cooEntity.y, 5, sf::Color::White);
	}
	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);

	m_InstanceGameManager->GetWindow()->setView(*mView); // Voir si possibilit� de ne pas call la view chaque frame
}
