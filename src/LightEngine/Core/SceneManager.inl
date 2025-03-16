#include "SceneManager.h"

template<typename T>
inline void SceneManager::AddScene(const char* name)
{
	mListScene.insert({ name , new T() });
}

template<typename T>
inline void SceneManager::LaunchScene()
{
	//static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	//_ASSERT(mCurrentScene == nullptr);

	//T* newScene = new T();
	//mCurrentScene = newScene;

	mCurrentScene = (T*)mCurrentScene;

	mCurrentScene->SetGameManager(GameManager::Get());
	mCurrentScene->OnInitialize();

	//TODO mettre ailleur avec une scene par defaut dans le constructeur ?
	GameManager::Get()->Run();
}
template<typename T>
inline void SceneManager::SelectScene(const char* name)
{
	mCurrentScene = (T*)mListScene.at(name);
}
