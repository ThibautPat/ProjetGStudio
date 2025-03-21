
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Manager/GameManager.h"
#include "GameScene/TestScene.h"
#include "GameScene/BeginScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();
	SceneManager* pScM = pInstance->GetSceneManager();

	pInstance->CreateWindow(1920, 1080, "Solnish", 60, sf::Color(100,150,255));
	
	pScM->AddScene<TestScene>("testscene");
	pScM->AddScene<BeginScene>("beginscene");

	pScM->SelectScene("beginscene");
	pScM->LaunchScene();

	return 0;
}