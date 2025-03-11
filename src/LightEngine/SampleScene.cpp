#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateRectEntity<DummyEntityRect>(100, 100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateRectEntity<DummyEntityRect>(50, 50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);

	pEntity3 = CreateCircleEntity<DummyEntityCircle>(100, sf::Color::Magenta);
	pEntity3->SetPosition(100, 400);
	pEntity3->SetRigidBody(true);

	pEntity4 = CreateCircleEntity<DummyEntityCircle>(50, sf::Color::Yellow);
	pEntity4->SetPosition(600, 400);
	pEntity4->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity3, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity4, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
	if (event.mouseButton.button == sf::Mouse::Button::Middle)
	{
		if (pEntitySelected2 != nullptr)
		{
			pEntitySelected2->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void SampleScene::TrySetSelectedEntity(DummyEntityRect* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::TrySetSelectedEntity(DummyEntityCircle* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected2 = pEntity;
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition(1.f, 1.f);
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	if (pEntitySelected2 != nullptr)
	{
		sf::Vector2f position2 = pEntitySelected2->GetPosition(1.f, 1.f);
		Debug::DrawCircle(position2.x, position2.y, 10, sf::Color::Cyan);
	}
}