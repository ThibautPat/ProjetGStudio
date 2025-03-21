#pragma once
#include "../Manager/GameManager.h"

class Battery
{
	sf::Texture* mBatteryTexture1 = new sf::Texture;
	sf::Texture* mBatteryTexture2 = new sf::Texture;
	sf::Texture* mBatteryTexture3 = new sf::Texture;

	sf::Sprite* mSprite1 = new sf::Sprite;
	sf::Sprite* mSprite2 = new sf::Sprite;
	sf::Sprite* mSprite3 = new sf::Sprite;

	sf::IntRect mRect;
	int mTotalFrames;

public:
	Battery();

	void Update(float timerValue, float maxTime, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
};

