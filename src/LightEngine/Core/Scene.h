#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "CameraMan.h"

class Scene
{
protected:
	GameManager* mpGameManager;

	CameraMan* mCam = new CameraMan();
	sf::View* mView;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;
	//virtual void Pause() = 0;

public:
	
	template<typename T>
	T* CreateCircleEntity(float radius, const sf::Color& color);

	template<typename T>
	T* CreateRectEntity(float height, float Width, const sf::Color& color);

	float GetDeltaTime() const;
	sf::View* GetView() { return mView; }
	CameraMan* GetCamera() { return mCam; }

	bool freeze = false; 
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"