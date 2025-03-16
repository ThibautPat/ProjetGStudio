#pragma once

#include "GameManager.h"
#include <map>

class TextureRender;


class TextureManager
{

protected:

	std::map<std::string, sf::Texture*> mAssets;

public:

	TextureManager() {};

	/// <summary>
	/// Charge la texture dans le dictionnaire(std::map) du TextureManager.
	/// </summary>
	/// <param name="path">Chemin d'acces de la texture</param>
	/// <param name="name">Nom de </param>
	/// <returns></returns>
	sf::Texture* LoadTexture(const char* path, std::string name);
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à la texture envoyee en parametre.
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="textured">Texture a laquelle on applique la texture du dictionnaire</param>
	void FindTexture(std::string name, sf::Texture* text);
	/// <summary>
	/// Cherche la texture dans le dictionnaire et l'associe à la texture en fonction de la shape.
	/// </summary>
	/// <param name="name">Nom de la texture dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="textured">Texture a laquelle on applique la texture du dictionnaire</param>
	/// <param name="rect">Zone de la texture a conserver</param>
	void FindTexture(std::string name, sf::IntRect rect, sf::Texture* text);
};

