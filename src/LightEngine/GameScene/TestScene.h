#pragma once

#include "../GameScene/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Entity;
class Player;

class TestScene : public Scene
{
protected:

	GameManager* m_InstanceGameManager;
	sf::View* mView;
	sf::Clock menuClock;
	sf::Clock escapeClockGap;
	sf::Clock RespawnClock;
	sf::Clock TeleportClock;
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
		PLATFORM,

		COUNT
	};
	
	void PlayerRespawn();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void HandleConsoleEvent();
	void HandleKeyboardEvent();
	void OnUpdate() override;
};