#include "Level.h"
#include "../Other/Utils.h"
#include "../GameEntity/Player.h"
#include "../GameScene/TestScene.h"
#include "../GameEntity/Checkpoint.h"
#include "../GameEntity/DeadlyObstacle.h"
#include "../GameEntity/Teleporter.h"
#include "../GameEntity/Moving_Platform.h"
#include "../Manager/TextureManager.h"
#include "../Renderer/TextureRender.h"

void Level::ChooseJson(const char* path)
{
	mMap = *Utils::Parse(path);
	std::string jsonpath = mMap["JsonPath"];
	std::string sourcepath = mMap["SourcePath"];
	std::string spritesheetname = mMap["SpriteSheetName"];
	GameManager::Get()->GetTextureManager()->LoadSpriteSheet(jsonpath.c_str(), sourcepath.c_str(), spritesheetname);
}

void Level::LoadLevel()
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();


	for (int i = 0; i < mMap["Rows"]; i++) { // Load Player
		for (int j = 0; j < mMap["Columns"]; j++) {

			std::string tmp = mMap["MapPhysics"][i][j];

			if (tmp != "1")
				continue;

			sc->SetPlayer(sc->CreateRectEntity<Player>(175, 75, sf::Color(0, 255, 0, 150)));

			Player* pEntity = sc->GetPlayer();
			pEntity->SetGravity((bool)mMap["Physics"][tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mMap["Physics"][tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mMap["Physics"][tmp]["IsKinematic"]);
			pEntity->SetTag((int)mMap["Physics"][tmp]["Tag"]);
			pEntity->SetPosition(128 * j, 128 * i);
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
			pEntity->SetPosition(128 * j, 128 * i);
			std::string spritesheetname = mMap["SpriteSheetName"];
			pEntity->InitRender(spritesheetname.c_str(), ((std::string)mMap["MapGrid"][i][j]).c_str());

			std::cout << ((std::string)mMap["MapGrid"][i][j]).c_str() << std::endl;
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
	case 11: return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Transparent);
	case 7: return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Transparent);
	case 3: return sc->CreateRectEntity<Checkpoint>(128, 128, sf::Color::Transparent);
	case 5: return sc->CreateRectEntity<DeadlyObstacle>(128, 128, sf::Color::Transparent);
	case 8: return sc->CreateRectEntity<Teleporter>(128, 128, sf::Color::Transparent);
	case 9: return sc->CreateRectEntity<Moving_Platform>(128, 128, sf::Color::Transparent);
	default:
		return nullptr; // Retourne nullptr si aucun cas ne correspond
	}
}