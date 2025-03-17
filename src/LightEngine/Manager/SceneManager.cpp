#include "SceneManager.h"

SceneManager::SceneManager()
{
	mCurrentScene = nullptr;
}

void SceneManager::SelectScene(const char* name)
{
	mCurrentScene = mListScene.at(name);
	GameManager::Get()->SetIsSceneChanged(true);
}

void SceneManager::LaunchScene()
{
	mCurrentScene->SetGameManager(GameManager::Get());
	mCurrentScene->OnInitialize();

	GameManager::Get()->SetIsSceneChanged(false);
	GameManager::Get()->Run();
}
