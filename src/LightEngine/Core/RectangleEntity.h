#pragma once
#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
	class Shape;
	class Color;
}

class Scene;
class AABBCollider;
class Collider;

class RectangleEntity : public Entity
{
protected: 

	AABBCollider* mCollider;
	sf::RectangleShape mShape;

public:

	// Hérité via Entity
	Collider* GetCollider() override;
	sf::Shape* GetShape() override;
	bool IsColliding(Entity* other) override;
	bool IsInside(float x, float y) override;
	void Initialize(float radius, const sf::Color& color) override {};
	void Initialize(float height, float Width, const sf::Color& color) override;
	void Repulse(Entity* other) override;
	/// <summary>
	/// Update du collider puis de l'entity
	/// </summary>
	void Update() override;

	virtual void OnUpdate();
	virtual void OnCollision(Entity* collidedWith);
	virtual void OnInitialize();
	virtual void OnDestroy();
};

