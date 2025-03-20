#pragma once

class GameManager;
class SceneManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/View.hpp>

class Player;

class Scene
{
private:
	GameManager* mpGameManager;
	
private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Player* mPlayer;
	bool mIsEnd = false; 
	Scene() = default;

	sf::View* mView;
	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:
	void SetIsEnd(bool isEnd) { mIsEnd = isEnd; }
	virtual Player* GetPlayer() { return mPlayer; }
	virtual void SetPlayer(Player* _player) { mPlayer = _player; }

	template<typename T>
	T* CreateCircleEntity(float radius, const sf::Color& color);

	template<typename T>
	T* CreateRectEntity(float height, float Width, const sf::Color& color);

	float GetDeltaTime() const;

	sf::View* GetView() { return mView; }
	bool freeze = false; 
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
	friend SceneManager;
};

#include "Scene.inl"