#pragma once
#include "Scene.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include "../Other/Debug.h"

class BeginScene :	public Scene
{
	GameManager* m_InstanceGameManager;
	sf::View* mView;
	sf::Clock menuClock;
	std::string text = "Press to Start";
	bool isPressed = false;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void HandleConsoleEvent();
	void HandleKeyboardEvent();
	void OnUpdate() override;
	
};