#include "Level.h"
#include "../Core/Utils.h"
#include "../Game/Player.h"
#include "../Game/TestScene.h"

void Level::ChooseJson(const char* path)
{
	mMap = *Utils::Parse(path);
}

void Level::LoadLevel()
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();

	for (int i = 0; i < mMap["Rows"]; i++) {
		for (int j = 0; j < mMap["Columns"]; j++) {

			std::string tmp = mMap["Cases"][i][j];
			//mMap["Cases"][0][0] = "PL" for 

			Entity* pEntity = CreateNewEnity(tmp.c_str());
			pEntity->SetGravity((bool)mMap[tmp]["Gravity"]);
			pEntity->SetRigidBody((bool)mMap[tmp]["RigidBody"]);
			pEntity->SetIsKinematic((bool)mMap[tmp]["IsKinematic"]);
			pEntity->SetTag((int)mMap[tmp]["Tag"]);
			pEntity->SetPosition(100 * j, 100 * i);
		}
	}

	RectangleEntity* Ground = sc->CreateRectEntity<RectangleEntity>(5000, 10000, sf::Color::Green);
	Ground->SetPosition(0, 3850);
	Ground->SetRigidBody(true);
	Ground->SetIsKinematic(true);
	Ground->SetGravity(false);
	Ground->SetTag(TestScene::Tag::OBSTACLE);
}

Entity* Level::CreateNewEnity(const char* id)
{
	Scene* sc = GameManager::Get()->GetSceneManager()->GetScene();
	int name = std::atoi(id);

	switch (name)
	{
	case 0:
		return sc->CreateRectEntity<Player>(128, 256, sf::Color::Blue);;
		break;
	default:
		break;
	}
}
