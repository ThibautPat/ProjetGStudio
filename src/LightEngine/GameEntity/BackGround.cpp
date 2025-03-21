#include "BackGround.h"
#include "../GameScene/TestScene.h"
#include "../GameEntity/Player.h"
void BackGround::OnInitialize()
{
	SetPosition(0, 0);
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);

}

void BackGround::OnUpdate()
{
	Scene* sc = GetScene();
	for (Entity* entity : GameManager::Get()->GetEntities<Entity>())
	{
		if (dynamic_cast<Player*>(entity))
		{
			if (IsTag(TestScene::Tag::BACK_GROUND1))
				SetPosition(sc->GetView()->getCenter().x - entity->GetPosition(0, 0).x / 9.5f +200, sc->GetView()->getCenter().y-64);

			if (IsTag(TestScene::Tag::BACK_GROUND2BIS))
				SetPosition(sc->GetView()->getCenter().x - entity->GetPosition(0, 0).x / 6.5f + 200, sc->GetView()->getCenter().y - 64);
			if (IsTag(TestScene::Tag::BACK_GROUND2))
				SetPosition(sc->GetView()->getCenter().x - entity->GetPosition(0, 0).x / 5.5f + 200, sc->GetView()->getCenter().y - 64);
		}
	}
	if (dynamic_cast<TestScene*>(sc))
	SetPosition(GetPosition(0, 0).x, sc->GetView()->getCenter().y);
}

void BackGround::SetBackGroundTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	mShape.setTexture(texture);
}
