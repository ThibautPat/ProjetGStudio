#pragma once

#include "Scene.h"

class SceneManager 
{
protected:

	std::vector<Scene*> mTabScene;
	Scene* mCurrentScene;
public:
	SceneManager() {}

	Scene* GetScene() { return mCurrentScene; }

	template<typename T>
	void AddScene();

	template<typename T>
	void LaunchScene();


	friend Scene;
	friend GameManager;
};

#include "SceneManager.inl"
