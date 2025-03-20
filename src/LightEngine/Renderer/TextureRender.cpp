#include "../Renderer/TextureRender.h"
#include "../Other/Utils.h"

TextureRender::TextureRender(const char* spritesheetname, const char* spritename)
{
    mRenderRatio = sf::Vector2f(1.f, 1.f);
    mRenderSprite = new sf::Sprite();
    mSpriteSheetName = spritesheetname;
    mSpriteName = spritename;
    mTextRect = sf::IntRect(0, 0, 0, 0);

    TextureManager* tm = GameManager::Get()->GetTextureManager();
    json* njson = tm->GetJson(mSpriteSheetName);

    if (njson) {
        mTextRect.width = Utils::GetInfoFromArray<int>(njson, "frame_size", "width");
        mTextRect.height = Utils::GetInfoFromArray<int>(njson, "frame_size", "height");

        const char* charArray = mSpriteName.c_str();
        mTextRect.left = mTextRect.width * Utils::GetInfoFromArray<int>(njson, charArray, "x");
        mTextRect.top = mTextRect.height * Utils::GetInfoFromArray<int>(njson, charArray, "y");
    }


    sf::Texture* fullTexture = tm->GetTexture(spritesheetname);
    if (fullTexture)
    {
        sf::Vector2u textureSize = fullTexture->getSize();
        if (textureSize.x == 0 || textureSize.y == 0)
        {
            std::cerr << "Erreur: La texture '" << spritesheetname << "' est vide ou non chargée !" << std::endl;
            return;
        }

        sf::Image fullImage = fullTexture->copyToImage();

        if (fullImage.getSize().x == 0 || fullImage.getSize().y == 0)
        {
            std::cerr << "Erreur: L'image copiée est vide !" << std::endl;
            return;
        }

        sf::Image croppedImage;
        croppedImage.create(mTextRect.width, mTextRect.height);
        croppedImage.copy(fullImage, 0, 0, mTextRect);

        sf::Texture* mTexture = new sf::Texture();
        if (mTexture->loadFromImage(croppedImage)) {
            mRenderSprite->setTexture(*mTexture, true);
        }
        mRenderSprite->setOrigin(mTextRect.width / 2, mTextRect.height / 2);
        mRenderSprite->setScale(mRenderRatio);
    }
}

TextureRender::~TextureRender()
{
    delete mRenderSprite;
}

void TextureRender::Draw(Entity* entity, sf::RenderWindow* window)
{
    if (!mRenderSprite || !mRenderSprite->getTexture()) return;

    mRenderSprite->setPosition(entity->GetPosition(0, 0));

    window->draw(*mRenderSprite);
}

void TextureRender::SetNames(const std::string& spritesheetname, const std::string& spritename)
{
    mSpriteSheetName = spritesheetname;
    mSpriteName = spritename;
}
