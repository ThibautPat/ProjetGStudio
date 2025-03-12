#include "Textured.h"

void Textured::SetupTexture(const char* path, const char* textName)
{
	AssetsManager* assetsManager = GameManager::Get()->GetAssetsManager();
	mTextName = textName;
	assetsManager->Load(path, mTextName);
	assetsManager->SetTexture(mTextName, this);
}
