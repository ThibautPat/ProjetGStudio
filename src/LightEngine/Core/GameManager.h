#pragma once

#include <list>


#include <SFML/Graphics.hpp>

#define FIXED_DT 0.0167f

class Entity;
class Scene;
class Debug;
class InputManager;
class TextureManager;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
protected:
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

	TextureManager* mAs;

	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	

	void FixedUpdate();

public:
	~GameManager();

	void DrawTextureRender(Entity* entity);

	static GameManager* Get();
	TextureManager* GetAssetsManager() { return mAs; }

	void UpdateCollision(Entity* mEntities);

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);
	sf::RenderWindow* GetWindow() const { return mpWindow; }
	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };
	
	template<typename T>
	std::list<T*>& GetEntities();

	template<typename T>
	T* GetEntity(int tag);

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"