#include "Scene.h"
#include "../Manager/GameManager.h"
#include "../Puzzle/Puzzle.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

bool Scene::UpdateStartTimer()
{
	float dt = mpGameManager->GetDeltaTime();

	if (mStartTimerProgress >= mStartTimer)
		return true;

	mStartTimerProgress += dt;
	return false;
}

void Scene::UpdatePuzzle()
{
	for (Puzzle* puzzle : mTabPuzzle) {
		puzzle->TestConditions();
	}
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}
