#pragma once
#include "Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class Shape;
	class Color;
}

class Scene;
class CircleCollider;
class Collider;

class CircleEntity : public Entity
{
	CircleCollider* mCollider;

	sf::CircleShape mShape;

public:
	float GetRadius() const { return mShape.getRadius(); }

	// Hérité via Entity
	Collider* GetCollider() override;
	sf::Shape* GetShape() override;
	void Initialize(float radius, const sf::Color& color) override;
	void Initialize(float height, float Width, const sf::Color& color) override {};
	void Repulse(Entity* other) override;
	bool IsColliding(Entity* other);
	bool IsInside(float x, float y);
	void Update() override;

	virtual void OnUpdate();
	virtual void OnCollision(Entity* collidedWith);
	virtual void OnInitialize();
	virtual void OnDestroy();
};

