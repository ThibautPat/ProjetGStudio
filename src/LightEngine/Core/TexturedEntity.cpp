#include "TexturedEntity.h"

void TexturedEntity::SetupTexture(const char* path, const char* textName)
{
	AssetsManager* assetsManager = GameManager::Get()->GetAssetsManager();
	mTextName = textName;
	assetsManager->Load(path, mTextName);
	assetsManager->SetTexture(mTextName, this, sf::IntRect(0, 0, 18 * 4, 18 * 4));
}
