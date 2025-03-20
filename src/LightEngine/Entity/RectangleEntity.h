#pragma once

#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Renderer/TextureRender.h"

class Scene;
class AABBCollider;
class Collider;

class RectangleEntity : public Entity
{
protected:
    sf::RectangleShape mShape;
    AABBCollider* mCollider = nullptr;


    TextureRender* mTexture;

public:    

    bool mReverse = false;

    virtual TextureRender* GetRender() { return mTexture; }
    void InitRender(const char* spritesheetname, const char* spritename) override { mTexture = new TextureRender(spritesheetname, spritename); }
    // Getters
    Collider* GetCollider() override;
    sf::Shape* GetShape() override;

    // Collision & Position
    bool IsColliding(Entity* other) override;
    bool IsInside(float x, float y) override;

    // Initialisation
    void Initialize(float radius, const sf::Color& color) override {}
    void Initialize(float height, float width, const sf::Color& color) override;

    // Physique
    void Repulse(Entity* other) override;
	virtual void Block(Entity* other) override;
    void Update() override;

protected:
    virtual void OnUpdate() override {}
    virtual void OnCollision(Entity* collidedWith) override {}
    virtual void OnInitialize() override;
    virtual void OnDestroy() override {}
};
