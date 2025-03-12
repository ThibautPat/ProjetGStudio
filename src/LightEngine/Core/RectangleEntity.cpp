#include "RectangleEntity.h"
#include "AABBCollider.h"
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

void RectangleEntity::Initialize(float height, float Width, const sf::Color& color)
{
	mCollider = new AABBCollider(0.f, 0.f, height, Width);

	mSizeX = Width / 2;
	mSizeY = height / 2;

	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setSize(sf::Vector2f(Width, height));
	mShape.setFillColor(color);

	mTarget.isSet = false;

	OnInitialize();
}

void RectangleEntity::Repulse(Entity* other)
{
	//Tests collisions

	//float width1 = mShape.getGlobalBounds().width;
	//float width2 = other->GetShape()->getGlobalBounds().width;

	//float height1 = mShape.getGlobalBounds().height;
	//float height2 = other->GetShape()->getGlobalBounds().height;

	//sf::Vector2f position1 = GetPosition(0.f, 0.f);
	//sf::Vector2f position2 = sf::Vector2f(other->GetPosition(1.f, 1.f).x - height1 - height2 * 0.5f - 1, other->GetPosition(1.f, 1.f).y - width1 - width2 * 0.5f - 1);

	//SetPosition(position1.x, position2.y);

	//if (other->IsKinematic()) {
	//	sf::Vector2f position2 = other->GetPosition(0.f, 0.f);
	//	other->SetPosition(position2.x, position2.y);
	//}


	/*
	sf::Vector2f coOther = other->GetPosition(0.f, 0.f);
	sf::Vector2f co = GetPosition(0.f, 0.f);

	float width1 = mShape.getGlobalBounds().width/2;
	float width2 = other->GetShape()->getGlobalBounds().width/2;
	float width = width1 + width2;
	float height1 = mShape.getGlobalBounds().height/2;
	float height2 = other->GetShape()->getGlobalBounds().height/2;
	float height = height1 + height2;


	float diffx = 0;
	if(co.x < coOther.x)
		diffx = coOther.x - co.x;
	else
		diffx = co.x - coOther.x;
	float diffy = 0;
	if (co.y < coOther.y)
		diffy = coOther.y - co.y;
	else
		diffx = co.y - coOther.y;

	float penetrationx = width - diffx;
	float penetrationy = height - diffy;

	//Collision on y axe
	if (penetrationx > penetrationy) {
		std::cout << "penetration on y : " << penetrationx << " " << penetrationy << std::endl;
		if (co.y < coOther.y)
			SetPosition(co.y - penetrationx - 5, co.y);
		//else
		//	SetPosition(co.y + penetrationx + 5, co.y);
	}
	//Collision on x axe
	if (penetrationx < penetrationy) {
		if (co.x < coOther.x)
			SetPosition(co.x - penetrationx - 5, co.y);
		else
			SetPosition(co.x + penetrationx + 5, co.y);
		std::cout << "penetration on x : " << penetrationx << " " << penetrationy << std::endl;
	}
	*/



	sf::Vector2f distance = GetPosition(0.f, 0.f) - other->GetPosition(0.f, 0.f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);

	float width1 = mShape.getGlobalBounds().width;
	float width2 = other->GetShape()->getGlobalBounds().width;

	float overlap = (length - (width1 + width2)) * 0.5f;

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = overlap * normal;

	translation *= 0.05f;

	sf::Vector2f position1 = GetPosition(0.f, 0.f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.f, 0.f) + translation;

	SetPosition(position1.x, position1.y);
	mSpeed = 0;
	mDirection.x = 0;
	if (other->IsKinematic())
		return;
	other->SetPosition(position2.x, position2.y);
}

void RectangleEntity::Update()
{
    mCollider->Update(GetPosition(0.f, 0.f).x - mCollider->mWidth / 2.f, GetPosition(0.f, 0.f).y - mCollider->mHeight / 2.f);

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
