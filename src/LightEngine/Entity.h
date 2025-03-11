#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

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
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	sf::Vector2f GetPosition(float ratioX, float ratioY);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
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

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
    virtual void Update();
	virtual void Initialize(float radius, const sf::Color& color) = 0; //
	virtual void Initialize(float height, float weight, const sf::Color& color) = 0; //
	virtual void Repulse(Entity* other) = 0; // 

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"