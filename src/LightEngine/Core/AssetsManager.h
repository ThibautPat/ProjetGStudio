#pragma once

#include "GameManager.h"
#include <map>

class Textured;

class AssetsManager
{

protected:

	std::map<std::string, sf::Texture*> mAssets;

public:

	AssetsManager();

	sf::Texture* Load(const char* path, std::string name);
	void SetTexture(std::string name, Textured* textured);
	void SetTexture(std::string name, Textured* textured, sf::IntRect rect);
};

