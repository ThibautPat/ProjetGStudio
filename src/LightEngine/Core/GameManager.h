#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#define FIXED_DT 0.0167f

class Entity;
class Scene;
class Debug;
class InputManager;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;
	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

	float mAccumulatedDt = 0.f;

	InputManager* mInp;

private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	

	void FixedUpdate();

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);
	sf::RenderWindow* GetWindow() const { return mpWindow; }
	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	InputManager* GetInputManager() { return mInp; }
	sf::Font& GetFont() { return mFont; };
	
	template<typename T>
	std::list<T*>& GetEntities();

	template<typename T>
	T* GetEntity(int tag);

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"