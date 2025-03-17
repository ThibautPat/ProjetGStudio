#include "Entity.h"

#include "../Manager/GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}

template<typename T>
T* Entity::CreateCircleEntity(float radius, const sf::Color& color)
{
	return GetScene()->CreateCircleEntity<T>(radius, color);
}

template<typename T>
T* Entity::CreateRectEntity(float height, float weight, const sf::Color& color)
{
	return GetScene()->CreateRectEntity<T>(height, weight, color);
}