#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Entity;

class TestScene2 : public Scene
{
protected:

	GameManager* m_InstanceGameManager;
	sf::View* mView;
	sf::Clock menuClock;
	sf::Clock escapeClockGap;
	sf::Clock RespawnClock;
	sf::Vector2f mLastCheckPoint;
	bool playerIsDead = false;

public:

	enum Tag
	{
		PLAYER,
		CHECKPOINT,
		DEADLYOBSTACLE,
		METALIC_OBSTACLE,
		OBSTACLE,
		END_LEVEL,
		BLUE_KEY,
		RED_KEY,
		GREEN_KEY,
		BLUE_DOOR,
		RED_DOOR,
		GREEN_DOOR,

		COUNT
	};

	void PlayerDeath();
	void PlayerRespawn();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

