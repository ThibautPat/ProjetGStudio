#pragma once
#include "../Entity/RectangleEntity.h"
class LaserEntity : public RectangleEntity
{
protected:
	//bool mIsActive = true;
	//bool mAlreadyUsed = false;
	//int mNb = 0.f;

	//std::vector<LaserEntity*>* mLaser;

public:

	//void SetTabLaser(std::vector<LaserEntity*>* tablaser) { mLaser = tablaser; }
	//void SetNumber(int nb) { mNb = nb; }
	//void SetIsActive(bool active = true) { mIsActive = active; }
	//void AddToTab(LaserEntity* laser) { mLaser->push_back(laser); }

	void OnInitialize() override;
};

