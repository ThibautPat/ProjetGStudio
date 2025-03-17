#include "MenuButton.h"
#include "../Core/GameManager.h"

#include "TestScene.h"
MenuButton::MenuButton()
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::SetPosition(float x, float y)
{
	mShape.setPosition(x, y);
	mText.setPosition(mShape.getGlobalBounds().width/2, mShape.getGlobalBounds().height/2);
}

void MenuButton::SetButtonSize(float width, float height)
{
	mShape.setSize(sf::Vector2f(width, height));

	mText.setPosition(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);
}

void MenuButton::SetText(std::string text)
{
	mText.setString(text);
}

void MenuButton::SetTextColor(sf::Color color)
{
	mText.setFillColor(color);
}

void MenuButton::SetFont(std::string fontPath)
{
	mFont.loadFromFile(fontPath);
	mText.setFont(mFont);
}

void MenuButton::SetCharacterSize(int size)
{
	mText.setCharacterSize(size);
}

void MenuButton::SetTextPosition(float x, float y)
{
	mText.setPosition(x, y);
}

void MenuButton::SetButtonColor(sf::Color color)
{
	mShape.setFillColor(color);
}

bool MenuButton::IsClicked(sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window); 
	sf::Vector2f mousePositionF = sf::Vector2f((float)mousePosition.x, (float)mousePosition.y); 

	if (mShape.getGlobalBounds().contains(mousePositionF)) 
	{
		return true;
	}
	return false;
}

void MenuButton::OnInitialize()
{

}

void MenuButton::OnUpdate()
{
	if (IsClicked(*GameManager::Get()->GetWindow()))
	{
		mShape.setFillColor(sf::Color::Green);
	}
	else
	{
		mShape.setFillColor(sf::Color::Red);
	}
}
