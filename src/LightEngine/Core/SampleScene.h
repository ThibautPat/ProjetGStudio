#pragma once

#include "../Core/Scene.h"
#include "../Game/Player.h"
class DummyEntity;

class SampleScene : public Scene
{
	Player* mPlayer;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


