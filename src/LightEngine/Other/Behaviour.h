#pragma once

#include <vector>

template<typename T>
class Action;

template<typename T>
class Transition;

template<typename T>
class Behaviour
{
    std::vector<Action<T>*> mActions;
    T* mOwner;

    std::vector<Transition<T>*> mTransitions;

public:

    Behaviour(T* owner);
    ~Behaviour();

    void Start();
    int Update();
    void End();

    template<typename U>
    U* AddAction();

    Transition<T>* CreateTransition(int state);
};

#include "Behaviour.inl"