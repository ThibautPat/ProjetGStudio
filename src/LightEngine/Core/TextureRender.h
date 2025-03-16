#pragma once

#include "Entity.h"
#include "TextureManager.h"

#include "Render.h"

class TextureRender : public Render
{
protected:

	sf::IntRect mTextRect;

	std::string mTextName;

	sf::Vector2f mRenderRatio;

	//TODO stocker info json

public:

	TextureRender() { mRenderRatio = sf::Vector2f(1.f, 1.f); }

	/// <summary>
	/// Draw de la texture de l'entity (herite de Render)
	/// </summary>
	/// <param name="entity"></param>
	/// <param name="window"></param>
	void Draw(Entity* entity, sf::RenderWindow* window) override;

	/// <summary>
	/// Selectionne une texture depuis un fichier et l'associe à un nom (l'ajoute dans le TextureManager). Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="path">Chemin d'acces du fichier</param>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	void AddAndSelectTexture(const char* path, const char* textName, sf::IntRect rect);
	/// <summary>
	/// Selectionne une texture (stockee dans le TextureManager) depuis un nom. Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	void SelectTexture(const char* textName, sf::IntRect rect);

	void SetTextureRect(sf::IntRect& rect) { mTextRect = rect; }
	sf::IntRect* GetTextureRect() { return &mTextRect; }
	const std::string& GetTextName() { return mTextName; }

};

