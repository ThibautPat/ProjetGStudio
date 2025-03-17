#pragma once
#include "../../Core/Entity/RectangleEntity.h"
class DeadlyObstacle : public RectangleEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

