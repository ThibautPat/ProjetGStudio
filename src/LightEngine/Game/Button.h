#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Core/RectangleEntity.h"
class Button : public RectangleEntity
{
protected:
	sf::RectangleShape mShape;
	sf::Text mText;
	sf::Font mFont;
public:

	Button();
	~Button();

	virtual void SetPosition(float x, float y) = 0;
	virtual void SetButtonSize(float width, float height) = 0;
	virtual void SetText(std::string text) = 0;
	virtual void SetTextColor(sf::Color color) = 0;
	virtual void SetFont(std::string fontPath) = 0;
	virtual void SetCharacterSize(int size) = 0;
	virtual void SetTextPosition(float x, float y) = 0;
	virtual void SetButtonColor(sf::Color color) = 0;

	virtual bool IsClicked(sf::RenderWindow& window) = 0;
};

