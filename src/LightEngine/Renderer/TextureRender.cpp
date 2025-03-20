#include "../Renderer/TextureRender.h"
#include "../Other/Utils.h"

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

	mTextRect.left = mTextRect.width * Utils::GetInfoFromArray<int>(njson, charArray, "x");
	mTextRect.top = mTextRect.height * Utils::GetInfoFromArray<int>(njson, charArray, "y");
}

void TextureRender::Draw(Entity* entity, sf::RenderWindow* window)
{
	//A OPTI

	//faire en var membre
	TextureManager* tm = GameManager::Get()->GetTextureManager();

	//faire en var membre
	sf::Texture text = sf::Texture();

	tm->SetTetxureWithRect(mSpriteSheetName, mTextRect, &text);

	//faire en var membre
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

void TextureRender::SetNames(std::string spritesheetname, std::string spritename)
{
	mSpriteSheetName = spritesheetname;
	mSpriteName = spritename;

}
