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

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}

Scene::~Scene()
{
    delete mpGameManager;
    for (auto it = m_soundList.begin(); it != m_soundList.end();) {
        delete* it;
        it = m_soundList.erase(it);
    }
    for (auto it = m_MusicList.begin(); it != m_MusicList.end();) {
        delete* it;
        it = m_MusicList.erase(it);
    }
}