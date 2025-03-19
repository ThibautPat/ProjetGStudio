#include "BackGround.h"

void BackGround::OnInitialize()
{
	SetPosition(0, 0);
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);

}

void BackGround::OnUpdate()
{
	//SetPosition(GetPosition(0,0).x + 7 * GetDeltaTime(),GetPosition(0,0).y);
}

void BackGround::SetBackGroundTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	mShape.setTexture(texture);
}
