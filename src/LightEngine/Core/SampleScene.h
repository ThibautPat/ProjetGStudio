#pragma once

#include "Scene.h"
#include "Player.h"
class DummyEntity;

class SampleScene : public Scene
{
	Player* mPlayer;

public:
	float playerJumpTime;
	float playerRunTime;
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


