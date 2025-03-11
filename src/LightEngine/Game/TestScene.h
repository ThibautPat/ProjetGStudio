#pragma once

#include "../Core/Scene.h"

#define ENTITY_NB 0

class Entity;

class TestScene : public Scene
{
protected:

	GameManager* mGm;
	InputManager* mInp;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

