#pragma once

#include "Entity.h"
#include <SFML/Graphics/CircleShape.hpp>

class Scene;
class CircleCollider;
class Collider;

class CircleEntity : public Entity
{
protected:
    CircleCollider* mCollider = nullptr;
    sf::CircleShape mShape;

public:
    // Getter
    float GetRadius() const { return mShape.getRadius(); }

    // H�ritage Entity
    Collider* GetCollider() override;
    sf::Shape* GetShape() override;

    // Initialisation
    void Initialize(float radius, const sf::Color& color) override;
    void Initialize(float height, float width, const sf::Color& color) override {}

    // Physique
    void Repulse(Entity* other) override;
    bool IsColliding(Entity* other);
    bool IsInside(float x, float y);
    void Update() override;

protected:
    virtual void OnUpdate() override;
    virtual void OnCollision(Entity* collidedWith) override;
    virtual void OnInitialize() override;
    virtual void OnDestroy() override;
};
