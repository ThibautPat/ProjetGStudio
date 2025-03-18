#pragma once
#include "../Core/RectangleEntity.h"
class Teleporter : public RectangleEntity
{

public:
	void OnInitialize() override;
	void OnUpdate() override;
};

