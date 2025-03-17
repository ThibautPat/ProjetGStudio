#pragma once

#include "../../Core/Other/Scene.h"

class SceneManager 
{
protected:

	std::map<std::string, Scene*> mListScene;
	Scene* mCurrentScene;
	const char* mNextScene = nullptr;

public:

	SceneManager();

	Scene* GetScene() { return mCurrentScene; }

	template<typename T>
	void AddScene(const char* name);

	/// <summary>
	/// Selectionne une Scene parmis les Scenes de la map (met son pointeur sur mCurrentScene)
	/// </summary>
	/// <param name="name">Nom de la Scene dans map a selectionner</param>
	void SelectScene(const char* name);

	/// <summary>
	/// Initialise la Scene selectionnee (mCurrentScene) et la lance dans le GameManager
	/// </summary>
	void LaunchScene();

	friend Scene;
	friend GameManager;
};

#include "SceneManager.inl"
