#include "PlayerAction.h"

void PlayerAction_Jump::OnStart(Player* pOwner)
{
	pOwner->SetGravitySpeed(-pOwner->mPData->mJumpHeight);
	pOwner->mPData->pJumpDuration = 0;

}

void PlayerAction_Jump::OnUpdate(Player* pOwner)
{
		pOwner->secondjump -= 1; 
		pOwner->mPData->pJumpDuration = 0; 
		pOwner->SetGravitySpeed(-pOwner->mPData->mJumpHeight);
		pOwner->SetGravity(true);
}

void PlayerAction_Jump::OnEnd(Player* pOwner)
{

}

void PlayerAction_Crouch::OnStart(Player* pOwner)
{

}

void PlayerAction_Crouch::OnUpdate(Player* pOwner)
{
	float dt = FIXED_DT;
	float spd = pOwner->GetSpeed();
	sf::Vector2f movement = pOwner->InputDirection();
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
	pOwner->SetSpeed(spd);
}

void PlayerAction_Crouch::OnEnd(Player* pOwner)
{
}

void PlayerAction_JumpOnCrouch::OnStart(Player* pOwner)
{
}

void PlayerAction_JumpOnCrouch::OnUpdate(Player* pOwner)
{
	if (pOwner->GetGravity() && pOwner->secondjump <= 0)
		return;
	if (pOwner->mPData->pJumpDuration < pOwner->mPData->mJumpTime) 
		return;

	pOwner->secondjump -= 1;  
	pOwner->mPData->pJumpDuration = 0; 
	pOwner->SetGravitySpeed(-pOwner->mPData->mJumpHeight/1.5f); 
	pOwner->SetGravity(true); 
}

void PlayerAction_JumpOnCrouch::OnEnd(Player* pOwner)
{
}

void PlayerAction_Walk::OnStart(Player* pOwner)
{
}

void PlayerAction_Walk::OnUpdate(Player* pOwner)
{
	sf::Vector2f movement = pOwner->InputDirection();
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

void PlayerAction_Walk::OnEnd(Player* pOwner)
{
}

void PlayerAction_Idle::OnStart(Player* pOwner)
{
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

void PlayerAction_Idle::OnEnd(Player* pOwner)
{
}