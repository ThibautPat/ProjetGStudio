#include "SampleScene.h"

#include "DummyEntity.h"

#include <iostream>
#include "Debug.h"
sf::View view(sf::FloatRect(0, 0, 1280, 720));
void SampleScene::OnInitialize()
{
	mPlayer = CreateEntity<Player>(25,sf::Color::Cyan);
	
}

void SampleScene::OnEvent(const sf::Event& event)
{

}


void SampleScene::OnUpdate()
{
	playerJumpTime += GetDeltaTime();
	bool isJumping = mPlayer->Jump(GetDeltaTime(), playerJumpTime);
	if (isJumping == true)
	{
		playerJumpTime = 0;
	}
	sf::Vector2f movement = mPlayer->Movement();
	if (movement.x != 0 || movement.y != 0)
	{
		playerRunTime += GetDeltaTime();
	}
	else
	{
		playerRunTime = 0;
	}
	mPlayer->Move(movement, GetDeltaTime(), playerRunTime);
	view.setCenter(mPlayer->GetPosition().x, mPlayer->GetPosition().y);
	mpGameManager->GetWindow()->setView(view);
}
