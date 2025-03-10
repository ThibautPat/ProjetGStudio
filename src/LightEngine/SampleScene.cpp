#include "SampleScene.h"

#include "DummyEntity.h"

#include <iostream>
#include "Debug.h"

void SampleScene::OnInitialize()
{

}

void SampleScene::OnEvent(const sf::Event& event)
{

}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y){}

void SampleScene::OnUpdate()
{
	float x = 0;
	float y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		x = -100; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		x = 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		y = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		y = 100;
	}

	if (sf::Joystick::isConnected(0))
	{
		x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	}

	if (x > -10 && x < 10)
		x = 0;
	if (y > -10 && y < 10)
		y = 0;
	if (x < 0)
		x = -1;
	if (x > 0)
		x = 1;
	if (y < 0)
		y = -1;
	if (y > 0)
		y = 1;
	std::cout << x << "," << y << std::endl;
}