
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "../Game/TestScene.h"


#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();
	SceneManager* pScM = pInstance->GetSceneManager();

	pInstance->CreateWindow(1280, 720, "TestScene", 63, sf::Color::Black);
	
	pScM->AddScene<TestScene>("testsecne");
	//pas de diff avec <>s
	pScM->SelectScene<TestScene>("testsecne");
	pScM->LaunchScene<TestScene>();

	return 0;
}