#pragma once

#include "../Core/Scene.h"
#include "../Core/AudioManager.h"

#define ENTITY_NB 0

class Entity;

class TestScene : public Scene
{
protected:
	AudioManager* AudioM;
	GameManager* mGm;

	std::vector<std::string*> m_soundList;
	std::vector<std::string*> m_MusicList;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

