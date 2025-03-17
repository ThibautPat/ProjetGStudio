
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Core/Manager/GameManager.h"
#include "../Game/GameScene/TestScene.h"
#include "../Game/GameScene/TestScene2.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();
	SceneManager* pScM = pInstance->GetSceneManager();

	pInstance->CreateWindow(1280, 720, "TestScene", 63, sf::Color(0,100,255));
	
	//Add all scenes
	pScM->AddScene<TestScene>("testscene");
	pScM->AddScene<TestScene2>("testscene2");


	pScM->SelectScene("testscene");
	pScM->LaunchScene();

	return 0;
}