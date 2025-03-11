#pragma once
#include "../Core/Scene.h"
class PauseScene : public Scene
{
public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

