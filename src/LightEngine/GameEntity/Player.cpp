#include "Player.h"
#include "../Other/Debug.h"
#include "../Manager/TextureManager.h"
#include "../PlayerStateMachine/PlayerAction.h"
#include "../GameScene/TestScene.h"
#include "../Renderer/AnimationRender.h"
#include "../Collider/AABBCollider.h"

void Player::OnInitialize()
{
    mPData = new PlayerData;
    mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2); //WTF pourquoi l'h�ritage n'est pas fait ?!
    mAs = GameManager::Get()->GetTextureManager();

    //Setup de la gestion de textures
    mAs->LoadSpriteSheet("../../../res/Assets/SpriteSheet/Character.json", "../../../res/Assets/SpriteSheet/spritesheet_character.png", "player");
    mAnimator = new Animator();
    mAnimator->AddAnimation("player", "walk");
    mAnimator->AddAnimation("player", "jump");
    mAnimator->AddAnimation("player", "idle");
    mAnimator->AddAnimation("player", "StartCrouch");
    mAnimator->AddAnimation("player", "OnCrouch");
    //mAnimator->AddAnimation("player", "EndCrouch");
    mAnimator->AddAnimation("player", "fall");
    mAnimator->AddAnimation("player", "death");
    mAnimator->AddAnimation("player", "respawn");
    mAnimator->AddAnimation("player", "OnPush");
    mAnimator->AddAnimation("player", "StartPush");
}

void Player::OnUpdate()
{
    mAnimator->UpdateCurrentAnimation();

    if (mPData->isGrounded && std::abs(mPData->mDirection.x) == 1 && !mPData->isCrouching) {
        SetState(WALK);
    }

    if (mReverse && mAnimator->GetRatio().y == 1) {
        mAnimator->SetRatio(sf::Vector2f(mAnimator->GetRatio().x, -1.f));
    }
    else if (!mReverse && mAnimator->GetRatio().y == -1) {
        mAnimator->SetRatio(sf::Vector2f(mAnimator->GetRatio().x, 1.f));
    }

    if (mPData->mDirection.x == -1 && !mPData->isBackward) {
        mAnimator->SetRatio(sf::Vector2f(-1.f, mAnimator->GetRatio().y));
        mPData->isBackward = true;
    }
    else if (mPData->mDirection.x == 1 && mPData->isBackward) {
        mAnimator->SetRatio(sf::Vector2f(1.f, mAnimator->GetRatio().y));
        mPData->isBackward = false;
    }

    if (!mPData->isGrounded && GetGravitySpeed() > 0.f) {
        SetState(FALL);
    }

    if (mPData->mDirection.x == 0 && !mPData->isCrouching) {
        if (mPData->isGrounded && !mPData->playerIsDead) {
            SetState(IDLE);
        }
    }

    mActions[(int)mState]->OnUpdate(this);

    std::string text2 = std::to_string((int)mSpeed);
    Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 50, text2, sf::Color::White);
    std::string text3 = std::to_string((int)mPData->isGrounded);
    Debug::DrawText(mShape.getPosition().x, mShape.getPosition().y - 70, text3, sf::Color::Red);
}

TextureRender* Player::GetRender()
{
    return mAnimator->GetCurrentAnimation();
}

void Player::OnCollision(Entity* other)
{
    mReverse = false;

    if (other->IsTag(TestScene::Tag::METALIC_OBSTACLE) && static_cast<AABBCollider*>(GetCollider())->GetCollideFace()->y != 0)
    {
        if (static_cast<AABBCollider*>(GetCollider())->GetCollideFace()->y == -1)
        {
            mReverse = true;
            mBoolGravity = false;
        }
        mPData->isGrounded = true;  // Le joueur est au sol lorsqu'il touche un obstacle métallique

    }
    else if (static_cast<AABBCollider*>(GetCollider())->GetCollideFace()->y == 1)
    {
		if (other->IsTag(TestScene::Tag::PLATFORM) || other->IsTag(TestScene::Tag::OBSTACLE) || other->IsTag(TestScene::Tag::METALIC_OBSTACLE))
        {
            mPData->isGrounded = true;  // Le joueur est au sol lorsqu'il touche une plateforme
        }
    }
    else {
        mPData->isGrounded = false; // Sinon, il n'est pas au sol
    }
    if (other->IsTag(TestScene::Tag::OBSTACLE) && std::abs(static_cast<AABBCollider*>(GetCollider())->GetCollideFace()->x) == 1) {
        if (other->GetGravitySpeed() <= 10) {
            SetState(PUSH);
        }
        else {
            SetState(IDLE);
        }
    }
    if (other->IsTag(TestScene::Tag::CHECKPOINT))
    {
        mPData->isGrounded = false; // Sinon, il n'est pas au sol 
    }
    if (other->IsTag(TestScene::Tag::CHECKPOINT)) 
    { 
        mPData->mLastCheckPoint = other->GetPosition(0.f, 0.f); // On set le dernier checkpoint  

    }
    if (other->IsTag(TestScene::Tag::DEADLYOBSTACLE)) 
    {
        SetState(DEAD);
    }
    if (other->IsTag(TestScene::Tag::END_LEVEL))
    {
    }
}

void Player::PlayerRespawn()
{
    SetSpeed(0); // On reset la vitesse du joueur
    SetGravitySpeed(0); // On reset la vitesse de gravit� du joueur
    SetPosition(mPData->mLastCheckPoint.x, mPData->mLastCheckPoint.y); // On respawn le joueur au dernier checkpoint
    if (mPData->RespawnClock.getElapsedTime().asSeconds() > 5) // Si le joueur est mort depuis plus de 5 seconde
    {
        SetGravity(true); // On r�active la gravit� 
        mPData->playerIsDead = false;
    }
}

void Player::PlayerDeath()
{
    mPData->RespawnClock.restart(); // On restart le timer de respawn 
    mPData->playerIsDead = true;
}

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

bool Player::Movement() {
    sf::Vector2f movement = mPData->mDirection;

    if (movement == sf::Vector2f(0.f, 0.f)) {
        return false;
    }

    float speed = GetSpeed();
    speed += movement.x * 50 * FIXED_DT * mPData->mAcceleration;
    SetSpeed(speed);
    if (movement.x != 0) // Mise � jour de mLastMovement si movement.x n'est pas nul
    {
        mLastMovement = movement;
    }
    if ((mLastMovement.x == -1 && GetSpeed() > 0) || (mLastMovement.x == 1 && GetSpeed() < 0)) // Gestion de la d�c�l�ration si la direction du mouvement change
    {
        float spd = GetSpeed();
        spd += (mLastMovement.x == -1 ? -1 : 1) * mPData->mDeceleration * 50 * FIXED_DT;
        SetSpeed(spd);
    }
    return true;
}

void Player::FixedUpdate(float dt)
{
    Fall(dt);
    mPData->pJumpDuration += dt;

    Move(mPData->mDirection, dt);
}

bool Player::SetState(PlayerStateList newState)
{
    if (mTransitions[(int)mState][(int)newState]) {
        mState = newState;
        mActions[(int)mState]->OnStart(this);
        return true;
    }
    return false;
}

Player::Player()
{

    SetTag(TestScene::Tag::PLAYER);

    for (int i = 0; i < STATE_COUNT; i++)
    {
        for (int j = 0; j < STATE_COUNT; j++)
        {
            mTransitions[i][j] = false;
        }
    }

    mActions[(int)PlayerStateList::IDLE] = new PlayerAction_Idle();
    mActions[(int)PlayerStateList::CROUCH] = new PlayerAction_Crouch();
    mActions[(int)PlayerStateList::WALK] = new PlayerAction_Walk();
    mActions[(int)PlayerStateList::JUMP] = new PlayerAction_Jump();
    mActions[(int)PlayerStateList::FALL] = new PlayerAction_Fall();
    mActions[(int)PlayerStateList::DEAD] = new PlayerAction_Death();
    mActions[(int)PlayerStateList::RESPAWN] = new PlayerAction_Respawn();
    mActions[(int)PlayerStateList::PUSH] = new PlayerAction_Push();

    SetTransition(PlayerStateList::IDLE, PlayerStateList::WALK, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::JUMP, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::CROUCH, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::FALL, true);
    SetTransition(PlayerStateList::IDLE, PlayerStateList::DEAD, true);

    SetTransition(PlayerStateList::CROUCH, PlayerStateList::IDLE, true);
    SetTransition(PlayerStateList::CROUCH, PlayerStateList::JUMP, true);
    SetTransition(PlayerStateList::CROUCH, PlayerStateList::WALK, true);
    SetTransition(PlayerStateList::CROUCH, PlayerStateList::DEAD, true);
    SetTransition(PlayerStateList::CROUCH, PlayerStateList::PUSH, true);

    SetTransition(PlayerStateList::WALK, PlayerStateList::JUMP, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::IDLE, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::CROUCH, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::FALL, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::DEAD, true);
    SetTransition(PlayerStateList::WALK, PlayerStateList::PUSH, true);

    SetTransition(PlayerStateList::JUMP, PlayerStateList::FALL, true);
    SetTransition(PlayerStateList::JUMP, PlayerStateList::CROUCH, true);
    SetTransition(PlayerStateList::JUMP, PlayerStateList::DEAD, true);
    SetTransition(PlayerStateList::JUMP, PlayerStateList::WALK, true);
    SetTransition(PlayerStateList::JUMP, PlayerStateList::IDLE, true);

    SetTransition(PlayerStateList::FALL, PlayerStateList::IDLE, true);
    SetTransition(PlayerStateList::FALL, PlayerStateList::DEAD, true);
    SetTransition(PlayerStateList::FALL, PlayerStateList::WALK, true);

    SetTransition(PlayerStateList::DEAD, PlayerStateList::RESPAWN, true);

    SetTransition(PlayerStateList::RESPAWN, PlayerStateList::IDLE, true);

    SetTransition(PlayerStateList::PUSH, PlayerStateList::IDLE, true);
    SetTransition(PlayerStateList::PUSH, PlayerStateList::DEAD, true);
}

Player::~Player()
{
}
