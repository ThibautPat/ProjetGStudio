#pragma once

class GameManager;
class SceneManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Player;

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Player* mPlayer;

	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:
	virtual Player* GetPlayer() { return mPlayer; }
	
	template<typename T>
	T* CreateCircleEntity(float radius, const sf::Color& color);

	template<typename T>
	T* CreateRectEntity(float height, float Width, const sf::Color& color);

	float GetDeltaTime() const;

	bool freeze = false; 
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
	friend SceneManager;
};

#include "Scene.inl"