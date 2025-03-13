#include "RectangleEntity.h"
#include "AABBCollider.h"
#include "Debug.h"
#include <iostream>

Collider* RectangleEntity::GetCollider()
{
    return mCollider;
}

sf::Shape* RectangleEntity::GetShape()
{
    return &mShape;
}

bool RectangleEntity::IsColliding(Entity* other)
{
    return mCollider->IsColliding(other->GetCollider());
}

bool RectangleEntity::IsInside(float x, float y)
{
    return mShape.getGlobalBounds().contains(sf::Vector2f(x, y));
}

void RectangleEntity::Initialize(float height, float width, const sf::Color& color)
{
	mCollider = new AABBCollider(0.f, 0.f, width, height);

	mSizeX = width / 2;
	mSizeY = height / 2;

	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setSize(sf::Vector2f(width, height));
	mShape.setFillColor(color);

	mTarget.isSet = false;

	OnInitialize();
}

void RectangleEntity::Repulse(Entity* other)
{
    if (IsKinematic())
    {
        SetPosition(GetPosition(0.f, 0.f).x, GetPosition(0.f, 0.f).y);
        return;
    }
    if (other->IsKinematic())
    {
        other->SetPosition(other->GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y);
    }
    sf::Vector2f distance = GetPosition(0.f, 0.f) - other->GetPosition(0.f, 0.f);

    float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
    float length = std::sqrt(sqrLength);

    int width1 = mShape.getGlobalBounds().width;
    int width2 = other->GetShape()->getGlobalBounds().width;

    float overlap = (length - (width1 + width2)) * 0.5f;

    sf::Vector2f normal = distance / length;

    sf::Vector2f translation = overlap * normal;

    sf::Vector2f position1 = GetPosition(0.f, 0.f) - translation;
    sf::Vector2f position2 = other->GetPosition(0.f, 0.f) + translation;

    // V�rifier si le joueur se d�place vers l'autre objet
    std::string debug = "mDirection.x: " + std::to_string(mMove.x) + ", normal.x: " + std::to_string(normal.x) + ", mSpeed: " + std::to_string(mSpeed);
    Debug::DrawText(GetPosition(0.f, 0.f).x, GetPosition(0.f, 0.f).y + 100, debug, sf::Color::Cyan);

        int place;

        if (mCollider->GetCollideFace()->x != 0)
        {
            if (mCollider->GetCollideFace()->x > 0)
                place = 1;
            else
                place = -1;
            if ((mMove.x <= 0) || (mMove.x >= 0))
            {
                SetPosition(other->GetPosition(0.f, 0.f).x - place * width2 * 0.5f - place * width1 * 0.5f, GetPosition(0.f, 0.f).y);
                // Le joueur se d�place vers l'autre objet, donc on l'arr�te
                mSpeed = 0.f;
            }
        }
        else 
        {
            if (mCollider->GetCollideFace()->y > 0)
            {
                place = 1;
                mGravitySpeed = 0.f;
				mBoolGravity = false;
            }
            else
            {
				mGravitySpeed = 0.f;
                place = -1;
            }
            if ((mMove.y <= 0) || (mMove.y >= 0))
            {
				SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * width2 * 0.5f - place * width1 * 0.5f);
                // Le joueur se d�place vers l'autre objet, donc on l'arr�te
                hasCollidingLastFrame = true;
            }
        }
		
}

void RectangleEntity::Update()
{
    mCollider->Update(GetPosition(0.f, 0.f).x - mCollider->mWidth / 2.f, GetPosition(0.f, 0.f).y - mCollider->mHeight / 2.f);

	//#TODO : � revoir pour �viter de perdre les comportement des classes h�rit�es ?
    Entity::Update();
}

void RectangleEntity::OnUpdate()
{
}

void RectangleEntity::OnCollision(Entity* collidedWith)
{
}

void RectangleEntity::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width/2,mShape.getGlobalBounds().height/2);
}

void RectangleEntity::OnDestroy()
{
}
