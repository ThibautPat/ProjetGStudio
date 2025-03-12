#pragma once
#include <SFML/System/Vector2.hpp>

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
class Collider;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
	float mSizeX, mSizeY;

    sf::Vector2f mDirection;
	Target mTarget;
    
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

	bool mBoolGravity = true;
	float mGravitySpeed = 0.f;
	float mSpeed = 0.f;

public:


	bool IsOnGround() { return not mBoolGravity; }
	float GetGravitySpeed() { return mGravitySpeed; }
	float GetSpeed() { return mSpeed;  }

	virtual void FixedUpdate(float dt) { Fall(dt); };
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	sf::Vector2f GetPosition(float ratioX, float ratioY);
	void Fall(float dt);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	void SetGravity(bool gravity) { mBoolGravity = gravity; }
	sf::Vector2f GetDirection() const { return mDirection; }
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }
	virtual Collider* GetCollider() = 0; //

	virtual sf::Shape* GetShape() = 0;

	bool IsTag(int tag) const { return mTag == tag; }
    virtual bool IsColliding(Entity* other) = 0; //
	virtual bool IsInside(float x, float y) = 0; //

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
	T* CreateCircleEntity(float radius, const sf::Color& color);

	template<typename T>
	T* CreateRectEntity(float height, float weight, const sf::Color& color); //

protected:
    Entity() = default;
    ~Entity() = default;

	virtual void OnUpdate() = 0;
    virtual void OnCollision(Entity* collidedWith) = 0;
	virtual void OnInitialize() = 0;
	virtual void OnDestroy() = 0;
	
    virtual void Update();
	virtual void Initialize(float radius, const sf::Color& color) = 0; //
	virtual void Initialize(float height, float weight, const sf::Color& color) = 0; //
	virtual void Repulse(Entity* other) = 0; // 

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"