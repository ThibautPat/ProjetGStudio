#pragma once

#include "Scene.h"

class InputManager
{
protected:
	sf::Vector2f mDir;

public:

	InputManager();

	void InputUpdate(const sf::Event& event);

	sf::Vector2f GetInput() { return mDir; }
};

