#include "Battery.h"

Battery::Battery()
{
    mTotalFrames = 10;

    mBatteryTexture1->loadFromFile("../../../res/Assets/Battery/Batterie_fond.png");
    mBatteryTexture2->loadFromFile("../../../res/Assets/Battery/Batterie_barres.png");
    mBatteryTexture3->loadFromFile("../../../res/Assets/Battery/Batterie_branche.png");

    int frameWidth = mBatteryTexture2->getSize().x / mTotalFrames;
    int frameHeight = mBatteryTexture2->getSize().y;

    mRect = sf::IntRect(0, 0, 0, frameHeight);

    mSprite1->setTexture(*mBatteryTexture1);
    mSprite2->setTexture(*mBatteryTexture2);
    mSprite2->setTextureRect(mRect);
    mSprite3->setTexture(*mBatteryTexture3);

    mSprite1->setScale(0.4f, 0.35f);
    mSprite2->setScale(0.4f, 0.35f);
    mSprite3->setScale(0.4f, 0.35f);

}

void Battery::Update(float timerValue, float maxTime, sf::Vector2f position)
{
    mSprite1->setPosition(position.x, position.y);
    mSprite2->setPosition(position.x, position.y);
    mSprite3->setPosition(position.x, position.y);

    float chargeRatio = timerValue / maxTime;
    int newWidth = static_cast<int>((mSprite2->getTexture()->getSize().x) * chargeRatio);

    mRect.width = newWidth;
    mSprite2->setTextureRect(mRect);
}

void Battery::Draw(sf::RenderWindow& window)
{
    window.draw(*mSprite1);
    window.draw(*mSprite2);
    window.draw(*mSprite3);
}