
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "../Game/TestScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "TestScene", 63, sf::Color::Black);
	
	pInstance->LaunchScene<TestScene>();

	return 0;
}