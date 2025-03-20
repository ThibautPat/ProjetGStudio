#pragma once
#include "../Entity/RectangleEntity.h"
class Checkpoint : public RectangleEntity
{
protected:
	bool mIsActivated = false;
public:
	void OnInitialize() override;
	void OnUpdate() override;
};

