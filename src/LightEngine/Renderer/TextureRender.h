#pragma once

#include "../Entity/Entity.h"
#include "../Manager/TextureManager.h"

class TextureRender
{
protected:
	std::string mSpriteSheetName;
	std::string mSpriteName;

	sf::Vector2f mRenderRatio;
	sf::IntRect mTextRect;
	sf::Sprite* mRenderSprite;

public:
	TextureRender(const char* spritesheetname, const char* spritename);
	virtual ~TextureRender();

	/// <summary>
	/// Dessine la texture de l'entité
	/// </summary>
	void Draw(Entity* entity, sf::RenderWindow* window);

	void SetNames(const std::string& spritesheetname, const std::string& spritename);
	void SetTextureRect(const sf::IntRect& rect) { mTextRect = rect; }
	void SetRatio(const sf::Vector2f& nratio) { mRenderRatio = nratio; }

	sf::IntRect GetTextureRect() const { return mTextRect; }
	const std::string& GetSpriteSheetName() const { return mSpriteSheetName; }
	const std::string& GetSpriteName() const { return mSpriteName; }
};
