#include "RectangleEntity.h"
#include "AABBCollider.h"
#include "Debug.h"
#include <iostream>
#include "../Game/TestScene.h"

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

    // Calcul des positions, distances et normalisation
    sf::Vector2f distance = GetPosition(0.f, 0.f) - other->GetPosition(0.f, 0.f);
    float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
    float length = std::sqrt(sqrLength);

    // Récupération des dimensions avec des noms plus parlants
    int entityWidth = mShape.getGlobalBounds().width;
    int otherWidth = other->GetShape()->getGlobalBounds().width;
    int entityHeight = mShape.getGlobalBounds().height;
    int otherHeight = other->GetShape()->getGlobalBounds().height;

    float overlap = (length - (entityWidth + otherWidth)) * 0.5f;
    sf::Vector2f normal = distance / length;
    sf::Vector2f translation = overlap * normal;

    sf::Vector2f position1 = GetPosition(0.f, 0.f) - translation;
    sf::Vector2f position2 = other->GetPosition(0.f, 0.f) + translation;

    int place = 0;
    if (mCollider->GetCollideFace()->x != 0)
    {
        // Collision horizontale : on utilise les largeurs
        place = (mCollider->GetCollideFace()->x > 0) ? 1 : -1;
        if ((mMove.x <= 0) || (mMove.x >= 0))
        {
            SetPosition(other->GetPosition(0.f, 0.f).x - place * (otherWidth * 0.5f + entityWidth * 0.5f), GetPosition(0.f, 0.f).y);
            mSpeed = 0.f;
        }
    }
    else
    {
        
        // Collision verticale : on utilise les hauteurs

        int gap = 0;
        if (mCollider->GetCollideFace()->y == 1)
        {
            place = 1;
            mGravitySpeed = 0.f;
            mBoolGravity = false;
            secondjump = 2;
            gap = 5;
        }
        else if (mCollider->GetCollideFace()->y == -1 && !other->IsTag(TestScene::Tag::METALIC_OBSTACLE))
        {
            mBoolGravity = true;
            mGravitySpeed = 0.f;
            place = -1;
            gap = -5;
        }
		else 
		{
            secondjump = 2; 
            mBoolGravity = false;
            mGravitySpeed = 0.f;
            place = -1;
            gap = -5;
		}
        if ((mMove.y <= 0) || (mMove.y >= 0))
        {
            if (mCollider->GetCollideFace()->y == -1 && !other->IsTag(TestScene::Tag::METALIC_OBSTACLE))
            {
                SetGravity(true);
                SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f)+1);
			}
            else if (mCollider->GetCollideFace()->y == 1 && Clockjump.getElapsedTime().asSeconds() > 0.3f && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)))
            {
				Clockjump.restart(); 
                mGravitySpeed = -600.f;
                SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f) - gap);
            }
            else if (Clockjump.getElapsedTime().asSeconds() > 0.3f && mCollider->GetCollideFace()->y == -1 && other->IsTag(TestScene::Tag::METALIC_OBSTACLE) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)))
            {
				mReverse = true;
				Clockjump.restart(); 

                mGravitySpeed = 600.f;
                SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f) - gap);
            }
            else
            {
                SetPosition(GetPosition(0.f, 0.f).x, other->GetPosition(0.f, 0.f).y - place * (otherHeight * 0.5f + entityHeight * 0.5f));
            }
            // Le joueur se d�place vers l'autre objet, donc on l'arr�te
            hasCollidingLastFrame = true;

        }

    }
}


void RectangleEntity::Update()
{
    mCollider->Update(GetPosition(0.f, 0.f).x - mCollider->mWidth / 2.f, GetPosition(0.f, 0.f).y - mCollider->mHeight / 2.f);
    Debug::DrawRectangle(GetPosition(-1.f, -1.f).x, GetPosition(-1.f, -1.f).y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height, sf::Color::Cyan);
	//#TODO : � revoir pour �viter de perdre les comportement des classes h�rit�es ?
    Entity::Update();
}

void RectangleEntity::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width/2,mShape.getGlobalBounds().height/2);
}
