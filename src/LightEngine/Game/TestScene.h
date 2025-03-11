#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#define ENTITY_NB 0

class Entity;

class TestScene : public Scene
{
protected:

	GameManager* mGm;
	sf::View mView;
	sf::Clock escapeClockGap;
	int pauseMenu = 0;
	sf::Clock menuClock;
public:
	void Pause() override;
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

