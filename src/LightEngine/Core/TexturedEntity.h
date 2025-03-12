#pragma once

#include "Entity.h"
#include "AssetsManager.h"

class TexturedEntity : public Entity
{
protected:
	sf::Texture mText;
	std::string mTextName;

public:

	void SetupTexture(const char* path, const char* textName);

	const std::string& GetTextName() { return mTextName; }
	void SetTexture(const sf::Texture& text) override { mText = text; }
	sf::Texture* GetTexture() override { return &mText; }

};

