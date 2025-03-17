#include "InputManager.h"

InputManager::InputManager()
{
	mDir = sf::Vector2f(0, 0);
}

void InputManager::InputUpdate(const sf::Event& event)
{
	//Reset moves
	mDir = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		mDir.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		mDir.x = 1;
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10)
	//{
	//	mDir.y = -1;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10)
	//{
	//	mDir.y = 1;
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
	{
		mDir.y = -1;
	}
}
