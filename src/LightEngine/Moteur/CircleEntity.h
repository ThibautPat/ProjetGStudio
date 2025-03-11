#pragma once
#include "../Entity.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class Shape;
	class Color;
}

class Scene;
class CircleCollider;

class CircleEntity : public Entity
{
public:
	float GetRadius() const { return mShape.getRadius(); }
};

