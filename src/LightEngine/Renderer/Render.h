#pragma once

#include "SFML/Graphics.hpp"

class Entity;

class Render
{
public:
	virtual void Draw(Entity* entity, sf::RenderWindow* window) = 0;
};

