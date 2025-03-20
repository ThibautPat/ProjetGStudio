#include "GameManager.h"

#include "../Entity/Entity.h"
#include "../Renderer/TextureRender.h"
#include "../Other/Debug.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../GameScene/TestScene.h"
#include "../GameEntity/Player.h"

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mWindowWidth = -1;
	mWindowHeight = -1;
	mAs = new TextureManager();
	mScM = new SceneManager();
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;
	return &mInstance;
}

void GameManager::FixedUpdate()
{
	for (Entity* entity : mEntities) {
		entity->FixedUpdate(FIXED_DT);
	}
	PhysiqueUpdate();
}

void GameManager::PhysiqueUpdate()
{
	//Collision
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != mEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			if (entity->IsColliding(otherEntity))
			{
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);

				if (entity->IsRigidBody() && otherEntity->IsRigidBody())
				{
					if (otherEntity->IsKinematic()) {
						entity->Block(otherEntity);
					}
					else {
						entity->Repulse(otherEntity);
					}
				}
			}
			else if (entity->hasCollidedLastFrame)
			{
				
				entity->mBoolGravity = true;
				entity->hasCollidedLastFrame = false;
			}
		}
	}
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mScM;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::DrawRender(Entity* entity)
{
	if (entity->GetTextureRender() == nullptr) {
		return;
	}

	entity->GetTextureRender()->Draw(entity, mpWindow);
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mClearColor = clearColor;
}

void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		CreateWindow(1280, 720, "Default window");
	}

	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);
	_ASSERT(mScM->GetScene() != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());
		
		HandleInput();
		
		Update();
		
		Draw();

		if (IsSceneChanged()) {
			mEntities.clear();
			mScM->LaunchScene();
			return;
		}
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}
		mScM->GetScene()->OnEvent(event);
	}
}

void GameManager::Update()
{
	mScM->GetScene()->OnUpdate();
    //Update
    for (auto it = mEntities.begin(); it != mEntities.end(); )
    {
		Entity* entity = *it;

		entity->Update();
		
        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }
        mEntitiesToDestroy.push_back(entity);
        it = mEntities.erase(it);
    }

	//FixedUpdate
	mAccumulatedDt += mDeltaTime;
	while (mAccumulatedDt >= FIXED_DT)
	{
		if (!mScM->GetScene()->freeze)
		{
			FixedUpdate();
		}
		mAccumulatedDt -= FIXED_DT;
	}

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();
}

void GameManager::Draw()
{
	mpWindow->clear(mClearColor);
	
	for (Entity* entity : mEntities)
	{
		DrawRender(entity);

		mpWindow->draw(*entity->GetShape());
	}
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}
