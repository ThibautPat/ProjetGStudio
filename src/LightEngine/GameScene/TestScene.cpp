#include <iostream>

#include "TestScene.h"
#include "../Entity/Entity.h"
#include "../Other/Debug.h"
#include "../GameEntity/Player.h"
#include "../GameEntity/BackGround.h"
#include "../GameScene/Level.h"

void TestScene::OnInitialize()
{

	m_InstanceGameManager = GameManager::Get();

	

	mView = new sf::View(sf::FloatRect(0, -340, GetWindowWidth() + 56.25f, GetWindowHeight() + 100)); // Ajout de la cam�ra
	

	BackGround* pEntity1 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity1->SetPosition(0, 205);
	pEntity1->SetRigidBody(false);
	pEntity1->SetIsKinematic(true);
	pEntity1->SetGravity(false);
	pEntity1->SetBackGroundTexture("..//..//..//res//Assets//Background//sky_mercure.png");
	pEntity1->SetTag(Tag::BACK_GROUND1);

	BackGround* pEntity2 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity2->SetPosition(mView->getCenter().x, mView->getCenter().y);
	pEntity2->SetRigidBody(false);
	pEntity2->SetIsKinematic(true);
	pEntity2->SetGravity(false);
	pEntity2->SetBackGroundTexture("..//..//..//res//Assets//Background//upsky_background_mercure.png");
	pEntity2->SetTag(Tag::BACK_GROUND2BIS);

	BackGround* pEntity3 = CreateRectEntity<BackGround>(1090, 3350, sf::Color::White);
	pEntity3->SetPosition(mView->getCenter().x - 30, mView->getCenter().y);
	pEntity3->SetRigidBody(false);
	pEntity3->SetIsKinematic(true);
	pEntity3->SetGravity(false);
	pEntity3->SetBackGroundTexture("..//..//..//res//Assets//Background//upsky_background_mercure.png");
	pEntity3->SetTag(Tag::BACK_GROUND2);

	mLevel = new Level();
	mLevel->ChooseJson("../../../res/map.json");
	mLevel->LoadLevel();
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
		else if (!mPlayer->GetPlayerData()->isGrounded) {
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

	mPlayer->PlayerRespawn();

	mView->setCenter(mPlayer->GetPosition(0.f, 0.f).x + 200, mPlayer->GetPosition(0.f, 0.f).y - 115); //Repositionnement de la cam�ra sur le joueur chaque frame 

	Debug::ShowFPS(mView->getCenter().x - mView->getSize().x / 2 + 10, mView->getCenter().y - mView->getSize().y / 2 + 10);

	m_InstanceGameManager->GetWindow()->setView(*mView); // Mise a jour de la view
}
