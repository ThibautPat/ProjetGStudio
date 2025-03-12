#pragma once

#include "Entity.h"
#include "AssetsManager.h"

class Textured //: public Entity
{
protected:
	sf::Texture mText;
	std::string mTextName;

public:

	Textured() {};

	void SetupTexture(const char* path, const char* textName);

	const std::string& GetTextName() { return mTextName; }
	void SetTexture(const sf::Texture& text) { mText = text; }
	sf::Texture* GetTexture() { return &mText; }

};

