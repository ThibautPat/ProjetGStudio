#pragma once

#include "GameManager.h"
#include <map>

class AssetsManager
{

protected:

	std::map<std::string, sf::Texture*> mAssets;

public:

	AssetsManager();

	sf::Texture* Load(const char* path, std::string name);
	void SetTexture(std::string name, Entity* entity);
	void SetTexture(std::string name, Entity* entity, sf::IntRect rect);
};

