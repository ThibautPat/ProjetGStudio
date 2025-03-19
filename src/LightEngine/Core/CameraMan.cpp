#include "CameraMan.h"
#include "GameManager.h"
#include "Utils.h"

void CameraMan::SetView(sf::View* view)
{
	mView = view;
	mOriginalSize = mView->getSize();
}

void CameraMan::Update()
{
	sf::Vector2f position = mView->getCenter();

	if (mDest == position)
		return;
	
	sf::Vector2f movement = mDest - position;
	float distance = Utils::GetDistance(position.x, position.y, mDest.x, mDest.y);

	float dt = GameManager::Get()->GetDeltaTime();
	movement *= dt* mFollowSpeed;

	mView->setCenter(position.x + movement.x, position.y + movement.y);
}

void CameraMan::Zoom(float offsetx, float offsety)
{
	sf::Vector2f zoom = sf::Vector2f(mView->getSize().x * offsetx, mView->getSize().y * offsety);
	mView->setSize(zoom);
}

void CameraMan::SetZoom(float offsetx, float offsety)
{
	sf::Vector2f zoom = sf::Vector2f(mOriginalSize.x * offsetx, mOriginalSize.y * offsety);
	mView->setSize(zoom);
}

void CameraMan::GoTo(sf::Vector2f& dest)
{
	mDest = dest; 

	sf::Vector2f position = mView->getCenter();

	if (mDest == position)
		return;

	sf::Vector2f movement = mDest - position;
	float distance = Utils::GetDistance(position.x, position.y, mDest.x, mDest.y);

	mFollowSpeed = distance/10 * mCamSpeed;
}
