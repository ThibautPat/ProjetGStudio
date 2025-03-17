#include "GameManager.h"

#include "../../Core/Entity/Entity.h"
#include "../../Core/Renderer/TextureRender.h"
#include "../../Core/Other/Debug.h"
#include "TextureManager.h"
#include "SceneManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	//mpScene = nullptr;
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
				if (entity->IsRigidBody() && otherEntity->IsRigidBody())
				{
					entity->Repulse(otherEntity);
				}

				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
			}
			else if (entity->hasCollidingLastFrame)
			{
				entity->mBoolGravity = true;
				entity->hasCollidingLastFrame = false;
			}
		}
	}
}

GameManager::~GameManager()
{
	delete mpWindow;
	//delete mpScene;
	delete mScM;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::DrawRender(Entity* entity)
{
	if (entity->GetRender() == nullptr) {
		return;
	}
		
	render_nb++;
	entity->GetRender()->Draw(entity, mpWindow);

}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mClearColor = clearColor;
}

/*
Scene* GameManager::GetScene() const
{
	return mScM->GetScene();
}
*/

void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	//_ASSERT(mpScene != nullptr);
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
		//#TODO peut être remove à la fin
		mpWindow->draw(*entity->GetShape());

		DrawRender(entity);
	}
	
	//TODO remove if u want (for debug)
	std::string render = std::to_string(render_nb);
	Debug::DrawText(10, 60, render, sf::Color::White);
	render_nb = 0;
	//----------

	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}
