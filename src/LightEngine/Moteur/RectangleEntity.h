#pragma once
#include "../Entity.h"
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
	AABBCollider* mCollider;

	sf::RectangleShape mShape;

public:

	// Hérité via Entity
	Collider* GetCollider() override;
	sf::Shape* GetShape() override;
	bool IsColliding(Entity* other) override;
	bool IsInside(float x, float y) override;
	void Initialize(float radius, const sf::Color& color) override {};
	void Initialize(float height, float weight, const sf::Color& color) override;
	void Repulse(Entity* other) override;
	void Update() override;
};

