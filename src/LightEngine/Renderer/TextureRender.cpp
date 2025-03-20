#include "../Renderer/TextureRender.h"
#include "../Other/Utils.h"

TextureRender::TextureRender(const char* spritesheetname, const char* spritename)
{
	mRenderRatio = sf::Vector2f(1.f, 1.f);
	mRenderTexture = new sf::Texture();
	mRenderSprite = new sf::Sprite();
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
	TextureManager* tm = GameManager::Get()->GetTextureManager();

	tm->SetTetxureWithRect(mSpriteSheetName, mTextRect, mRenderTexture);

	mRenderSprite->setTexture(*mRenderTexture);

	mRenderSprite->setScale(mRenderRatio);

	float offset = 0.5f;
	sf::Vector2f renderPos = sf::Vector2f(
		entity->GetPosition(0, 0).x - mRenderTexture->getSize().x * offset * mRenderRatio.x,
		entity->GetPosition(0, 0).y - mRenderTexture->getSize().y * offset * mRenderRatio.y);
	mRenderSprite->setPosition(renderPos);

	window->draw(*mRenderSprite);
}

void TextureRender::SetNames(std::string spritesheetname, std::string spritename)
{
	mSpriteSheetName = spritesheetname;
	mSpriteName = spritename;

}
