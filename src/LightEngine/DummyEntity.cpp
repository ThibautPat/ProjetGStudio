#include "DummyEntity.h"

#include <iostream>

void DummyEntityRect::OnCollision(Entity* other)
{
	std::cout << "DummyEntityRect::OnCollision" << std::endl;
}

void DummyEntityCircle::OnCollision(Entity* other)
{
	std::cout << "DummyEntityCircle::OnCollision" << std::endl;
}