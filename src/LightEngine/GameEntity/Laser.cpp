#include "../GameEntity/Laser.h"
#include "../Manager/GameManager.h"
#include "../GameEntity/Player.h"

void Laser::Initialize(float x, float y, const sf::Color& color)
{
	mStart.x = x;
	mStart.y = y;
}

void Laser::OnInitialize()
{
	mSizeY = 10;
	mSizeY = 0;

	mRigidBody = false;
	mKinematic = true;
	mBoolGravity = false;
	SetTag(Scene::Tag::LASER);
}


//------------------------------

Laser::Laser(int nb, sf::Vector2f& dir, sf::IntRect& laser, const sf::Color& color)
{
	mNb = nb;
	mLaserDir = dir;

	int sizex = laser.width;
	int sizey = laser.height;

	LaserEntity* nlaser = GameManager::Get()->GetSceneManager()->GetScene()->CreateRectEntity<LaserEntity>(sizey, sizex, color);

	sf::Vector2f pos = sf::Vector2f(laser.left, laser.top);

	sf::Vector2f npos = sf::Vector2f(pos.x + sizex * dir.x, pos.y + sizey * dir.y);

	nlaser->SetDirection(dir.x, dir.y);
	nlaser->SetPosition(npos.x, npos.y);

	mLaser.push_back(nlaser);
}

void Laser::Update()
{
	for (int i = 0; i < mLaser.size(); i++) {
		mLaser[i]->RectangleEntity::Update();
	}

	if (mNb > 0) {
		AddLaser();
		mNb--;
	}
}

void Laser::AddLaser()
{
	int sizex = mLaser[mLaser.size()-1]->GetSizeX();
	int sizey = mLaser[mLaser.size()-1]->GetSizeY();

	sf::Color color = mLaser[mLaser.size()-1]->GetShape()->getFillColor();

	LaserEntity* laser = GameManager::Get()->GetSceneManager()->GetScene()->CreateRectEntity<LaserEntity>(sizey * 2, sizex * 2, color);

	sf::Vector2f pos = mLaser[mLaser.size()-1]->GetPosition(0.f, 0.f);
	sf::Vector2f dir = mLaser[mLaser.size()-1]->GetDirection();

	sf::Vector2f npos = sf::Vector2f(pos.x + sizex * dir.x, pos.y + sizey * dir.y);

	laser->SetDirection(dir.x, dir.y);
	laser->SetPosition(npos.x, npos.y);

	mLaser.push_back(laser);
}

bool Laser::IsCollidingWithLaser(Entity* other)
{
	for (int i = 0; i < mLaser.size(); i++) {

		if (mLaser[i]->IsColliding(other))
			return true;
	}

	return false;
}
