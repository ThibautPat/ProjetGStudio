#pragma once
#include "../Entity/RectangleEntity.h"
class Checkpoint : public RectangleEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

