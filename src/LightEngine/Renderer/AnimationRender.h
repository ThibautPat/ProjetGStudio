#pragma once

#include <vector>
#include <string>

#include "TextureRender.h"

class AnimationRender : public TextureRender
{
protected:
	int mFrameNb = 0;
	int mFrameCounter = 0;
	float mTimer = 0.f;
	float mTimePerFrame = 0.f;
	bool mIsLoop = true;
	
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

	bool IsLoop() { return mIsLoop; }

};

