#pragma once

#include <iostream>
#include "../Library/json.hpp"

using json = nlohmann::json;

class Entity;

class Level
{
	int coX = 0;
	int coY = 0;
protected:
	json mTileMap;
	json mEnv;

public:
	void ChooseJson(const char* path, const char* envipath);

	void LoadLevel();

	void AddPlayer();
	void AddEnvironment();
	void AddTiles();



	Entity* CreateNewEnity(const char* id);

	//template <typename T>
	//T* CreateNewEnity(const char* id);
};

#include "Level.inl"

