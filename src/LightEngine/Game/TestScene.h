#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Entity;
class Player;

class TestScene : public Scene
{
protected:

	Player* mPlayer;

	GameManager* m_InstanceGameManager;
	sf::View* mView;
	sf::Clock menuClock;
	sf::Clock escapeClockGap;
	sf::Clock RespawnClock;
	sf::Vector2f mLastCheckPoint;
	bool playerIsDead = false;

public:
	enum Tags {
		PLAYER,
		OBSTACLE,
		PLATFORM,
		CHECKPOINT,
		DEADLY_OBSTACLE,

		COUNT
	};

	Player* GetPlayer() { return mPlayer; };

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