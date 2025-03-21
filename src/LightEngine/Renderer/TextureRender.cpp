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

    if (!mLoadTexture) { // Vérifier si la texture est déjà chargée
        mLoadTexture = tm->GetTexture(spritesheetname); // Charger la texture complète
        if (mLoadTexture)
        {
            mRenderSprite->setTexture(*mLoadTexture, true);
        }
    }
    mRenderSprite->setTextureRect(mTextRect); // Définir la zone initiale
    mRenderSprite->setOrigin(mTextRect.width / 2, mTextRect.height / 2);
    mRenderSprite->setScale(mRenderRatio);
}

TextureRender::~TextureRender()
{
    delete mRenderSprite;
    delete mLoadTexture; // Libérer la mémoire
}

void TextureRender::ResetRect()
{
    TextureManager* tm = GameManager::Get()->GetTextureManager();
    json* njson = tm->GetJson(mSpriteSheetName);

    mTextRect.width = Utils::GetInfoFromArray<int>(njson, "frame_size", "width");
    mTextRect.height = Utils::GetInfoFromArray<int>(njson, "frame_size", "height");

    const char* charArray = mSpriteName.c_str();

    mTextRect.left = mTextRect.width * Utils::GetInfoFromArray<int>(njson, charArray, "x");
    mTextRect.top = mTextRect.height * Utils::GetInfoFromArray<int>(njson, charArray, "y");

    mRenderSprite->setTextureRect(mTextRect); // Changer la zone affichée
    mRenderSprite->setOrigin(mTextRect.width / 2, mTextRect.height / 2);
    mRenderSprite->setScale(mRenderRatio);
}

void TextureRender::SetSpriteRect(const sf::IntRect& rect)
{
    SetTextureRect(rect);
    mRenderSprite->setTextureRect(mTextRect); // Changer la zone affichée
    mRenderSprite->setOrigin(mTextRect.width / 2, mTextRect.height / 2);
    mRenderSprite->setScale(mRenderRatio);
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

