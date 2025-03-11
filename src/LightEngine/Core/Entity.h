#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#define GRAVITYACCEL 9.81f
#define AIRRESISANTCE GRAVITYACCEL/4

namespace sf 
{
	class Shape;
    class Color;
}
struct PlayerData
{
	float mJumpHeight = 600.f; // #TODO: Change to jump force
	float mJumpTime = 0.3f;
	float mMinSpeed = 0.f;
	float mMaxSpeed = 20000.f;
	float mAcceleration = 700.f;
	float mDeceleration = 500.f;
};
class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
	Target mTarget;
    
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

public:
	bool mBoolGravity = true;
	float mGravitySpeed = 0.f;
	float mSpeed = 0.f;
	int secondjump = 2;
	float mVelocitySpeed = 0.f;
	float mVelocityMax = 0.f;

	virtual void FixedUpdate(float dt) { Fall(dt); };
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	void SetGravity(bool gravity) { mBoolGravity = gravity; }
	float GetRadius() const { return mShape.getRadius(); }
	sf::Vector2f GetDirection() const { return mDirection; }
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) const;
	bool IsInside(float x, float y) const;

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

protected:
    Entity() = default;
    ~Entity() = default;

	virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	void Fall(float dt);
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);
	void Repulse(Entity* other);
	

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"