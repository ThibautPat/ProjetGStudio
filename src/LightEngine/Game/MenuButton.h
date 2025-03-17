#pragma once
#include "Button.h"
class MenuButton : public Button
{
public:
	MenuButton();
	~MenuButton();

	void SetPosition(float x, float y) override;
	void SetButtonSize(float width, float height) override;
	void SetText(std::string text) override;
	void SetTextColor(sf::Color color) override;
	void SetFont(std::string fontPath) override;
	void SetCharacterSize(int size) override;
	void SetTextPosition(float x, float y) override;
	void SetButtonColor(sf::Color color) override;
	
	bool IsClicked(sf::RenderWindow& window) override;

	void OnInitialize() override;
	void OnUpdate() override; 
};

