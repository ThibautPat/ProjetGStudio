#pragma once
#include <map>
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

class AnimationRender;

class Animator 
{
protected:
	std::map<std::string, AnimationRender*> mAnimMap;

	
	AnimationRender* mCurrentAnim = nullptr;

	sf::Vector2f mRatio;

public:
	Animator() { mRatio = sf::Vector2f(1, 1); }

	void AddAnimation(const char* spritesheetname, const char* spritename);

	void SetCurrentAnimation(std::string& spritename);
	void SetRatio(sf::Vector2f nratio);
	AnimationRender* GetCurrentAnimation() { return mCurrentAnim; }

	void UpdateCurrentAnimation();
};

