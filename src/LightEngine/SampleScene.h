#pragma once

#include "Scene.h"
#include "SFML/System/Clock.hpp"
class DummyEntity;

class SampleScene : public Scene
{

	

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	float dt;
	float time;
	sf::Clock jumpclock;
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	sf::Vector2f Movement();
	void Jump();
};


