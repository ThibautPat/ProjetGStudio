#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Player;

class Entity;

class TestScene2 : public Scene
{
	Player* mPlayer;

	enum Tags
	{
		PLAYER,
		CHECKPOINT,
		DEADLY_OBSTACLE,
		METALIC_OBSTACLE,
		OBSTACLE,
		END_LEVEL,
		PLATFORM,

		COUNT
	};

protected:

	GameManager* m_InstanceGameManager;
	sf::View* mView;
	sf::Clock menuClock;
	sf::Clock escapeClockGap;
	sf::Clock RespawnClock;
	sf::Vector2f mLastCheckPoint;
	bool playerIsDead = false;

public:

	Player* GetPlayer() { return mPlayer; }

	void PlayerDeath();
	void PlayerRespawn();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

