#pragma once
#include "../Core/RectangleEntity.h"
class Checkpoint : public RectangleEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

