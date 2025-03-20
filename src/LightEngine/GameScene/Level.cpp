#include "Level.h"
#include "../Other/Utils.h"
#include "../GameEntity/Player.h"
#include "../GameScene/TestScene.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"
#include "../GameEntity/Teleporter.h"
#include "../GameEntity/Moving_Platform.h"

void Level::ChooseJson(const char* path)
{
	mMap = *Utils::Parse(path);
}

void Level::LoadLevel()
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();

	for (int i = 0; i < mMap["Rows"]; i++) { // Load Player
		for (int j = 0; j < mMap["Columns"]; j++) {

			std::string tmp = mMap["MapPhysics"][i][j];

			if (tmp != "1")
				continue;

			sc->SetPlayer(sc->CreateRectEntity<Player>(200, 100, sf::Color(0, 255, 0, 150)));

			Player* pEntity = sc->GetPlayer();
			pEntity->SetGravity((bool)mMap["Physics"][tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mMap["Physics"][tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mMap["Physics"][tmp]["IsKinematic"]);
			pEntity->SetTag((int)mMap["Physics"][tmp]["Tag"]);
			pEntity->SetPosition(128 * j, 128 * i -128* mMap["Rows"]);
		}
	}

	for (int i = 0; i < mMap["Rows"]; i++) {  // Load Tiles
		for (int j = 0; j < mMap["Columns"]; j++) {

			std::string tmp = mMap["MapPhysics"][i][j];
			//std::string tmp2 = mMap["MapGrid"][i][j];

			if (tmp == "0" || tmp == "1")
				continue;

			Entity* pEntity = CreateNewEnity(tmp.c_str());

			pEntity->SetGravity((bool)mMap["Physics"][tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mMap["Physics"][tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mMap["Physics"][tmp]["IsKinematic"]);
			pEntity->SetTag((int)mMap["Physics"][tmp]["Tag"]);
			pEntity->SetPosition(128 * j, 128 * i - 128 * mMap["Rows"]);

			//if (tmp2 == "X")
			//	continue;

			//(RectangleEntity*)pEntity;
		}
	}
}

Entity* Level::CreateNewEnity(const char* id)
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();
	int name = std::atoi(id);

	switch (name)
	{
	case 2:
	case 4:
	case 6:
	case 10:
	case 11: return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Red);
	case 7: return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Green);
	case 3: return sc->CreateRectEntity<Checkpoint>(128, 128, sf::Color::Red);
	case 5: return sc->CreateRectEntity<DeadlyObstacle>(128, 128, sf::Color::Red);
	case 8: return sc->CreateRectEntity<Teleporter>(128, 128, sf::Color::Red);
	case 9: return sc->CreateRectEntity<Moving_Platform>(128, 128, sf::Color::Red);
	default:
		return nullptr; // Retourne nullptr si aucun cas ne correspond
	}
}