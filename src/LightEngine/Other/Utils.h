#pragma once

#include <SFML/System/Vector2.hpp>
#include "../nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2);

	json* Parse(const char* path);

	/// <summary>
	/// Cherche et retourne une info du json
	/// </summary>
	/// <param name="jsontoexploit">Json parse dans lequel on pioche l'info</param>
	/// <param name="infoname">Nom de l'information dans le json ("exemple" : ...)</param>
	/// <typeparam name="T">Choisir parmis ces types : int, bool, std::string (le type selectionne doit correspondre au type stocke dans le json)</typeparam>
	/// <returns>Retourne la valeur de l'info</returns>
	template<typename T>
	T GetInfo(json* jsontoexploit, const char* infoname);

	/// <summary>
	/// Cherche et retourne une info d'un tableau du json
	/// </summary>
	/// <param name="jsontoexploit">Json parse dans lequel on pioche l'info</param>
	/// <param name="arrayName">Tableau du json dans lequel est stocke l'info</param>
	/// <param name="infoname">Nom de l'information dans le json ("exemple" : ...)</param>
	/// <typeparam name="T">Choisir parmis ces types : int, bool, std::string (le type selectionne doit correspondre au type stocke dans le json)</typeparam>
	/// <returns>Retourne la valeur de l'info</returns>
	template<typename T>
	T GetInfoFromArray(json* jsontoexploit, const char* arrayName, const char* infoname);
};

#include "Utils.inl"
