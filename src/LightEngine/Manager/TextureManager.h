#pragma once

#include "GameManager.h"
#include <map>
#include <iostream>
#include <fstream>
#include "../Library/json.hpp"

using json = nlohmann::json;

class TextureRender;

class TextureManager
{

protected:

	std::map<std::string, sf::Texture*> mSpriteSheet;
	std::map<std::string, json*> mJson;

public:

	TextureManager() {};

	/// <summary>
	/// Ajoute une SpriteSheet et son json aux maps, les relie tout les 2 par un nom
	/// </summary>
	/// <param name="jsonpath">: Chemin d'acces du json</param>
	/// <param name="sourcepath">: Chemin d'acces de l'image</param>
	/// <param name="name">: Nom de connexion</param>
	/// <returns></returns>
	sf::Texture* LoadSpriteSheet(const char* jsonpath, const char* sourcepath, std::string name);

	json* GetJson(std::string spritesheetname);

	/// <summary>
	/// Retourne une SpriteSheet entiere
	/// </summary>
	/// <param name="spritesheetname">: Nom de la SpriteSheet</param>
	/// <returns></returns>
	sf::Texture* GetTexture(std::string spritesheetname);

	/// <summary>
	/// Retourne un Sprite de la SpriteSheet
	/// </summary>
	/// <param name="spritesheetname">: Nom de la SpriteSheet</param>
	/// <param name="texturerender">: Zone du Sprite</param>
	/// <param name="text">: Texture a definir</param>
	void SetTetxureWithRect(std::string spritesheetname, sf::IntRect texturerender, sf::Texture* text);
};
