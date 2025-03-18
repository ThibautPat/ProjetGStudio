#include "../GameEntity/LaserEntity.h"
#include "../GameEntity/Player.h"
#include "../GameScene/Scene.h"

#include <iostream>

void LaserEntity::OnInitialize()
{
	RectangleEntity::OnInitialize();

	mRigidBody = false;
	mKinematic = true;
	mBoolGravity = false;
	SetTag(Scene::Tag::LASER);


}
