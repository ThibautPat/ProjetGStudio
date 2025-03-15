#include "Player.h"
#include "../Core/InputManager.h"
#include "../Core/Debug.h"
#include "../Core/TextureManager.h"
#include "../Game/PlayerAction.h"
#include "../Game/PlayerCondition.h"
#include "../Game/TestScene.h"


void Player::Move(sf::Vector2f movement, float dt)
{
	

	SetDirection(dt, 0, mSpeed);
}

void Player::FixedUpdate(float dt)
{
	Fall(dt); 
	mPData->pJumpDuration += dt;
	Move(InputDirection(), dt); 
}

void Player::OnUpdate()
{
	const char* stateName = GetStateName((PlayerStateList)mStateMachine.GetCurrentState());
	// Debug de valeur

	Debug::DrawText(mShape.getPosition().x,mShape.getPosition().y - 30, stateName ,sf::Color::White);

	std::string text2 = std::to_string(mSpeed);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);
	mStateMachine.Update(); 
	//Stress Test TextureManager
	if (testvar >= 110)
		testvar = 0;

	testvar += 18;

	sf::IntRect rect = sf::IntRect(0, 0, 18, 18);
	mTextured->SetTextureRect(rect);
	//-----
}

void Player::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2); //WTF pourquoi l'h�ritage n'est pas fait ?!
	mPData = new PlayerData;
	
	mAs = GameManager::Get()->GetAssetsManager();

	//Setup de la gestion de textures
	mAs->LoadTexture("../../../res/Assets/Tilemap/tilemap_packed.png", "tilemap");
	mTextured = new TextureRender();
	mTextured->SelectTexture("tilemap", sf::IntRect(0, 0, 110, 110));
}

sf::Vector2f Player::InputDirection()
{
	float dir_x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
	{
		dir_x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
	{
		dir_x = 1;
	}

	return sf::Vector2f(dir_x, 0);
}

Player::~Player()
{
}

Player::Player() : mStateMachine(this, PlayerStateList::COUNT)
{
	SetTag(TestScene::Tag::PLAYER); 

	//IDLE
	{
		Behaviour<Player>* pStay = mStateMachine.CreateBehaviour(PlayerStateList::IDLE);
		pStay->AddAction<PlayerAction_Idle>();
		//-> WALK
		{
			auto transition = pStay->CreateTransition(PlayerStateList::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
		}
		//-> JUMP
		{
			auto transition = pStay->CreateTransition(PlayerStateList::JUMP);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false); 
		}
		//-> CROUCH
		{
			auto transition = pStay->CreateTransition(PlayerStateList::CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
		}
		//-> JUMP ON CROUCH
		{
			auto transition = pStay->CreateTransition(PlayerStateList::JUMP_ON_CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
		}
		//-> DASH
		{
			auto transition = pStay->CreateTransition(PlayerStateList::DASH);

			auto condition = transition->AddCondition<PlayerCondition_IsDashing>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			auto condition3 = transition->AddCondition<PlayerCondition_DashOnCoolDown>(false); 

		}
	}
	//WALK
	{
		Behaviour<Player>* pWalk = mStateMachine.CreateBehaviour(PlayerStateList::WALK);
		pWalk->AddAction<PlayerAction_Walk>();
		//-> IDLE
		{
			auto transition = pWalk->CreateTransition(PlayerStateList::IDLE);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
		}
		//-> JUMP
		{
			auto transition = pWalk->CreateTransition(PlayerStateList::JUMP);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_HasJump>(true);
		}
		//-> CROUCH
		{
			auto transition = pWalk->CreateTransition(PlayerStateList::CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
		}
		//-> DASH
		{
			auto transition = pWalk->CreateTransition(PlayerStateList::DASH);

			auto condition = transition->AddCondition<PlayerCondition_IsDashing>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			auto condition3 = transition->AddCondition<PlayerCondition_DashOnCoolDown>(false);
		}
	}
	//JUMP
	{
		Behaviour<Player>* pJump = mStateMachine.CreateBehaviour(PlayerStateList::JUMP);
		pJump->AddAction<PlayerAction_Jump>();
		//-> IDLE
		{
			auto transition = pJump->CreateTransition(PlayerStateList::IDLE);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(false);
			auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
		}
		//-> WALK
		{
			auto transition = pJump->CreateTransition(PlayerStateList::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_IsJumping>(false);
		}
		//-> CROUCH
		{
			auto transition = pJump->CreateTransition(PlayerStateList::CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(false);
		}
	}
	//CROUCH
	{
		Behaviour<Player>* pCrouch = mStateMachine.CreateBehaviour(PlayerStateList::CROUCH);
		pCrouch->AddAction<PlayerAction_Crouch>();
		//-> IDLE
		{
			auto transition = pCrouch->CreateTransition(PlayerStateList::IDLE);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
		}
		//-> WALK
		{
			auto transition = pCrouch->CreateTransition(PlayerStateList::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
		}
		//-> JUMP ON CROUCH
		{
			auto transition = pCrouch->CreateTransition(PlayerStateList::JUMP_ON_CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
		}
		//-> DASH
		{
			auto transition = pCrouch->CreateTransition(PlayerStateList::DASH);

			auto condition = transition->AddCondition<PlayerCondition_IsDashing>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true); 
			auto condition3 = transition->AddCondition<PlayerCondition_DashOnCoolDown>(false);
		}
	}
	//JUMP ON CROUCH
	{
		Behaviour<Player>* pJumpOnCrouch = mStateMachine.CreateBehaviour(PlayerStateList::JUMP_ON_CROUCH);
		pJumpOnCrouch->AddAction<PlayerAction_JumpOnCrouch>();
		//-> IDLE
		{
			auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::IDLE);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(false);
			auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);

		}
		//-> WALK
		{
			auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_IsJumping>(false);
		}
		//-> CROUCH
		{
			auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
		}
	}
	// DASH
	{
		Behaviour<Player>* pDash = mStateMachine.CreateBehaviour(PlayerStateList::DASH);
		pDash->AddAction<PlayerAction_Dash>();
		//-> IDLE
		{
			auto transition = pDash->CreateTransition(PlayerStateList::IDLE);

			auto condition = transition->AddCondition<PlayerCondition_IsDashing>(false);
		}
		//-> WALK
		{
			auto transition = pDash->CreateTransition(PlayerStateList::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_HasDash>(false); 


		}
		//-> JUMP
		{
			auto transition = pDash->CreateTransition(PlayerStateList::JUMP);

			auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);

			auto condition3 = transition->AddCondition<PlayerCondition_HasDash>(false);
		}
		//-> CROUCH
		{
			auto transition = pDash->CreateTransition(PlayerStateList::CROUCH);

			auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
			auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
			auto condition3 = transition->AddCondition<PlayerCondition_HasDash>(false);
		}
	}
	mStateMachine.SetState(PlayerStateList::IDLE);


}
const char* Player::GetStateName(PlayerStateList state) const
{
	switch (state)
	{
	case IDLE: return "IDLE";
	case WALK: return "WALK";
	case JUMP: return "JUMP";
	case CROUCH: return "CROUCH";
	case JUMP_ON_CROUCH: return "JUMP_ON_CROUCH";	
	case DASH: return "DASH";
	default: return "Unknown";
	}
}
