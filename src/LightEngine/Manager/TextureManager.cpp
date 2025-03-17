#include "TextureManager.h"
#include "../Renderer/TextureRender.h"
#include <iostream>

sf::Texture* TextureManager::LoadTexture(const char* path, std::string name)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(path))
		return nullptr;
	mAssets.insert({ name , text });

	return text;
}

void TextureManager::FindTexture(std::string name, sf::Texture* text)
{
	*text = *mAssets.at(name);
}

void TextureManager::FindTexture(std::string name, sf::IntRect rect, sf::Texture* text)
{
	if (mAssets.at(name) == nullptr)
		std::cout << "Asset on assetmanager null" << std::endl;
	sf::Texture texture = *mAssets.at(name);

	sf::RenderTexture renderTexture;
	renderTexture.create(rect.width, rect.height); // Taille du recadrage

	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height)); // On recadre la texture
	sprite.setPosition(0, 0); // On le dessine en (0,0) pour que ça remplisse bien

	renderTexture.clear();
	renderTexture.draw(sprite);
	renderTexture.display();

	*text = renderTexture.getTexture();
}
