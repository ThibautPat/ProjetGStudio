#pragma once

#include "../Core/Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#define ENTITY_NB 0

class Entity;
class Level;

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
	bool GreenKey = false;
	bool RedKey = false;
	bool BlueKey = false;

	Level* mLevel;

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
		BACK_GROUND1,
		BACK_GROUND2,
		BACK_GROUND1BIS,
		BACK_GROUND2BIS,
		BOUCING_OBSTACLE,
		TELEPORTER,
		TELEPORTER_2,

		COUNT
	};
	
	void PlayerRespawn();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

