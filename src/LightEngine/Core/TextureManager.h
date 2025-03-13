#pragma once

#include "GameManager.h"
#include <map>

class TextureRender;

class TextureManager
{

protected:

	std::map<std::string, sf::Texture*> mAssets;

public:

	TextureManager();

	/// <summary>
	/// Charge la texture dans le dictionnaire(std::map) de l'AssetManager
	/// </summary>
	/// <param name="path">Chemin d'acces de la texture</param>
	/// <param name="name">Nom de </param>
	/// <returns></returns>
	sf::Texture* Load(const char* path, std::string name);
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à l'entity via Textured::SetTexture
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::map) de l'AssetManager</param>
	/// <param name="textured">Gestionnaire de textures de l'entity</param>
	void Find(std::string name, TextureRender* textured);
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à l'entity via Textured::SetTexture. Recadre la texture avant de l'associer.
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::map) de l'AssetManager</param>
	/// <param name="textured">Gestionnaire de textures de l'entity</param>
	/// <param name="rect">Zone de la texture stockee dans le dictionnaire a envoyer dans l'entity</param>
	void Find(std::string name, TextureRender* textured, sf::IntRect rect);
};

