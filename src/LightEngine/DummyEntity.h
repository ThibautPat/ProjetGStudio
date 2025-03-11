#pragma once
//#include "Moteur/CircleEntity.h"
#include "Moteur/RectangleEntity.h"

class DummyEntity : public RectangleEntity
{
public:
	void OnCollision(Entity* other) override;
};

