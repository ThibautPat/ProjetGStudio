#include "Checkpoint.h"
#include "../GameScene/TestScene.h"
#include "../GameEntity/Player.h"

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
	//Attendre la spritesheet et json
	/*
	if (mIsActivated)
		return;

	Player* p = GameManager::Get()->GetEntity<Player>(TestScene::Tag::PLAYER);
	if (IsColliding((Entity*)p) == false)
		return;

	sf::IntRect checkpointon = sf::IntRect(
		mTextureRender->GetTextureRect().left + mTextureRender->GetTextureRect().width, 
		mTextureRender->GetTextureRect().top, 
		mTextureRender->GetTextureRect().width, 
		mTextureRender->GetTextureRect().height
	);
	mTextureRender->SetSpriteRect(checkpointon);
	p->GetPlayerData()->mLastCheckPoint = GetPosition(0.f, 0.f);
	mIsActivated = true;
	*/
}
