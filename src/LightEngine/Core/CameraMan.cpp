#include "CameraMan.h"
#include "GameManager.h"
#include "Utils.h"

void CameraMan::Update(sf::View* view)
{
	/*
	float dt = GameManager::Get()->GetDeltaTime();
	float distance = dt * 50;
	sf::Vector2f translation = distance * mDirection;

	sf::Vector2f position = view->getCenter();
	
	float x1 = position.x;
	float y1 = position.y;

	float distance = Utils::GetDistance(position.x, position.y, mDest.x, mDest.y);

	float x2 = x1 + mDest.x * distance2;
	float y2 = y1 + mDest.y * distance2;

	//mTarget.distance -= distance;

	if (distance <= 0.f)
	{
		view->setCenter(mTarget.position.x, mTarget.position.y, 1.f, 1.f);
		mDirection = sf::Vector2f(0.f, 0.f);
		mTarget.isSet = false;
	}
	*/
}

void CameraMan::Zoom(sf::View* view, float offsetx, float offsety)
{
	sf::Vector2f zoom = sf::Vector2f(view->getSize().x * offsetx, view->getSize().y * offsety);
	view->setSize(zoom);
}
