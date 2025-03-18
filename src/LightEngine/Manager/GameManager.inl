#pragma once

#include "GameManager.h"
#include "../GameScene/Scene.h"
#include "../Entity/Entity.h"

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
