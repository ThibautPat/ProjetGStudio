#include "StateMachine.h"

#include "../../Core/Other/Behaviour.h"

template<typename T>
StateMachine<T>::StateMachine(T* owner, int stateCount)
{
	mOwner = owner;
	mCurrentState = -1;
	mBehaviour.resize(stateCount);
}

template<typename T>
StateMachine<T>::~StateMachine()
{
	for (Behaviour<T>* pBehaviour : mBehaviour)
		delete pBehaviour;
}


template<typename T>
void StateMachine<T>::SetState(int state)
{
	if (mCurrentState > 0 && mCurrentState < mBehaviour.size())
		mBehaviour[mCurrentState]->End();

	mCurrentState = state;

	mBehaviour[mCurrentState]->Start();
}

template<typename T>
void StateMachine<T>::Update()
{
	if (mCurrentState == -1)
		return;

	int transitionState = mBehaviour[mCurrentState]->Update();

	if (transitionState == -1)
		return;

	SetState(transitionState);

}

template<typename T>
Behaviour<T>* StateMachine<T>::CreateBehaviour(int state)
{
	_ASSERT(state >= 0 && state < mBehaviour.size());

	Behaviour<T>* pBehaviour = new Behaviour<T>(mOwner);
	mBehaviour[state] = pBehaviour;

	return pBehaviour;
}