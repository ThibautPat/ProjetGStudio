#pragma once
#include "../GameEntity/LaserEntity.h"

class Laser : public Entity
{
protected:

	sf::Vector2f mStart;
	sf::Vector2f mEnd;

	//--------

	int mNb = 0.f;
	sf::Vector2f mLaserDir;
	std::vector<LaserEntity*> mLaser;

public:

	virtual void OnUpdate() = 0;
	virtual void OnCollision(Entity* collidedWith) = 0;
	virtual void OnDestroy() = 0;
	virtual void Initialize(float x, float y, const sf::Color& color);

	void OnInitialize();
	virtual void Initialize(float radius, const sf::Color& color) {} ;
	void Repulse(Entity* other) {};

	//-----------
	Laser(int nb, sf::Vector2f& dir, sf::IntRect& laser, const sf::Color& color = sf::Color::Red);

	void Update();
	void AddLaser();

	bool IsCollidingWithLaser(Entity* other);
};

