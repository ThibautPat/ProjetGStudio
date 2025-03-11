#pragma once

#include "Scene.h"

class DummyEntityRect;
class DummyEntityCircle;

class SampleScene : public Scene
{
	DummyEntityRect* pEntity1;
	DummyEntityRect* pEntity2;

	DummyEntityCircle* pEntity3;
	DummyEntityCircle* pEntity4;

	DummyEntityRect* pEntitySelected;
	DummyEntityCircle* pEntitySelected2;

private:
	void TrySetSelectedEntity(DummyEntityRect* pEntity, int x, int y);
	void TrySetSelectedEntity(DummyEntityCircle* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};