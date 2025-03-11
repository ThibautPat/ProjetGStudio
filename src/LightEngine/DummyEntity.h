#pragma once
#include "Moteur/CircleEntity.h"
#include "Moteur/RectangleEntity.h"

class DummyEntityRect : public RectangleEntity
{
public:
	void OnCollision(Entity* other) override;
};

class DummyEntityCircle : public CircleEntity
{
public:
	void OnCollision(Entity* other) override;
}; 
