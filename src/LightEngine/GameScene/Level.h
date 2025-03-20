#pragma once

#include <iostream>
#include "../Library/json.hpp"

using json = nlohmann::json;

class Entity;

class Level
{
protected:
	json mMap;

public:
	void ChooseJson(const char* path);

	void LoadLevel();

	Entity* CreateNewEnity(const char* id);

	//template <typename T>
	//T* CreateNewEnity(const char* id);
};

#include "Level.inl"

