#pragma once
#include <vector>
#include <string>
#include "TextureRender.h"

class AnimationRender : public TextureRender
{
protected:
	int mFrameNb;
	int mFrameCounter = 0;
	float mTimer = 0.f;
	float mTimePerFrame;
	float mAnimSpeed = 1.f;

	int mOgx;
	bool mIsFinished = false;
	bool mIsLoop;
	
public:

	/// <summary>
	/// Defini les proprietees de l'animation grace a la SpriteSheet et au nom de l'animation
	/// </summary>
	/// <param name="spritesheetname">: Nom de la SpriteSheet</param>
	/// <param name="spritename">: Nom de l'animation</param>
	AnimationRender(const char* spritesheetname, const char* spritename);

	/// <summary>
	/// Gere le changement du masque (et donc de la frame)
	/// </summary>
	void UpdateAnimation();

	void SetFrameCounter(int frame) { mFrameCounter = 0; }
	void SetIsFinished(bool value) { mIsFinished = value; }
	void SetAnimationSpeed(int speed) { mAnimSpeed = speed; }

	bool IsLoop() { return mIsLoop; }
};

