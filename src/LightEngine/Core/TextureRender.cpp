#include "TextureRender.h"

void TextureRender::SetupTexture(const char* path, const char* textName)
{
	TextureManager* assetsManager = GameManager::Get()->GetAssetsManager();
	mTextName = textName;
	assetsManager->Load(path, mTextName);
	assetsManager->Find(mTextName, this);
}
