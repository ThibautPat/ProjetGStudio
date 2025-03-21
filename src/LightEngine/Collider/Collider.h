#pragma once

class Collider {
public:
	Collider(float xMin, float yMin, float xMax, float yMax);
	Collider(float x, float y, float radius);

	//Pk pas un sf::Rect ici ?
	float mXMin = 0.f, mYMin = 0.f;
	float mWidth = 0.f, mHeight = 0.f;
	//---------------------------

	float mX = 0.f, mY = 0.f;
	float mRadius = 0.f;

	virtual bool IsColliding(Collider* pOther, bool rigidBody = true) = 0;

	/// <summary>
	/// Update de la position du collider avant l'update de l'entity
	/// </summary>
	/// <param name="newX">Nouvelle coordonnee x au centre du collider</param>
	/// <param name="newY">Nouvelle coordonnee y au centre du collider</param>
	virtual void Update(float newX, float newY) = 0;

	void SetRect(float xMin, float yMin, float width, float height);
};

