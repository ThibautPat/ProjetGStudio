#include "AssetsManager.h"

AssetsManager::AssetsManager()
{
}

sf::Texture* AssetsManager::Load(const char* path, std::string name)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(path))
		return nullptr;
	mAssets.insert({ name , text });

	return text;
}

void AssetsManager::SetTexture(std::string name, Entity* entity)
{
	entity->SetTexture(*mAssets.at(name));
}

void AssetsManager::SetTexture(std::string name, Entity* entity, sf::IntRect rect)
{
	sf::Texture texture = *mAssets.at(name);

	sf::RenderTexture renderTexture;
	renderTexture.create(rect.width, rect.height); // Taille du recadrage

	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height)); // On recadre la texture
	sprite.setPosition(0, 0); // On le dessine en (0,0) pour que ça remplisse bien

	renderTexture.clear();
	renderTexture.draw(sprite);
	renderTexture.display();

	entity->SetTexture(renderTexture.getTexture());

}
