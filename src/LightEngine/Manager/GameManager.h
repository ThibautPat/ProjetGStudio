#pragma once
#include <list>
#include <SFML/Graphics.hpp>

#include "SceneManager.h"

#define FIXED_DT 0.0167f

class Entity;
class Scene;
class Debug;
class InputManager;
class TextureManager;
class SceneManager;

class GameManager
{

protected:
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;
	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

	float mAccumulatedDt = 0.f;

	TextureManager* mAs;

	SceneManager* mScM;
	bool mIsSceneChanged = false;

	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	void FixedUpdate();

	void PhysiqueUpdate();

public:

	~GameManager();

	void DrawRender(Entity* entity);

	static GameManager* Get();
	TextureManager* GetTextureManager() { return mAs; }
	SceneManager* GetSceneManager() { return mScM; }

	bool IsSceneChanged() { return mIsSceneChanged; }
	void SetIsSceneChanged(bool isccenechanged) { mIsSceneChanged = isccenechanged; }

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);
	sf::RenderWindow* GetWindow() const { return mpWindow; }

	float GetDeltaTime() const { return mDeltaTime; }
	sf::Font& GetFont() { return mFont; };
	
	template<typename T>
	std::list<T*>& GetEntities();

	template<typename T>
	T* GetEntity(int tag);

	friend Debug;
	friend Scene;
	friend SceneManager;
};

#include "GameManager.inl"