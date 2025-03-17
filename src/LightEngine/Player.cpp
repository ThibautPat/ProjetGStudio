#include "Player.h"
#include "InputManager.h"
#include "Debug.h"
#include "TextureManager.h"
#include "PlayerAction.h"
#include "PlayerCondition.h"
#include "TestScene.h"
#include "AnimationRender.h"


void Player::Move(sf::Vector2f movement, float dt)
{
	if (mSpeed > mPData->mMaxSpeedWalk)
	{
		mSpeed = mPData->mMaxSpeedWalk;
	}
	if (mSpeed < -mPData->mMaxSpeedWalk)
	{
		mSpeed = -mPData->mMaxSpeedWalk;
	}

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

	std::string text2 = std::to_string((int)mSpeed);
	Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);
	mStateMachine.Update(); 

	mTextured->UpdateAnimation();
}

void Player::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2); //WTF pourquoi l'h�ritage n'est pas fait ?!
	mPData = new PlayerData;
	
	mAs = GameManager::Get()->GetTextureManager();

	//Setup de la gestion de textures
	mAs->LoadTexture("../../../res/Assets/Tilemap/tilemap_packed.png", "tilemap");
	mTextured = new AnimationRender(8, "tilemap", sf::IntRect(0, 0, 18, 18));
	//mTextured->SelectTexture();
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

	{
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
			//-> FALL WALK
			{
				auto transition = pStay->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL IDLE
			{
				auto transition = pStay->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL CROUCH
			{
				auto transition = pStay->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(false);
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
			//-> FALL WALK 
			{
				auto transition = pWalk->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL IDLE
			{
				auto transition = pWalk->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL CROUCH
			{
				auto transition = pWalk->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
		}
		//JUMP
		{
			Behaviour<Player>* pJump = mStateMachine.CreateBehaviour(PlayerStateList::JUMP);
			pJump->AddAction<PlayerAction_Jump>();

			//-> ON JUMP WALK
			{
				auto transition = pJump->CreateTransition(PlayerStateList::ON_JUMP_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> ON JUMP IDLE
			{
				auto transition = pJump->CreateTransition(PlayerStateList::ON_JUMP_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> ON JUMP CROUCH
			{
				auto transition = pJump->CreateTransition(PlayerStateList::ON_JUMP_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
			}
		}
		//ON JUMP WALK
		{
			Behaviour<Player>* pOnJumpWalk = mStateMachine.CreateBehaviour(PlayerStateList::ON_JUMP_WALK);
			pOnJumpWalk->AddAction<PlayerAction_OnJumpWalk>();
			//-> IDLE
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			}
			//-> WALK
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);

			}
			//-> CROUCH
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			}
			//-> JUMP
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> FALL WALK 
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL IDLE
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL CROUCH
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> ON JUMP IDLE
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::ON_JUMP_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> ON JUMP CROUCH
			{
				auto transition = pOnJumpWalk->CreateTransition(PlayerStateList::ON_JUMP_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
		}
		//ON JUMP IDLE
		{
			Behaviour<Player>* pOnJumpIdle = mStateMachine.CreateBehaviour(PlayerStateList::ON_JUMP_IDLE);
			pOnJumpIdle->AddAction<PlayerAction_OnJumpIdle>();
			//-> IDLE
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			}
			//-> WALK
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);

			}
			//-> CROUCH
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> JUMP
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> FALL WALK 
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL IDLE
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
			}
			//-> FALL CROUCH
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> ON JUMP WALK
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::ON_JUMP_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> ON JUMP CROUCH
			{
				auto transition = pOnJumpIdle->CreateTransition(PlayerStateList::ON_JUMP_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
		}
		//ON JUMP CROUCH 
		{
			Behaviour<Player>* pOnJumpCrouch = mStateMachine.CreateBehaviour(PlayerStateList::ON_JUMP_CROUCH);
			pOnJumpCrouch->AddAction<PlayerAction_OnJumpCrouch>();
			//-> IDLE
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
			}
			//-> WALK
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);

			}
			//-> CROUCH
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsJumping>(false);
				auto condition3 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> JUMP ON CROUCH
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::JUMP_ON_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> JUMP
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL WALK 
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL IDLE
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_GravityPlus>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> FALL CROUCH
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition <PlayerCondition_GravityPlus>(true);
				auto condition4 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> ON JUMP WALK
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::ON_JUMP_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> ON JUMP IDLE
			{
				auto transition = pOnJumpCrouch->CreateTransition(PlayerStateList::ON_JUMP_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
		}
		//FALL WALK
		{
			Behaviour<Player>* pFallWalk = mStateMachine.CreateBehaviour(PlayerStateList::FALL_WALK);
			pFallWalk->AddAction<PlayerAction_FallWalk>();
			//-> IDLE
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> WALK
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> CROUCH
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> JUMP
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> FALL CROUCH
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> FALL IDLE
			{
				auto transition = pFallWalk->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
		}
		//FALL IDLE
		{
			Behaviour<Player>* pFallIdle = mStateMachine.CreateBehaviour(PlayerStateList::FALL_IDLE);
			pFallIdle->AddAction<PlayerAction_FallIdle>();
			//-> IDLE
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> WALK
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> CROUCH
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> JUMP ON CROUCH
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::JUMP_ON_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> JUMP
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> FALL CROUCH
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::FALL_CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> FALL WALK
			{
				auto transition = pFallIdle->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
		}
		//FALL CROUCH
		{
			Behaviour<Player>* pFallCrouch = mStateMachine.CreateBehaviour(PlayerStateList::FALL_CROUCH);
			pFallCrouch->AddAction<PlayerAction_FallCrouch>();
			//-> IDLE
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> WALK
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
			}
			//-> CROUCH
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::CROUCH);

				auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_IsGrounded>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsWalking>(true);
			}
			//-> JUMP
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::JUMP);

				auto condition = transition->AddCondition<PlayerCondition_IsJumping>(true);
				auto condition2 = transition->AddCondition<PlayerCondition_HasJump>(true);
			}
			//-> FALL IDLE
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::FALL_IDLE);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(false);
			}
			//-> FALL WALK
			{
				auto transition = pFallCrouch->CreateTransition(PlayerStateList::FALL_WALK);

				auto condition = transition->AddCondition<PlayerCondition_IsGrounded>(false);
				auto condition2 = transition->AddCondition<PlayerCondition_IsWalking>(true);
				auto condition3 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
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
		}
		//JUMP ON CROUCH
		{
			Behaviour<Player>* pJumpOnCrouch = mStateMachine.CreateBehaviour(PlayerStateList::JUMP_ON_CROUCH);
			pJumpOnCrouch->AddAction<PlayerAction_JumpOnCrouch>();
			{

				//-> ON JUMP WALK
				{
					auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::ON_JUMP_WALK);

					auto condition = transition->AddCondition<PlayerCondition_IsWalking>(true);
					auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
				}
				//-> ON JUMP IDLE
				{
					auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::ON_JUMP_IDLE);

					auto condition = transition->AddCondition<PlayerCondition_IsWalking>(false);
					auto condition2 = transition->AddCondition<PlayerCondition_IsCrouching>(false);
				}
				//-> ON JUMP CROUCH
				{
					auto transition = pJumpOnCrouch->CreateTransition(PlayerStateList::ON_JUMP_CROUCH);

					auto condition = transition->AddCondition<PlayerCondition_IsCrouching>(true);
				}
			}
		}
		mStateMachine.SetState(PlayerStateList::IDLE);
	}

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
	case FALL_CROUCH: return "FALL_CROUCH";
	case FALL_WALK: return "FALL_WALK";
	case FALL_IDLE: return "FALL_IDLE";
	case ON_JUMP_CROUCH: return "ON_JUMP_CROUCH";
	case ON_JUMP_WALK: return "ON_JUMP_WALK";
	case ON_JUMP_IDLE: return "ON_JUMP_IDLE";
	default: return "Unknown";
	}
}
