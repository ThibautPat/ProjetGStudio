#include "RectangleEntity.h"
#include "AABBCollider.h"

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

void RectangleEntity::Initialize(float height, float weight, const sf::Color& color)
{
	mCollider = new AABBCollider(0.f, 0.f, height, weight);

	mSizeX = weight / 2;
	mSizeY = height / 2;

	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setSize(sf::Vector2f(weight, height));
	mShape.setFillColor(color);

	mTarget.isSet = false;

	OnInitialize();
}

void RectangleEntity::Repulse(Entity* other)
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);

	float radius1 = mShape.getGlobalBounds().width;
	float radius2 = other->GetShape()->getGlobalBounds().width;

	float overlap = (length - (radius1 + radius2)) * 0.5f;

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = overlap * normal;

	translation *= 0.05f;

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	SetPosition(position1.x, position1.y, 1.f, 1.f);
	other->SetPosition(position2.x, position2.y, 1.f, 1.f);
}

void RectangleEntity::Update()
{
    mCollider->Update(GetPosition(1.f, 1.f).x - mCollider->mWeight / 2.f, GetPosition(1.f, 1.f).y - mCollider->mHeight / 2.f);

    Entity::Update();
}
