#include "TextureRender.h"
#include "Utils.h"

TextureRender::TextureRender(const char* spritesheetname, const char* spritename)
{
	mRenderRatio = sf::Vector2f(1.f, 1.f);

	mSpriteSheetName = spritesheetname;
	mSpriteName = spritename;

	TextureManager* tm = GameManager::Get()->GetTextureManager();
	json* njson = tm->GetJson(mSpriteSheetName);

	mTextRect.width = Utils::GetInfoFromArray<int>(njson, "frame_size", "width");
	mTextRect.height = Utils::GetInfoFromArray<int>(njson, "frame_size", "height");

	const char* charArray = mSpriteName.c_str();

	mTextRect.left = Utils::GetInfoFromArray<int>(njson, charArray, "x");
	mTextRect.top = Utils::GetInfoFromArray<int>(njson, charArray, "y");
}

void TextureRender::Draw(Entity* entity, sf::RenderWindow* window)
{
	TextureManager* tm = GameManager::Get()->GetTextureManager();
	sf::Texture text = sf::Texture();

	json* njson = tm->GetJson(mSpriteSheetName);

	tm->SetTetxureWithRect(mSpriteSheetName, mTextRect, &text);

	sf::Sprite spr;
	spr.setTexture(text);

	spr.setScale(mRenderRatio);

	float offset = 0.5f;
	sf::Vector2f renderPos = sf::Vector2f(
		entity->GetPosition(0, 0).x - text.getSize().x * offset * mRenderRatio.x,
		entity->GetPosition(0, 0).y - text.getSize().y * offset * mRenderRatio.y);
	spr.setPosition(renderPos);

	window->draw(spr);
}

void TextureRender::SelectTexture(const char* spritesheetname, const char* spritename)
{
	TextureRender(spritesheetname, spritename);
}
