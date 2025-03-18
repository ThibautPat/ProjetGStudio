#include "Scene.h"


#include "../Manager/GameManager.h"

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

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}
