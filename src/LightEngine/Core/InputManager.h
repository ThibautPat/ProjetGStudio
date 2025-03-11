#pragma once

#include "Scene.h"

class InputManager
{
protected:
	sf::Vector2f mDir;

public:
	enum class Key
	{
		Nothing,
		Q,
		D,
		Z,
		Espace,
		MAJ,
	};
protected :

	Key mKeyPressed;

public:

	InputManager();

	void InputUpdate(const sf::Event& event);

	Key& GetInput() { return mKeyPressed; }
	//sf::Vector2f GetInput() { return mDir; }


};

