#pragma once
#include "../Entity/RectangleEntity.h"
class Teleporter : public RectangleEntity
{

public:
	void OnInitialize() override;
	void OnUpdate() override;
};

