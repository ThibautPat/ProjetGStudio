#pragma once

#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"

class CameraMan
{
protected:
	sf::Vector2f mDest;
public:
	CameraMan() { mDest = sf::Vector2f(0, 0); }


	//#TODO remove view* and add in local var
	void Update(sf::View* view);

	void Zoom(sf::View* view, float offsetx, float offsety);
	void GoTo(sf::Vector2f& dest) { mDest = dest; }

};

