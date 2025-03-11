#include "SampleScene.h"

#include "DummyEntity.h"

#include <iostream>
#include "Debug.h"

void SampleScene::OnInitialize()
{
	mPlayer = CreateEntity<Player>(100,sf::Color::Cyan);
	mPlayer->pJumpTime = 2;
}

void SampleScene::OnEvent(const sf::Event& event)
{
}

void SampleScene::OnUpdate()
{ 
	mPlayer->Jump(GetDeltaTime());

	sf::Vector2f movement = mPlayer->InputDirection();

	mPlayer->Move(movement, GetDeltaTime());
}
