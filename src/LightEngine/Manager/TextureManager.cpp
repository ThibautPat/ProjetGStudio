#include "TextureManager.h"
#include "TextureRender.h"
#include "Utils.h"

sf::Texture* TextureManager::LoadSpriteSheet(const char* jsonpath, const char* sourcepath, std::string spritesheetname)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(sourcepath))
		return nullptr;
	mSpriteSheet.insert({ spritesheetname , text });

	json* njson = Utils::Parse(jsonpath);

	mJson.insert({ spritesheetname , njson });

	return text;
}

json* TextureManager::GetJson(std::string name)
{
	return mJson.at(name);
}

sf::Texture* TextureManager::GetTexture(std::string name)
{
	return mSpriteSheet.at(name);
}

void TextureManager::SetTetxureWithRect(std::string spritesheetname, sf::IntRect texturerender, sf::Texture* text)
{
	if (!GetTexture(spritesheetname))
		std::cout << "Pas de texture avec ce nom dans la map" << std::endl;

	sf::Texture texture = *GetTexture(spritesheetname);

	sf::RenderTexture renderTexture;
	renderTexture.create(texturerender.width, texturerender.height); // Taille du recadrage

	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(texturerender.left, texturerender.top, texturerender.width, texturerender.height)); // On recadre la texture
	sprite.setPosition(0, 0); // On le dessine en (0,0) pour que �a remplisse bien

	renderTexture.clear(sf::Color(0,0,0,0)); //Color(0,0,0,0) pour supporter la transparence
	renderTexture.draw(sprite);
	renderTexture.display();

	*text = renderTexture.getTexture();
}
