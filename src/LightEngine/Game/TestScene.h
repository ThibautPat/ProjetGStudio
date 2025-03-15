#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Entity;

class TestScene : public Scene
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
	void PlayerDeath();
	enum Tag
	{
		PLAYER,
		CHECKPOINT,
		DEADLYOBSTACLE,
		METALIC_OBSTACLE,
		OBSTACLE,
		END_LEVEL,

		COUNT
	};
	
	void PlayerRespawn();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

