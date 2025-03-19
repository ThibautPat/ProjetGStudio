#include "PlayerCondition.h"
#include "../GameScene/TestScene.h"
#include "../Collider/AABBCollider.h"

bool PlayerCondition_IsJumping::OnTest(Player* owner)
{
	if (owner->GetGravity() && owner->secondJump <= 0)
		return false;
	if (owner->mPData->pJumpDuration < owner->mPData->mJumpTime) 
		return false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
	{
		return true;
	}
	return false;
}

bool PlayerCondition_IsCrouching::OnTest(Player* owner)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
	{
		return true;
	}
	return false;
}

bool PlayerCondition_IsWalking::OnTest(Player* owner)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || std::abs(sf::Joystick::getAxisPosition(0, sf::Joystick::X)) > 10)
	{
		return true;
	}
	return false;
}

bool PlayerCondition_HasJump::OnTest(Player* owner)
{
	if (owner->secondJump > 0)
	{
		return true;
	}
	return false;
}

bool PlayerCondition_IsGrounded::OnTest(Player* owner)
{
	for (Entity* entity : GameManager::Get()->GetEntities<Entity>())
	{
		if (entity->IsColliding(owner))
		{
			if (entity->IsTag(TestScene::Tag::METALIC_OBSTACLE))
			{
				return true;
			}
			else if (entity->IsTag(TestScene::Tag::OBSTACLE) && static_cast<AABBCollider*>(owner->GetCollider())->GetCollideFace()->y == 1)

			{
				return true;
			}
		}
	}
	owner->mReverse = false;
	return false;
}

bool PlayerCondition_GravityPlus::OnTest(Player* owner)
{
	if (owner->GetGravitySpeed() > 30)
	{
		return true;
	}
	return false;
}