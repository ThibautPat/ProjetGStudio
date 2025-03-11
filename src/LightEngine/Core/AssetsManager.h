#pragma once

#include "GameManager.h"
#include <map>

class AssetsManager
{

protected:

	std::map<std::string, sf::Texture*> mAssets;

public:

	AssetsManager();

	void Load(const char* path, std::string name);
	sf::Texture* GetTexture(std::string name);
	sf::Texture* GetTexture(std::string name, sf::IntRect rect);
	//sf::Texture* GetTile(std::string name);
};

