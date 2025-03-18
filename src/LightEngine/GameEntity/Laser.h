#pragma once
#include "../GameEntity/LaserEntity.h"

class Laser
{
protected:
	int mNb = 0.f;
	sf::Vector2f mLaserDir;
	std::vector<LaserEntity*> mLaser;

public:
	Laser(int nb, sf::Vector2f& dir, sf::IntRect& laser, const sf::Color& color = sf::Color::Red);

	void Update();
	void AddLaser();

	bool IsCollidingWithLaser(Entity* other);
};

