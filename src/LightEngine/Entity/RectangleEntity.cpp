#include "RectangleEntity.h"
#include "../Collider/AABBCollider.h"
#include "../Other/Debug.h"
#include <iostream>
#include "../GameScene/TestScene.h"

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
    if (*mCollider->GetCollideFace() == sf::Vector2f(0.f, 0.f)) {
        return;
    }

    // Calcul des positions, distances et normalisation
    sf::Vector2f distance = GetPosition(0.f, 0.f) - other->GetPosition(0.f, 0.f);
    float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
    float length = std::sqrt(sqrLength);

    int entityWidth = mShape.getGlobalBounds().width;
    int otherWidth = other->GetShape()->getGlobalBounds().width;
    int entityHeight = mShape.getGlobalBounds().height;
    int otherHeight = other->GetShape()->getGlobalBounds().height;

    float overlap = (length - (entityWidth + otherWidth)) * 0.5f;
    sf::Vector2f normal = distance / length;
    sf::Vector2f translation = overlap * normal;

    sf::Vector2f position1 = GetPosition(0.f, 0.f) - translation * 0.01f;
    sf::Vector2f position2 = other->GetPosition(0.f, 0.f) + translation * 0.12f;

    //if (mCollider->GetCollideFace()->x != 0)
    //{
    //    // Collision horizontale
    //    SetPosition(position1.x, GetPosition(0.f, 0.f).y);
    //    other->SetPosition(position2.x, other->GetPosition(0.f, 0.f).y);
    //    mSpeed = 0.f;
    //}

    Block(other);
}

void RectangleEntity::Block(Entity* other)
{
    if (*mCollider->GetCollideFace() == sf::Vector2f(0.f, 0.f)) {
        return;
    }

    // Récupération des dimensions avec des noms plus parlants
    int entityWidth = mShape.getGlobalBounds().width;
    int otherWidth = other->GetShape()->getGlobalBounds().width;
    int entityHeight = mShape.getGlobalBounds().height;
    int otherHeight = other->GetShape()->getGlobalBounds().height;

    int place = 0;
    if (mCollider->GetCollideFace()->x != 0)
    {
        // Collision horizontale : on utilise les largeurs
        place = (mCollider->GetCollideFace()->x > 0) ? 1 : -1;
        SetPosition(other->GetPosition(0.f, 0.f).x - place * (otherWidth * 0.5f + entityWidth * 0.5f), GetPosition(0.f, 0.f).y);
        mSpeed = 0.f;
    }
	else
	{
		// Collision verticale : on utilise les hauteurs
        place = (mCollider->GetCollideFace()->y > 0) ? 1 : -1;

		if (mCollider->GetCollideFace()->y == 1 && !other->IsTag(TestScene::Tag::BOUCING_OBSTACLE))
		{
           
                SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f) - 0.5f);
                mGravitySpeed = 0.f;
                mBoolGravity = false;
		}
        else if (other->IsTag(TestScene::Tag::BOUCING_OBSTACLE))
        {
            mBoolGravity = true;
            mGravitySpeed = -600;
            
            SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f) + 1 - 10);
        }
		else 
        {
			mBoolGravity = true;
			mGravitySpeed = 0.f;
            SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f) + 1 - int(mReverse));
        }

		hasCollidedLastFrame = true;
	}
}

void RectangleEntity::Update()
{
    mCollider->Update(GetPosition(0.f, 0.f).x - mCollider->mWidth / 2.f, GetPosition(0.f, 0.f).y - mCollider->mHeight / 2.f);
    //Debug::DrawRectangle(GetPosition(-1.f, -1.f).x, GetPosition(-1.f, -1.f).y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height, sf::Color::Cyan);
    Entity::Update();
}

void RectangleEntity::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width/2,mShape.getGlobalBounds().height/2);
}
