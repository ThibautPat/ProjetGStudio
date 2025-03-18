#include "PuzzleAction.h"

void PuzzleAction_RectDestroy::OnEnd(RectangleEntity* owner)
{
	owner->Destroy();
}
