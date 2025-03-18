#pragma once
#include "../Entity/RectangleEntity.h"
#include "../StateMachine/Condition.h"
#include "../StateMachine/Action.h"

struct ConditionDone : public Condition<RectangleEntity> {
	bool mDoneOneTime = false;
	bool mNeedToDoOneTime = false;
};

struct Key {
	RectangleEntity* mObject;
	std::vector<ConditionDone*> mCondition;

	Key(RectangleEntity* obj, ConditionDone* condition) { mObject = obj;  if (condition) { mCondition.push_back(condition); } }
};
struct Activable {
	RectangleEntity* mObject;
	std::vector< Action<RectangleEntity>* > mAction;

	Activable(RectangleEntity* obj, Action<RectangleEntity>* action) { mObject = obj;  if (action) { mAction.push_back(action); } }
};

class Puzzle
{
protected:

	Key* mKey;
	Activable* mActivable;
	bool mPuzzleIsFinished = false;

public:

	/// <summary>
	/// Recupere la structure de l'activateur = boutton (objet et conditions)
	/// </summary>
	/// <returns></returns>
	Key* GetKey() { return mKey; }
	/// <summary>
	/// Recupere la structure de l'activable = laser (objet et actions)
	/// </summary>
	/// <returns></returns>
	Activable* GetActivable() { return mActivable; }

	/// <summary>
	/// Cree un puzzle avec un activateur (sans condition) et un activable (sans action).
	/// /!\ Un puzzle sans condition est considere comme complete
	/// </summary>
	/// <param name="objkey">: Entity qui sera l'activateur (n'a pas necessairement besoin d'etre utilisee dans les conditions)</param>
	/// <param name="objactivable">: Entity qui sera l'activable (n'a pas necessairement besoin d'etre utilisee dans les actions)</param>
	Puzzle(RectangleEntity* objkey, RectangleEntity* objactivable);

	/// <summary>
	/// Ajoute une condition a l'activateur
	/// </summary>
	/// <param name="key">: Activateur du puzzle</param>
	/// <param name="condition">: Condition (herite de Condition puis de ConditionDone)</param>
	/// <param name="needtodoonetime">: si = true, la condition est marquee comme faite (jusqu'a la fin du puzzle) lorsqu'elle est accomplie</param>
	void AddCondition(Key* key, Condition<RectangleEntity>* condition, bool needtodoonetime = false);
	/// <summary>
	/// Ajoute une action a l'activable
	/// </summary>
	/// <param name="act">: Activable du puzzle</param>
	/// <param name="action">: Action (herite de Action)</param>
	void AddAction(Activable* act, Action<RectangleEntity>* action);

	/// <summary>
	/// Verifie si les conditions sont remplies. Si elles sont correctement completees, la fonction effectue les actions necessaires
	/// </summary>
	void TestConditions();

};

