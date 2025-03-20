#include "Checkpoint.h"
#include "../GameScene/TestScene.h"

void Checkpoint::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);

	SetTag(TestScene::Tag::CHECKPOINT);
	SetRigidBody(false);
	SetIsKinematic(true);
	SetGravity(false);
}

void Checkpoint::OnUpdate()
{
}
