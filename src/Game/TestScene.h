#pragma once

#include "../LightEngine/Scene.h"

#define ENTITY_NB 2

class Entity;

class TestScene : public Scene
{
protected:

	GameManager* mGm;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

