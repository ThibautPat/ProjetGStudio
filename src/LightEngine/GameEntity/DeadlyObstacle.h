#pragma once
#include "../Entity/RectangleEntity.h"
class DeadlyObstacle : public RectangleEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

