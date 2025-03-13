#pragma once
#include "SFML/Graphics.hpp"

#include "../Core/RectangleEntity.h"
class CheckPoint : public RectangleEntity
{
public:

	void OnInitialize() override;
	void OnUpdate() override;
};

