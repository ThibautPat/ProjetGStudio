#include "../../Core/Entity/CircleEntity.h"
#include "../../Core/Collider/CircleCollider.h"

Collider* CircleEntity::GetCollider()
{
    return mCollider;
}

sf::Shape* CircleEntity::GetShape()
{
    return &mShape;
}

void CircleEntity::Initialize(float radius, const sf::Color& color) {
	mCollider = new CircleCollider(0.f, 0.f, radius);

	mSizeX = radius;
	mSizeY = radius;

	mDirection = sf::Vector2f(0.f, 0.f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setRadius(radius);
	mShape.setFillColor(color);

	mTarget.isSet = false;

	OnInitialize();
}

void CircleEntity::Repulse(Entity* other)
{
	CircleEntity* otherCircle = dynamic_cast<CircleEntity*>(other); //TODO à changer si possible (faire sans dynamic_cast)

	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);

	float radius1 = mShape.getRadius();
	float radius2 = otherCircle->mShape.getRadius();

	float overlap = (length - (radius1 + radius2)) * 0.5f;

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = overlap * normal;

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	SetPosition(position1.x, position1.y, 0.5f, 0.5f);
	other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
}

bool CircleEntity::IsColliding(Entity* other) {
	return mCollider->IsColliding(other->GetCollider());
}

bool CircleEntity::IsInside(float x, float y)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mShape.getRadius();

	return (dx * dx + dy * dy) < (radius * radius);
}

void CircleEntity::Update() {
	mCollider->Update(GetPosition(0.f, 0.f).x, GetPosition(0.f, 0.f).y);

	Entity::Update();
}

void CircleEntity::OnUpdate()
{
}

void CircleEntity::OnCollision(Entity* collidedWith)
{
}

void CircleEntity::OnInitialize()
{
}

void CircleEntity::OnDestroy()
{
}
