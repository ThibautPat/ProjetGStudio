#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

constexpr float GRAVITY_ACCEL = 9.81f;
constexpr float AIR_RESISTANCE = GRAVITY_ACCEL / 4.0f;

class Scene;
class Collider;
class TextureRender;
class TextureManager;

class Entity {
public:
    struct Target {
        sf::Vector2i position;
        float distance = 0.0f;
        bool isSet = false;
    };

protected:
    float mSizeX = 0.0f, mSizeY = 0.0f;
    sf::Vector2f mDirection;
    sf::Vector2f mMove;
    Target mTarget;

    bool mToDestroy = false;
    int mTag = -1;
    bool mRigidBody = false;
    bool mKinematic = false;
    bool mBoolGravity = true;
    float mGravitySpeed = 0.0f;
    float mSpeed = 0.0f;

public:
    bool hasCollidedLastFrame = false;

    Entity() = default;
    virtual ~Entity() = default;

    // Getters
    bool IsOnGround() const { return !mBoolGravity; }
    bool GetGravity() const { return mBoolGravity; }
    float GetGravitySpeed() const { return mGravitySpeed; }
    float GetSpeed() const { return mSpeed; }
    sf::Vector2f GetDirection() const { return mDirection; }
    bool IsRigidBody() const { return mRigidBody; }
    bool IsKinematic() const { return mKinematic; }
    bool ToDestroy() const { return mToDestroy; }
    bool IsTag(int tag) const { return mTag == tag; }
    sf::Vector2f GetPosition(float ratioX, float ratioY);

    // Setters
    void SetSpeed(float speed) { mSpeed = speed; }
    void SetGravitySpeed(float speed) { mGravitySpeed = speed; }
    void SetTag(int tag) { mTag = tag; }
    void SetGravity(bool gravity) { mBoolGravity = gravity; }
    void SetRigidBody(bool isRigidBody) { mRigidBody = isRigidBody; }
    void SetIsKinematic(bool isKinematic) { mKinematic = isKinematic; }
    void SetPosition(float x, float y, float ratioX = 0.0f, float ratioY = 0.0f);
    void SetDirection(float x, float y, float speed = -1.0f);

    // Movement & Physics
    virtual void FixedUpdate(float dt) { Fall(dt); }
    void Fall(float dt);
    bool GoToDirection(int x, int y, float speed = -1.0f);
    bool GoToPosition(int x, int y, float speed = -1.0f);

    // Collision
    virtual bool IsColliding(Entity* other) = 0;
    virtual bool IsInside(float x, float y) = 0;
    virtual Collider* GetCollider() = 0;
    virtual sf::Shape* GetShape() = 0;
    virtual void Repulse(Entity* other) = 0;
    virtual void Block(Entity* other) = 0;

    // Render
    virtual TextureRender* GetTextureRender() { return nullptr; }
    virtual void InitRender(const char* spritesheetname, const char* spritename) = 0;

    // Lifecycle
    void Destroy();
    virtual void OnUpdate() = 0;
    virtual void OnCollision(Entity* collidedWith) = 0;
    virtual void OnInitialize() = 0;
    virtual void OnDestroy() = 0;

    // Scene & Entity Creation
    template<typename T> T* GetScene() const;
    Scene* GetScene() const;
    float GetDeltaTime() const;

    template<typename T>
    T* CreateCircleEntity(float radius, const sf::Color& color);

    template<typename T>
    T* CreateRectEntity(float height, float width, const sf::Color& color);

protected:
    virtual void Update();
    virtual void Initialize(float radius, const sf::Color& color) = 0;
    virtual void Initialize(float height, float width, const sf::Color& color) = 0;

    friend class GameManager;
    friend class Scene;
};

#include "Entity.inl"