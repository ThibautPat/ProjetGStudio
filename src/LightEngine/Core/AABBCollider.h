#pragma once
#include "Collider.h"
#include "SFML/System/Vector2.hpp"

class AABBCollider : public Collider
{
protected:
	sf::Vector2f mCollideFace;

public:
	AABBCollider(float xMin, float yMin, float xMax, float yMax);

	sf::Vector2f* GetCollideFace() { return &mCollideFace; }

	// Hérité via Collider
	bool IsColliding(Collider* pOther) override;
	/// <summary>
	/// Update de la position du collider avant l'update de l'entity. Reset la face de collision de la frame d'avant.
	/// </summary>
	/// <param name="newX">Nouvelle coordonnee x au centre du collider</param>
	/// <param name="newY">Nouvelle coordonnee y au centre du collider</param>
	void Update(float newX, float newY) override; //override
};

