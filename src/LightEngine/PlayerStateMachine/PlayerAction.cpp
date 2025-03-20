#pragma once
#include "PlayerAction.h"
#include "../GameEntity/Player.h"
#include "../Renderer/AnimationRender.h"

void PlayerAction_Idle::OnStart(Player* pOwner)
{
	std::cout << "IDLE" << std::endl;
	std::string AnimName = "idle";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}
void PlayerAction_Idle::OnUpdate(Player* pOwner)
{
	float decelerationAmount = pOwner->mPData->mDeceleration * 50 * FIXED_DT;

	if (std::abs(pOwner->GetSpeed()) > 100)	// Decelerer ou accelerer vers z�ro en fonction de la vitesse
	{
		float spd = pOwner->GetSpeed();
		spd += (pOwner->GetSpeed() > 0 ? -1 : 1) * decelerationAmount;
		pOwner->SetSpeed(spd);
	}
	if (std::abs(pOwner->GetSpeed()) < 500)	// Si la vitesse est proche de 0, on la reinitialise
	{
		pOwner->SetSpeed(0);
	}
}

void PlayerAction_Jump::OnStart(Player* pOwner)
{
	std::cout << "JUMP" << std::endl;
	std::string AnimName = "jump";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);

	if (pOwner->mReverse) 
	{
		pOwner->mReverse = false;
		pOwner->SetPosition(pOwner->GetPosition(0.f, 0.f).x, pOwner->GetPosition(0.f, 0.f).y + 1);
	}
	else
	{
		pOwner->SetPosition(pOwner->GetPosition(0.f, 0.f).x, pOwner->GetPosition(0.f, 0.f).y - 1);
	}

	// Initialisation du saut si le joueur est au sol
	if (pOwner->mPData->isGrounded) {
		pOwner->mPData->pJumpDuration = 0;
		pOwner->SetGravitySpeed(-pOwner->mPData->mJumpHeight);
		pOwner->mPData->isGrounded = false;
	}
}

void PlayerAction_Jump::OnUpdate(Player* pOwner)
{
	// Si le joueur a terminé le saut, la gravité doit prendre le relais
	if (pOwner->mPData->pJumpDuration > pOwner->mPData->mJumpTime) {
		if (pOwner->mReverse) 
		{
			pOwner->SetGravitySpeed(-pOwner->mPData->mJumpHeight / 2);
		}
		else
		{
			pOwner->SetGravitySpeed(pOwner->mPData->mJumpHeight / 2);
		}
		pOwner->SetGravity(true);
	}
}

void PlayerAction_Crouch::OnStart(Player* pOwner)
{
	std::cout << "CROUCH" << std::endl;
	std::string AnimName = "StartCrouch";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}
void PlayerAction_Crouch::OnUpdate(Player* pOwner)
{
	if (pOwner->mAnimator->GetCurrentAnimation()->GetIsFinished()) {
		std::string AnimName = "OnCrouch";
		pOwner->mAnimator->SetCurrentAnimation(AnimName);
	}

	float dt = FIXED_DT;
	float spd = pOwner->GetSpeed();
	sf::Vector2f movement = pOwner->GetPlayerData()->mDirection;
	if (movement.x == 1)
	{
		if (pOwner->GetSpeed() > -pOwner->mPData->mMaxSpeedWalk)
		{
			spd += pOwner->mPData->mMaxSpeedWalk * dt;
			pOwner->SetSpeed(spd);
		}
		if (pOwner->GetSpeed() > pOwner->mPData->mMaxSpeedCrouch)
		{
			spd -= pOwner->mPData->mMaxSpeedWalk * dt * 2;
			pOwner->SetSpeed(spd);
		}
		if (pOwner->GetSpeed() < 11000 && pOwner->GetSpeed() > 9000)
		{
			spd = pOwner->mPData->mMaxSpeedCrouch;
			pOwner->SetSpeed(spd);
		}
	}
	else if (movement.x == -1)
	{
		if (pOwner->GetSpeed() < pOwner->mPData->mMaxSpeedWalk)
		{
			spd -= pOwner->mPData->mMaxSpeedWalk * dt;
			pOwner->SetSpeed(spd);
		}
		if (pOwner->GetSpeed() < -pOwner->mPData->mMaxSpeedCrouch)
		{
			spd += pOwner->mPData->mMaxSpeedWalk * dt * 2;
			pOwner->SetSpeed(spd);
		}
		if (pOwner->GetSpeed() > -11000 && pOwner->GetSpeed() < -9000)
		{
			spd = -pOwner->mPData->mMaxSpeedCrouch;
			pOwner->SetSpeed(spd);
		}
	}
	else {
		float decelerationAmount = pOwner->mPData->mDeceleration * 50 * FIXED_DT;

		if (std::abs(pOwner->GetSpeed()) > 100)	// Decelerer ou accelerer vers z�ro en fonction de la vitesse
		{
			float spd = pOwner->GetSpeed();
			spd += (pOwner->GetSpeed() > 0 ? -1 : 1) * decelerationAmount;
			pOwner->SetSpeed(spd);
		}
		if (std::abs(pOwner->GetSpeed()) < 500)	// Si la vitesse est proche de 0, on la reinitialise
		{
			pOwner->SetSpeed(0);
		}
	}
}

void PlayerAction_Walk::OnStart(Player* pOwner)
{
	std::cout << "WALK" << std::endl;
	std::string AnimName = "walk";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}
void PlayerAction_Walk::OnUpdate(Player* pOwner)
{
	sf::Vector2f movement = pOwner->GetPlayerData()->mDirection;

	float speed = pOwner->GetSpeed();
	speed += movement.x * 50 * FIXED_DT * pOwner->mPData->mAcceleration;
	pOwner->SetSpeed(speed);
	if (movement.x != 0) // Mise � jour de mLastMovement si movement.x n'est pas nul
	{
		pOwner->mLastMovement = movement;
	}
	if ((pOwner->mLastMovement.x == -1 && pOwner->GetSpeed() > 0) || (pOwner->mLastMovement.x == 1 && pOwner->GetSpeed() < 0)) // Gestion de la d�c�l�ration si la direction du mouvement change
	{
		float spd = pOwner->GetSpeed();
		spd += (pOwner->mLastMovement.x == -1 ? -1 : 1) * pOwner->mPData->mDeceleration * 50 * FIXED_DT;
		pOwner->SetSpeed(spd);
	}
}

void PlayerAction_Fall::OnStart(Player* pOwner)
{
	std::cout << "FALL" << std::endl; 
	std::string AnimName = "fall";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}

void PlayerAction_Fall::OnUpdate(Player* pOwner)
{
	float decelerationAmount = pOwner->mPData->mDeceleration * 50 * FIXED_DT;

	if (std::abs(pOwner->GetSpeed()) > 100)	// Decelerer ou accelerer vers z�ro en fonction de la vitesse
	{
		float spd = pOwner->GetSpeed();
		spd += (pOwner->GetSpeed() > 0 ? -1 : 1) * decelerationAmount;
		pOwner->SetSpeed(spd);
	}
	if (std::abs(pOwner->GetSpeed()) < 500)	// Si la vitesse est proche de 0, on la reinitialise
	{
		pOwner->SetSpeed(0);
	}
}

void PlayerAction_Death::OnStart(Player* pOwner)
{
	std::cout << "DEAD" << std::endl;
	std::string AnimName = "death";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}

void PlayerAction_Death::OnUpdate(Player* pOwner)
{
	if (pOwner->mAnimator->GetCurrentAnimation()->GetIsFinished()) {
		pOwner->SetState(Player::PlayerStateList::RESPAWN);
	}
}

void PlayerAction_Respawn::OnStart(Player* pOwner)
{
	std::cout << "RESPAWN" << std::endl;
	std::string AnimName = "respawn";
	pOwner->mAnimator->SetCurrentAnimation(AnimName);
}

void PlayerAction_Respawn::OnUpdate(Player* pOwner)
{
	pOwner->PlayerRespawn();
}
