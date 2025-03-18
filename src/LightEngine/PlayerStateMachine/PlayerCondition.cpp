//#include "PlayerCondition.h"
//#include "../GameScene/TestScene.h"
//#include "../Collider/AABBCollider.h"
//
//bool PlayerCondition_IsJumping::OnTest(Player* owner)
//{
//	owner->SetmPData->isGrounded(false);
//	if (owner->GetGravity())
//		return false;
//	if (owner->mPData->pJumpDuration < owner->mPData->mJumpTime) 
//		return false;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0))
//	{
//		owner->SetmPData->isGrounded(true);
//		return true;
//	}
//	return false;
//}
//
//bool PlayerCondition_IsCrouching::OnTest(Player* owner)
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 1))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool PlayerCondition_IsWalking::OnTest(Player* owner)
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || std::abs(sf::Joystick::getAxisPosition(0, sf::Joystick::X)) > 10)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool PlayerCondition_HasJump::OnTest(Player* owner)
//{
//	if (owner->GetSecondJump() > 0)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool PlayerCondition_mPData->isGrounded::OnTest(Player* owner)
//{
//	for (Entity* entity : GameManager::Get()->GetEntities<Entity>())
//	{
//		if (entity->IsColliding(owner))
//		{
//			if (entity->IsTag(TestScene::Tag::METALIC_OBSTACLE))
//			{
//				std::cout << "Grounded by metalic object" << std::endl;
//				return true;
//			}
//			else if (entity->IsTag(TestScene::Tag::PLATFORM) && static_cast<AABBCollider*>(owner->GetCollider())->GetCollideFace()->y == 1)
//			{
//				std::cout << "Grounded by obstacle" << std::endl;
//				return true;
//			}
//		}
//	}
//	std::cout << "Not Grounded" << std::endl;
//	return false;
//}
//
//bool PlayerCondition_GravityPlus::OnTest(Player* owner)
//{
//	if (owner->GetGravitySpeed() >= 0)
//	{
//		return true;
//	}
//	return false;
//}
