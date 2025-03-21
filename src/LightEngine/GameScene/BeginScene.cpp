#include "BeginScene.h"
#include "../GameEntity/BackGround.h"


void BeginScene::OnInitialize()
{
	mView = new sf::View(sf::FloatRect(0, 0, GetWindowWidth(), GetWindowHeight())); // Ajout de la cam�ra
	m_InstanceGameManager = GameManager::Get();

	BackGround* pEntity1 = CreateRectEntity<BackGround>(1080, 1920, sf::Color::White); 
	pEntity1->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
	pEntity1->SetRigidBody(false); 
	pEntity1->SetIsKinematic(true);
	pEntity1->SetGravity(false);
	pEntity1->SetBackGroundTexture("..//..//..//res//Assets//Background//Key_Art.png");
}

void BeginScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::JoystickButtonPressed)
	{
		text = "Loading...";
		isPressed = true;
		menuClock.restart();
	}
}

void BeginScene::HandleConsoleEvent()
{
}

void BeginScene::HandleKeyboardEvent()
{
}

void BeginScene::OnUpdate()
{
	Debug::DrawText(GetWindowWidth() / 2 - 100, GetWindowHeight() / 2 - 100, text, 0, 0, sf::Color::White);

	m_InstanceGameManager->GetWindow()->setView(*mView);

	if (isPressed && menuClock.getElapsedTime().asSeconds() > 0.2f)
	{
		for (Entity* entity : m_InstanceGameManager->Get()->GetEntities<Entity>())
		{
			entity->Destroy();
		}
		m_InstanceGameManager->GetSceneManager()->SelectScene("testscene");
		m_InstanceGameManager->GetSceneManager()->LaunchScene();
	}
}
