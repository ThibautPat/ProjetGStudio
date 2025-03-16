#include "TextureRender.h"

void TextureRender::AddAndSelectTexture(const char* path, const char* textName, sf::IntRect rect)
{
	TextureManager* assetsManager = GameManager::Get()->GetAssetsManager();
	assetsManager->LoadTexture(path, mTextName);
	SelectTexture(textName, rect);
}

void TextureRender::SelectTexture(const char* textName, sf::IntRect rect)
{
	mTextName = textName;
	mTextRect = rect;
}
