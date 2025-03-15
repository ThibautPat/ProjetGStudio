#include "PlayerCondition.h"
#include "TestScene.h"
#include "../Core/AABBCollider.h"

bool PlayerCondition_IsJumping::OnTest(Player* owner)
{
	if (owner->GetGravity() && owner->secondjump <= 0)
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
	if (owner->secondjump > 0)
	{
		return true;
	}
	return false;
}

bool PlayerCondition_IsGrounded::OnTest(Player* owner)
{
	for (Entity* entity : GameManager::Get()->GetEntities<Entity>())
	{
		if (owner->IsColliding(entity) && owner != entity && static_cast<AABBCollider*>(owner->GetCollider())->GetCollideFace()->y == 1)
		{
			return true;
		}
		else if (owner->IsColliding(entity) && owner != entity && static_cast<AABBCollider*>(owner->GetCollider())->GetCollideFace()->y == -1 && entity->IsTag(TestScene::Tag::METALIC_OBSTACLE))
		{
			return true;
		}
	}
	return false;
}

bool PlayerCondition_IsDashing::OnTest(Player* owner)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Joystick::isButtonPressed(0, 2))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || std::abs(sf::Joystick::getAxisPosition(0, sf::Joystick::X)) > 10)
		{
			return true;
		}
	}
	return false;
}

bool PlayerCondition_HasDash::OnTest(Player* owner)
{
	if (owner->mPData->pDashDuration < owner->mPData->mDashTime)
	{
		return true;
	}
	return false;
}

bool PlayerCondition_DashOnCoolDown::OnTest(Player* owner)
{
	if (owner->mPData->mDashCooldownDuration > owner->mPData->pDashCooldown) 
	{
		
		return true;
	}
	return false;
}
