#pragma once
#include "../Entity/RectangleEntity.h"
class BackGround : public RectangleEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetBackGroundTexture(std::string path);
};

