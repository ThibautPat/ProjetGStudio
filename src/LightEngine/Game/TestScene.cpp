#include "TestScene.h"

#include "../Core/Entity.h"
#include <iostream>
#include "../Core/Debug.h"
#include "../Game/Player.h"
void TestScene::Pause()
{
	//#TODO
	Debug::DrawText(mView.getCenter().x - 40, mView.getCenter().y - 10, "PAUSE", sf::Color::White);
	if (pauseMenu == 0)
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 50, "Resume", sf::Color::Red);
	}
	else
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 50, "Resume", sf::Color::White);
	}
	if (pauseMenu == 1)
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 80, "Settings", sf::Color::Red);
	}
	else
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 80, "Settings", sf::Color::White);
	}
	if (pauseMenu == 4)
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 170, "Quit to desktop", sf::Color::Red);
	}
	else
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 170, "Quit to desktop", sf::Color::White);
	}
	if (pauseMenu == 2)
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 110, "Return to Checkpoint", sf::Color::Red);
	}
	else
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 110, "Return to Checkpoint", sf::Color::White);
	}
	if (pauseMenu == 3)
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 140, "Quit to main menu", sf::Color::Red);
	}
	else
	{
		Debug::DrawText(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 140, "Quit to main menu", sf::Color::White);
	}

}
void TestScene::OnInitialize()
{
	mView = sf::View(sf::FloatRect(0, 0, 1280, 720));
	
	escapeClockGap.restart();
	menuClock.restart();

	Player* pEntity = CreateEntity<Player>(100, sf::Color::Red);
	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetPosition(600, 100);

	Entity* pEntity2 = CreateEntity<Entity>(100, sf::Color::Green);
	pEntity2->SetGravity(true);
	pEntity2->SetRigidBody(true);
	pEntity2->SetPosition(300, 100);

	Entity* pEntity3 = CreateEntity<Entity>(100, sf::Color::Green);
	pEntity3->SetGravity(true);
	pEntity3->SetRigidBody(true);
	pEntity3->SetPosition(0, 100);
	mGm = GameManager::Get();
}

void TestScene::OnEvent(const sf::Event& event)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7))
	{
		Debug::Pause(this);
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10 && freeze && menuClock.getElapsedTime().asSeconds() > 0.2f)
	{
		menuClock.restart();
		pauseMenu--;
		if (pauseMenu < 0)
		{
			pauseMenu = 4;
		}
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10 && freeze && menuClock.getElapsedTime().asSeconds() > 0.2f)
	{
		menuClock.restart();
		pauseMenu++;
		if (pauseMenu > 4)
		{
			pauseMenu = 0;
		}
	}
}

void TestScene::OnUpdate()
{

	std::list<Entity*> entities = mGm->GetEntities<Entity>();


	for (Entity* entity : entities)
	{
		if (dynamic_cast<Player*>(entity))
		{
			mView.setCenter(entity->GetPosition().x + 200, entity->GetPosition().y - 115);
			dynamic_cast<Player*>(entity)->Jump(GetDeltaTime());
			
		}
	}

	for (Entity* entity : entities)
	{
		sf::Vector2f co = entity->GetPosition();
		if (co.y + entity->GetRadius() > 720)
		{
			entity->mBoolGravity = 0;
			entity->SetPosition(co.x, 720 - entity->GetRadius() - 1);
			(entity)->secondjump = 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			entity->mBoolGravity = 1;
			entity->mGravitySpeed = -500;
		}
		int lisibleSpeed = (int)entity->mSpeed;
		lisibleSpeed = lisibleSpeed / 100;
		std::string gravsp = std::to_string((int)entity->mGravitySpeed) + " grav speed";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y, gravsp, sf::Color::White);
		std::string velo = std::to_string(lisibleSpeed) + " velo speed";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 20, velo, sf::Color::White);
		std::string grav = std::to_string(entity->mBoolGravity) + " grav";
		Debug::DrawText(co.x - entity->GetRadius() / 2, co.y + 40, grav, sf::Color::White);
	}
	mGm->GetWindow()->setView(mView);
	Debug::ShowFPS(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 10);
}
