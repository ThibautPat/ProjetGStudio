#include "AssetsManager.h"

AssetsManager::AssetsManager()
{
}

void AssetsManager::Load(const char* path, std::string name)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(path))
		return;
	mAssets.insert({ name , text });
}

sf::Texture* AssetsManager::GetTexture(std::string name)
{
	return mAssets.at(name);
}

sf::Texture* AssetsManager::GetTexture(std::string name, sf::IntRect rect)
{

	sf::Texture* tmp = new sf::Texture();
	tmp->create(rect.width, rect.height);
	//tmp->

	return nullptr;
}
