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
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à l'entity via Textured::SetTexture
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::list) de l'AssetManager</param>
	/// <param name="textured">Gestionnaire de textures de l'entity</param>
	void SetTexture(std::string name, Textured* textured);
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à l'entity via Textured::SetTexture. Recadre la texture avant de l'associer.
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::list) de l'AssetManager</param>
	/// <param name="textured">Gestionnaire de textures de l'entity</param>
	/// <param name="rect">Zone de la texture stockee dans le dictionnaire a envoyer dans l'entity</param>
	void SetTexture(std::string name, Textured* textured, sf::IntRect rect);
};

