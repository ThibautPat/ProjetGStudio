#include "DeadlyObstacle.h"
#include "../GameScene/TestScene.h"

void DeadlyObstacle::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);

	SetTag(TestScene::Tag::DEADLYOBSTACLE);
	SetRigidBody(false);
	SetIsKinematic(true);
	SetGravity(false);
}

void DeadlyObstacle::OnUpdate()
{
}
