#include "SceneManager.h"

/// <summary>
/// Ajoute une nouvelle Scene a la map de SceneManager (la Scene n'est pas initialise : pScene = nullptr)
/// </summary>
/// <typeparam name="T">Class de la Scene</typeparam>
/// <param name="name">Nom de la Scene stockee dans la map</param>
template<typename T>
inline void SceneManager::AddScene(const char* name)
{
	mListScene.insert({ name , new T() });
}
