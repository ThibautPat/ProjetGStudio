#include "Puzzle.h"
#include <iostream>

Puzzle::Puzzle(RectangleEntity* objkey, RectangleEntity* objactivable)
{
	Key* key = new Key(objkey, nullptr);
	Activable* act = new Activable(objactivable, nullptr);

	mKey = key;
	mActivable = act;

}

void Puzzle::AddCondition(Key* key, Condition<RectangleEntity>* condition, bool needtodoonetime)
{
	ConditionDone* ncondition = ((ConditionDone*)condition);
	ncondition->mNeedToDoOneTime = needtodoonetime;
	key->mCondition.push_back(ncondition);
}

void Puzzle::AddAction(Activable* act, Action<RectangleEntity>* action)
{
	act->mAction.push_back(action);
}

void Puzzle::TestConditions()
{
	if (mPuzzleIsFinished)
		return;

	mPuzzleIsFinished = true;
	for (Condition<RectangleEntity>* condition : mKey->mCondition) {
			
		if (condition->OnTest(mKey->mObject) == false) {
			mPuzzleIsFinished = false;
		}
			
	}

	if (mPuzzleIsFinished) {
		for (Action<RectangleEntity>* action : mActivable->mAction) {

			action->OnEnd(mActivable->mObject);
		}
	}
}
