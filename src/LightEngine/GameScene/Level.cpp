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

void Level::ChooseJson(const char* path, const char* envipath)
{
	mTileMap = *Utils::Parse(path);
	std::string jsonpath1 = mTileMap["JsonPath"];
	std::string sourcepath1 = mTileMap["SourcePath"];
	std::string spritesheetname1 = mTileMap["SpriteSheetName"];
	GameManager::Get()->GetTextureManager()->LoadSpriteSheet(jsonpath1.c_str(), sourcepath1.c_str(), spritesheetname1);

	mEnv = *Utils::Parse(envipath);
	std::string jsonpath2 = mEnv["JsonPath"];
	std::string sourcepath2 = mEnv["SourcePath"];
	std::string spritesheetname2 = mEnv["SpriteSheetName"];
	GameManager::Get()->GetTextureManager()->LoadSpriteSheet(jsonpath2.c_str(), sourcepath2.c_str(), spritesheetname2);
}

void Level::LoadLevel()
{
	AddEnvironment();
	AddPlayer();
	AddTiles();
}

void Level::AddPlayer()
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();

	for (int i = 0; i < mTileMap["Rows"]; i++) { // Load Player
		for (int j = 0; j < mTileMap["Columns"]; j++) {

			std::string tmp = mTileMap["MapPhysics"][i][j];

			if (tmp != "1")
				continue;

			sc->SetPlayer(sc->CreateRectEntity<Player>(200, 75, sf::Color::Transparent));

			Player* pEntity = sc->GetPlayer();
			pEntity->SetGravity((bool)mTileMap["Physics"][tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mTileMap["Physics"][tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mTileMap["Physics"][tmp]["IsKinematic"]);
			pEntity->SetTag((int)mTileMap["Physics"][tmp]["Tag"]);
			pEntity->SetPosition(128 * j, 128 * i);
		}
	}
}

void Level::AddEnvironment()
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();

	for (int i = 0; i < mTileMap["Rows"]; i++) {
		for (int j = 0; j < mTileMap["Columns"]; j++) {

			std::string tmp = mTileMap["MapPhysics"][i][j];

			if (tmp != "3")
				continue;

			Entity* pEntity = sc->CreateRectEntity<RectangleEntity>(50, 50, sf::Color::Transparent);

			pEntity->SetGravity(false);
			pEntity->SetRigidBody(false);
			pEntity->SetIsKinematic(false);
			pEntity->SetTag(12);
			pEntity->SetPosition(128 * j, 128 * i);
			pEntity->SetBackground(true);

			std::string spritesheetname = mTileMap["SpriteSheetName"];

			pEntity->InitRender(spritesheetname.c_str(), "");
			sf::IntRect rect(4*128, 7*128, 256, 384);
			pEntity->GetTextureRender()->SetSpriteRect(rect);
		}
	}
}

void Level::AddTiles()
{
	for (int i = 0; i < mTileMap["Rows"]; i++) {  // Load Tiles
		for (int j = 0; j < mTileMap["Columns"]; j++) {
			coX = 128 * j;
			coY = 128 * i;
			std::string tmp = mTileMap["MapPhysics"][i][j];

			if (tmp == "0" || tmp == "1")
				continue;

			Entity* pEntity = CreateNewEnity(tmp.c_str());

			pEntity->SetGravity((bool)mTileMap["Physics"][tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mTileMap["Physics"][tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mTileMap["Physics"][tmp]["IsKinematic"]);
			pEntity->SetTag((int)mTileMap["Physics"][tmp]["Tag"]);
			pEntity->SetPosition(128 * j, 128 * i);

			pEntity->SetBackground((bool)mTileMap["Physics"][tmp]["Background"]);

			std::string spritesheetname = mTileMap["SpriteSheetName"];

			std::string tmp2 = mTileMap["MapGrid"][i][j];

			if (tmp2 == "X") 
				continue;
			pEntity->InitRender(spritesheetname.c_str(), ((std::string)mTileMap["MapGrid"][i][j]).c_str());
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
	case 12:
	case 11:return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Transparent);
	case 7: return sc->CreateRectEntity<RectangleEntity>(128, 128, sf::Color::Transparent);
	case 3: return sc->CreateRectEntity<Checkpoint>(128, 128, sf::Color::Transparent);
	case 5: return sc->CreateRectEntity<DeadlyObstacle>(128, 128, sf::Color::Transparent);
	case 8: return sc->CreateRectEntity<Teleporter>(128, 128, sf::Color::Transparent);
	case 9: 
	{
		Moving_Platform* pEntity = sc->CreateRectEntity<Moving_Platform>(128, 128, sf::Color::Transparent);
		pEntity->setMaxTravelDistance(128);
		pEntity->SetLinearDirection(sf::Vector2f(1,0));
		pEntity->SetStartPosition(sf::Vector2f(coX,coY));
		return pEntity;
	}
	default:
		return nullptr; // Retourne nullptr si aucun cas ne correspond
	}
}