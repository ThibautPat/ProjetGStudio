#pragma once

#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"

//Le bug de camera au lancement du programme doit être du au temps de tout initialiser
class CameraMan
{
protected:
	//Pointeur vers la view de la scene
	sf::View* mView;
	//Taille originale de la view (pour reset le zoom)
	sf::Vector2f mOriginalSize;
	//Destination vers laquelle se dirige la camera 
	sf::Vector2f mDest;
	//Vitesse modifiee a chaque boucle afin de suivre proprement le mDest
	float mFollowSpeed = 0.f;
	//Facteur qui multiplie la vitesse de suivi de la camera
	float mCamSpeed = 1.f;

public:
	CameraMan() { mDest = sf::Vector2f(0, 0); mView = nullptr; }

	void SetView(sf::View* view);
	/// <summary>
	/// Defini le multiplicateur de vitesse (defaut =1)
	/// </summary>
	/// <param name="speed">Nouveau facteur vitesse</param>
	void SetSpeed(float speed) { mCamSpeed = speed; }

	/// <summary>
	/// Appeler au debut de chaque update du game manager (gere le CameraMan::GoTo(sf::Vector2f&))
	/// </summary>
	void Update();

	/// <summary>
	/// Zoom par rapport a la taille actuelle de la camera et sa position
	/// </summary>
	/// <param name="offsetx">facteur de taille en x</param>
	/// <param name="offsety">facteur de taille en y</param>
	void Zoom(float offsetx, float offsety);
	/// <summary>
	/// Set un zoom par rapport a la taille originale de la camera (defini lors de l'assignation avec CameraMan::SetView(sf::View*)) et sa position actuelle
	/// </summary>
	/// <param name="offsetx">facteur de taille en x</param>
	/// <param name="offsety">facteur de taille en y</param>
	void SetZoom(float offsetx, float offsety);
	/// <summary>
	/// Glisse vers une position grace a CameraMan::Update()
	/// </summary>
	/// <param name="dest">Point de destination</param>
	void GoTo(sf::Vector2f& dest);

};

