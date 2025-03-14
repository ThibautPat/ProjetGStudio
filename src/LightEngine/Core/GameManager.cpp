#include "GameManager.h"

#include "Entity.h"
#include "TextureRender.h"
#include "Debug.h"
#include "../Core/InputManager.h"
#include "../Core/TextureManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../Game/TestScene.h"
#include "../Game/Player.h"

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;
	mAs = new TextureManager();
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
					if (otherEntity->IsKinematic()) {
						entity->Block(otherEntity);
					}
					else {
						entity->Repulse(otherEntity);
					}
				}

				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
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
	delete mpScene;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::DrawTextureRender(Entity* entity)
{
	if (entity->GetTextureRender() == nullptr) {
		return;
	}

	TextureRender* tr = entity->GetTextureRender();

	std::string tname = tr->GetTextName();
	sf::IntRect* textrect = tr->GetTextureRect();
	sf::Texture text = sf::Texture();
	mAs->FindTexture(tname, *textrect, &text);

	sf::Sprite spr;
	spr.setTexture(text);

	float offset = 0.5f;
	sf::Vector2f renderPos = sf::Vector2f(
		entity->GetPosition(0, 0).x - text.getSize().x * offset,
		entity->GetPosition(0, 0).y - text.getSize().y * offset);
	spr.setPosition(renderPos);

	mpWindow->draw(spr);

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

	_ASSERT(mpScene != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		
		SetDeltaTime(clock.restart().asSeconds());
		
		HandleInput();
		
			Update();
		
			Draw();
		
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

		mpScene->OnEvent(event);
	}
}

void GameManager::Update()
{
	mpScene->OnUpdate();
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
		if (!mpScene->freeze)
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

		DrawTextureRender(entity);
	}
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}
