#include "TextureManager.h"
#include "TextureRender.h"

sf::Texture* TextureManager::LoadSpriteSheet(const char* jsonpath, const char* sourcepath, std::string spritesheetname)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(sourcepath))
		return nullptr;
	mSpriteSheet.insert({ spritesheetname , text });

	json* njson = new json();

	//TODO
	auto fichier(jsonpath);
	if (fichier.is_open()) {
		json data;
		fichier >> *njson;
		fichier.close();
		std::cout << "Json parse !" << std::endl;
	}

	mJson.insert({ spritesheetname , njson });

	std::cout << "SpriteSheet loaded and Json path added" << std::endl;
	return text;
}

//void TextureManager::FindTexture(std::string spritesheetname, std::string spritename, sf::IntRect* textrect)
//{
//	std::string jsonPath = mJson.at(spritesheetname);
//
//	std::ifstream fichier(jsonPath);
//	if (fichier.is_open()) {
//		json data;
//		fichier >> data;
//		fichier.close();
//
//		json anim = data["animations"];
//
//		if (anim.contains(spritename))
//		{
//			json animstate = anim[spritename];
//
//			std::string xinfo = "x";
//			std::string yinfo = "y";
//			textrect->left = GetSpriteInfo<int>(spritesheetname, spritename, xinfo);
//			textrect->top = GetSpriteInfo<int>(spritesheetname, spritename, yinfo);
//
//			std::string width = "width";
//			std::string height = "height";
//			textrect->width = GetSpriteInfo<int>(spritesheetname, spritename, width);
//			textrect->height = GetSpriteInfo<int>(spritesheetname, spritename, height);
//		}
//	}
//
//}

sf::Texture* TextureManager::LoadTexture(const char* path, std::string name)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(path))
		return nullptr;
	mSpriteSheet.insert({ name , text });

	return text;
}

void TextureManager::FindTexture(std::string name, sf::Texture* text)
{
	*text = *mSpriteSheet.at(name);
}

void TextureManager::FindTexture(std::string name, sf::IntRect rect, sf::Texture* text)
{
	if (mSpriteSheet.at(name) == nullptr)
		std::cout << "Asset on assetmanager null" << std::endl;
	sf::Texture texture = *mSpriteSheet.at(name);

	sf::RenderTexture renderTexture;
	renderTexture.create(rect.width, rect.height); // Taille du recadrage

	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height)); // On recadre la texture
	sprite.setPosition(0, 0); // On le dessine en (0,0) pour que ça remplisse bien

	renderTexture.clear(sf::Color(0,0,0,0));
	renderTexture.draw(sprite);
	renderTexture.display();

	*text = renderTexture.getTexture();

}
