#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#define ENTITY_NB 0

class Entity;

class TestScene : public Scene
{
protected:

	GameManager* mGm;
	sf::View mView;
public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

