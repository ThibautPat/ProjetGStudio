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
	Jump();
	sf::Vector2f move = Movement();
}

sf::Vector2f SampleScene::Movement()
{
	float x = 0;
	float y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		x = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		x = 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10)
	{
		y = -100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10)
	{
		y = 100;
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
	
	return sf::Vector2f(x , y);
}

void SampleScene::Jump()
{
	dt = jumpclock.getElapsedTime().asSeconds();
	jumpclock.restart();
	time += dt;
	if (time > 1) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
		{
			std::cout << "Jump" << std::endl;
			time = 0;

		}
	}
}
