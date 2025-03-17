#pragma once

#include "GameManager.h"
#include <map>
#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class TextureRender;

class TextureManager
{

protected:

	std::map<std::string, sf::Texture*> mSpriteSheet;
	std::map<std::string, json*> mJson;

public:

	TextureManager() {};

	sf::Texture* LoadSpriteSheet(const char* jsonpath, const char* sourcepath, std::string name);

	//void FindTexture(std::string spritesheetname, std::string spritename, sf::IntRect* textrect);

	template<typename T>
	T GetAnimationInfo(std::string& spritesheetname, std::string& spritename, std::string& info);

	template<typename T>
	T GetSpriteSheetInfo(std::string& spritesheetname, std::string& infotype, std::string& info);


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
	/// <param name="rect">Zone de la texture a conserver</param>
	/// <param name="textured">Texture a laquelle on applique la texture du dictionnaire</param>
	void FindTexture(std::string name, sf::IntRect rect, sf::Texture* text);
};

template<typename T>
inline T TextureManager::GetAnimationInfo(std::string& spritesheetname, std::string& spritename, std::string& info)
{
	std::string jsonPath = mJson.at(spritesheetname);

	std::ifstream fichier(jsonPath);
	if (fichier.is_open()) {
		json data;
		fichier >> data;
		fichier.close();

		json anim = data["animations"];

		if (anim.contains(spritename))
		{
			json animstate = anim[spritename];

			if (animstate.contains(info))
			{
				std::cout << spritename << " contain " << info << std::endl;
				return (T)animstate[info];
			}

			std::cout << spritename << " not contain " << info << std::endl;
		}

		std::cout << spritename << " not contain in animations" << std::endl;
	}

	return NULL;
}

template<typename T>
inline T TextureManager::GetSpriteSheetInfo(std::string& spritesheetname, std::string& infotype, std::string& info)
{
	std::string jsonPath = mJson.at(spritesheetname);

	std::ifstream fichier(jsonPath);
	if (fichier.is_open()) {
		json data;
		fichier >> data;
		fichier.close();

		if (data.contains(infotype)) {

			json type = data[infotype];

			if (type.contains(info)) {

				std::cout << infotype << " is " << info << std::endl;
				return (T)type[info];
			}
			else {

				std::cout << "info has " << info << std::endl;
				return (T)data[infotype];
			}
		}
	}

	return NULL;
}
