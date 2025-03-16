#pragma once

#include "Scene.h"

class SceneManager 
{
protected:

	std::map<std::string, Scene*> mListScene;
	Scene* mCurrentScene;
public:
	SceneManager();

	Scene* GetScene() { return mCurrentScene; }

	template<typename T>
	void AddScene(const char* name);

	template<typename T>
	void LaunchScene();

	template<typename T>
	void SelectScene(const char* name);

	friend Scene;
	friend GameManager;
};

#include "SceneManager.inl"
