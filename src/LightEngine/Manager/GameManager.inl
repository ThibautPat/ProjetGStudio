#pragma once

#include "GameManager.h"
#include "../GameScene/Scene.h"
#include "../Entity/Entity.h"

/*
template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	if (mpScene != nullptr)
		mpScene = nullptr;
	_ASSERT(mpScene == nullptr);

	T* newScene = new T();
	mpScene = newScene;

	mpScene->SetGameManager(this);
	mpScene->OnInitialize();

	Run();
}
*/

template<typename T>
inline std::list<T*>& GameManager::GetEntities()
{
	return mEntities;
}

template<typename T>
inline T* GameManager::GetEntity(int tag)
{
	for (Entity* entity : mEntities)
	{
		if (entity->IsTag(tag))
			return (T*)entity;
	}

	return nullptr;
}
