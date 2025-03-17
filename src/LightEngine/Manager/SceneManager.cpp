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
	//static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	//_ASSERT(mCurrentScene == nullptr);

	//T* newScene = new T();
	//mCurrentScene = newScene;

	mCurrentScene->SetGameManager(GameManager::Get());
	mCurrentScene->OnInitialize();

	//TODO mettre ailleur avec une scene par defaut dans le constructeur ?

	GameManager::Get()->SetIsSceneChanged(false);
	GameManager::Get()->Run();
	//Plus de code execute ici
}
