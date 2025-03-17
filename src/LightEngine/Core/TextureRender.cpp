#include "TextureRender.h"

void TextureRender::Draw(Entity* entity, sf::RenderWindow* window)
{
	//TextureManager* tm = GameManager::Get()->GetTextureManager();
	//sf::Texture text = *entity->GetRender()->GetTexture();

	//sf::Sprite spr;
	//spr.setTexture(mTexture);
	//spr.setTextureRect(mTextRect);
	//
	////TODO Remove this
	//mRenderRatio = sf::Vector2f(5, 5);
	////-----
	//spr.setScale(mRenderRatio);

	//float offset = 0.5f;
	//sf::Vector2f renderPos = sf::Vector2f(
	//	entity->GetPosition(0, 0).x - text.getSize().x * offset * mRenderRatio.x,
	//	entity->GetPosition(0, 0).y - text.getSize().y * offset * mRenderRatio.y);
	//spr.setPosition(renderPos);

	//window->draw(spr);

	TextureManager* tm = GameManager::Get()->GetTextureManager();
	sf::Texture text = sf::Texture();

	tm->FindTexture(mSpriteSheetName, mTextRect, &text);

	sf::Sprite spr;
	spr.setTexture(text);

	//TODO Remove this
	//mRenderRatio = sf::Vector2f(5, 5);
	//-----
	spr.setScale(mRenderRatio);

	float offset = 0.5f;
	sf::Vector2f renderPos = sf::Vector2f(
		entity->GetPosition(0, 0).x - text.getSize().x * offset * mRenderRatio.x,
		entity->GetPosition(0, 0).y - text.getSize().y * offset * mRenderRatio.y);
	spr.setPosition(renderPos);

	window->draw(spr);
}

void TextureRender::AddAndSelectTexture(const char* path, const char* textName, sf::IntRect rect)
{
	TextureManager* assetsManager = GameManager::Get()->GetTextureManager();
	assetsManager->LoadTexture(path, mSpriteSheetName);

	SelectTexture(textName, rect);
}

void TextureRender::SelectTexture(const char* textName, sf::IntRect rect)
{
	mSpriteSheetName = textName;
	mTextRect = rect;

	//TextureManager* tm = GameManager::Get()->GetTextureManager();
	//tm->FindTexture(mSpriteSheetName, &mTexture);
}
