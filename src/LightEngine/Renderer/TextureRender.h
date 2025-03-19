#pragma once

#include "../Entity/Entity.h"
#include "../Manager/TextureManager.h"

class TextureRender
{
protected:
	sf::IntRect mTextRect;

	std::string mSpriteSheetName;
	std::string mSpriteName;

	sf::Vector2f mRenderRatio;
public:

	TextureRender(const char* spritesheetname, const char* spritename);

	/// <summary>
	/// Draw de la texture de l'entity (herite de Render)
	/// </summary>
	/// <param name="entity"></param>
	/// <param name="window"></param>
	virtual void Draw(Entity* entity, sf::RenderWindow* window);

	/// <summary>
	/// Selectionne une texture depuis un fichier et l'associe � un nom (l'ajoute dans le TextureManager). Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="path">Chemin d'acces du fichier</param>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	//void SelectTexture(const char* spritesheetname, const char* spritename);

	/// <summary>
	/// Selectionne une texture (stockee dans le TextureManager) depuis un nom. Defini la zone de la texture (du disctionnaire) a conserver au rendu.
	/// </summary>
	/// <param name="textName">Nom du fichier attribuee dans le dictionnaire(std::map) du TextureManager</param>
	/// <param name="rect">Shape de la texture a conserver lors des rendus</param>
	//void SelectTexture(const char* textName, sf::IntRect rect);

	void SetNames(std::string spritesheetname, std::string spritename);
	void SetTextureRect(sf::IntRect& rect) { mTextRect = rect; }
	void SetRatio(sf::Vector2f& nratio) { mRenderRatio = nratio; }

	sf::IntRect* GetTextureRect() { return &mTextRect; }
	const std::string& GetSpriteSheetName() { return mSpriteSheetName; }
	const std::string& GetSpriteName() { return mSpriteName; }

};

