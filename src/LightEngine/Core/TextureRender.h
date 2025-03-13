#pragma once

#include "Entity.h"
#include "TextureManager.h"

class TextureRender
{
protected:

	//Revoir avec un rect pour le rendu
	sf::Texture mText;

	//peut être utile pour les animations ?
	std::string mTextName;

public:

	TextureRender() {};

	/// <summary>
	/// Charge une texture depuis un fichier et l'associe à un nom. Le tout est stocke dans l'AssetManager, puis la texture brute est liee à l'entity.
	/// </summary>
	/// <param name="path">Chemin d'acces du fichier</param>
	/// <param name="textName">Nom du fichier attribuer dans le dictionnaire(std::map) de l'AssetManager</param>
	void SetupTexture(const char* path, const char* textName);

	const std::string& GetTextName() { return mTextName; }
	void SetTexture(const sf::Texture& text) { mText = text; }
	sf::Texture* GetTexture() { return &mText; }

};

