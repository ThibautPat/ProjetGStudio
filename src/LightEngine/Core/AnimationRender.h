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

	//AnimationRender(std::string& spritesheetname, std::string& spritename);

	//void Update();


	/// <summary>
	/// Cree une Animation avec un nombre de frame, le nom de la texture (deja chargee dans le TextureManager), et un masque (zone selectionnee de la texture)
	/// </summary>
	/// <param name="frameNb">Nombre de frames (qui seront jouees en une seconde)</param>
	/// <param name="textName">Nom de la texture dans la bibliotheque du TextureManager</param>
	/// <param name="rect">Zone de la texture selectionnee pour le rendu</param>
	AnimationRender(int frameNb, const char* textName, sf::IntRect rect);

	/// <summary>
	/// Gere le changement du masque (et donc de la frame)
	/// </summary>
	void UpdateAnimation();

	bool IsLoop() { return mIsLoop; }

};

