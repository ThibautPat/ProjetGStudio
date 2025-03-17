#pragma once

#include "SFML/Graphics.hpp"

class Entity;

class Render
{
protected:

	//sf::Texture mTexture;

	sf::IntRect mTextRect;

	std::string mSpriteSheetName;
	std::string mSpriteName;

	sf::Vector2f mRenderRatio;

public:

	void SetNames(std::string spritesheetname, std::string spritename);
	void SetTextureRect(sf::IntRect& rect) { mTextRect = rect; }
	void SetRation(sf::Vector2f& nratio) { mRenderRatio = nratio; }

	sf::IntRect* GetTextureRect() { return &mTextRect; }
	const std::string& GetSpriteSheetName() { return mSpriteSheetName; }

	virtual void Draw(Entity* entity, sf::RenderWindow* window) = 0;
};

