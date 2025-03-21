#include "../Manager/TextureManager.h"
#include "../Renderer/TextureRender.h"
#include "../Other/Utils.h"

sf::Texture* TextureManager::LoadSpriteSheet(const char* jsonpath, const char* sourcepath, std::string spritesheetname)
{
	sf::Texture* text = new sf::Texture();
	if (!text->loadFromFile(sourcepath))
		return nullptr;
	if (text == nullptr)
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

