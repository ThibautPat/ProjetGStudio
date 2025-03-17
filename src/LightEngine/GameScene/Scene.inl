#pragma once

#include "Scene.h"
#include "../Manager/GameManager.h"
#include "../Entity/Entity.h"

template<typename T>
T* Scene::CreateCircleEntity(float radius, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(radius, color);
	
	GameManager::Get()->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
T* Scene::CreateRectEntity(float height, float weight, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(height, weight, color);

	GameManager::Get()->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}