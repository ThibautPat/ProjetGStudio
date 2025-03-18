#pragma once
#include "../StateMachine/Action.h"
#include "../Entity/RectangleEntity.h"

//--------------------------------
//Use ONLY OnEnd() !
//--------------------------------

class PuzzleAction_RectDestroy : public Action<RectangleEntity>
{
public:
	void OnStart(RectangleEntity* owner) override {};
	void OnUpdate(RectangleEntity* owner) override {};
	void OnEnd(RectangleEntity* owner) override;
};

