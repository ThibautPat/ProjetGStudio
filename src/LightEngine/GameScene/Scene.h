#pragma once

class GameManager;
class SceneManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

	float mStartTimer = 1.f;
	float mStartTimerProgress = 0.f;

public:

	enum Tag
	{
		PLAYER,
		CHECKPOINT,
		DEADLYOBSTACLE,
		METALIC_OBSTACLE,
		OBSTACLE,
		END_LEVEL,

		COUNT
	};
	
	/// <summary>
	/// Empeche de vérifier d'es'utiliser positions incorrectes (car toutes def à 0,0 au lancement du programme)
	/// </summary>
	/// <returns></returns>
	bool UpdateStartTimer();

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