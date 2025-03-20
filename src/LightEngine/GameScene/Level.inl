#include "Level.h"


//template <typename T>
//inline T* Level::CreateNewEnity(const char* id)
//{
//	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();
//	int name = std::atoi(id);
//
//	switch (name)
//	{
//	case 2:
//	case 4:
//	case 6:
//	case 10:
//	case 11: return sc->CreateRectEntity<T>(128, 128, sf::Color::Red);
//	case 7: return sc->CreateRectEntity<T>(128, 128, sf::Color::Green);
//	case 3: return sc->CreateRectEntity<T>(128, 128, sf::Color::Red);
//	case 5: return sc->CreateRectEntity<T>(128, 128, sf::Color::Red);
//	case 8: return sc->CreateRectEntity<T>(128, 128, sf::Color::Red);
//	case 9: return sc->CreateRectEntity<T>(128, 128, sf::Color::Red);
//	default:
//		return nullptr; // Retourne nullptr si aucun cas ne correspond
//	}
//}