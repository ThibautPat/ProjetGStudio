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
	Player* pEntity = CreateRectEntity<Player>(100, 100, sf::Color::Blue);
	escapeClockGap.restart();
	menuClock.restart();

	mGm = GameManager::Get();

	pEntity->SetGravity(true);
	pEntity->SetRigidBody(true);
	pEntity->SetIsKinematic(true);
	pEntity->SetPosition(100, 100);

	for (int i = 0; i <= ENTITY_NB; i++) 
	{
		RectangleEntity* pEntity = CreateRectEntity<RectangleEntity>(250, 600, sf::Color::Red);
		pEntity->SetPosition(i*400 + 600, 0);
		pEntity->SetRigidBody(true);
		pEntity->SetIsKinematic(false);
		pEntity->SetGravity(true);
	}
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
			mView.setCenter(entity->GetPosition(0.f, 0.f).x + 200, entity->GetPosition(0.f, 0.f).y - 115);
			dynamic_cast<Player*>(entity)->Jump(GetDeltaTime());
		}

		sf::Vector2f co = entity->GetPosition(0.f, 0.f);

		std::string textCo = std::to_string(co.x) + " : x		" + std::to_string(co.y) + " : y";
		Debug::DrawText(co.x, co.y, textCo, sf::Color::White);

		Debug::DrawCircle(co.x, co.y, 5, sf::Color::White);

		if (co.y + entity->GetShape()->getGlobalBounds().height * 0.5f > 720)
		{
			entity->SetGravity(false);
			entity->SetPosition(co.x, 720 - entity->GetShape()->getGlobalBounds().height * 0.5f, 0.f, 0.f);
		}
		else if (co.y + entity->GetShape()->getGlobalBounds().height * 0.5f < 720)
		{
			entity->SetGravity(true);
		}
			
		//int lisibleSpeed = (int)entity->GetSpeed();
		//lisibleSpeed = lisibleSpeed / 100;
		//std::string gravsp = std::to_string((int)entity->GetGravitySpeed()) + " grav speed";
		//Debug::DrawText(co.x, co.y , gravsp, sf::Color::White);
		//std::string velo = std::to_string(lisibleSpeed) + " velo speed";
		//Debug::DrawText(co.x, co.y + 20, velo, sf::Color::White);
		//std::string gravi = std::to_string(entity->IsOnGround()) + " on ground";
		//Debug::DrawText(co.x, co.y + 40, gravi, sf::Color::White);
	}
	mGm->GetWindow()->setView(mView);
	Debug::ShowFPS(mView.getCenter().x - GetWindowWidth() / 2 + 10, mView.getCenter().y - GetWindowHeight() / 2 + 10);
}
