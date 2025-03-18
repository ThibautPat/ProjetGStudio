#pragma once
#include "../Puzzle/Puzzle.h"

//--------------------------------
//See example at "PuzzleCondition_PlayerIsTouched::OnTest"
//--------------------------------

class PuzzleCondition_PlayerIsTouched : public ConditionDone
{
public:
	bool OnTest(RectangleEntity* owner) override;
};

class PuzzleCondition_PlayerUpTo500y : public ConditionDone
{
public:
	bool OnTest(RectangleEntity* owner) override;
};

