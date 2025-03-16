#pragma once

#include "Entity.h"
#include "TextureManager.h"

class TextureRender
{
protected:

	sf::IntRect mTextRect;

	//peut être utile pour les animations ?
	std::string mTextName;

public:

	TextureRender() {};

	/// <summary>
	/// Selectionne une texture depuis un fichier et l'associe à un nom (l'ajoute dans l'AssetManager). Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="path">Chemin d'acces du fichier</param>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) de l'AssetManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	void AddAndSelectTexture(const char* path, const char* textName, sf::IntRect rect);
	/// <summary>
	/// Selectionne une texture (stockee dans l'AssetManager) depuis un nom. Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) de l'AssetManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	void SelectTexture(const char* textName, sf::IntRect rect);

	void SetTextureRect(sf::IntRect& rect) { mTextRect = rect; }
	sf::IntRect* GetTextureRect() { return &mTextRect; }
	const std::string& GetTextName() { return mTextName; }

};

