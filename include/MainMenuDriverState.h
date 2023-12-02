#pragma once

#include "DriverState.h"
#include "MainMenuBackdrop.h"
#include "MainMenuTitleText.h"
#include "TextButton.h"

class MainMenuDriverState : public DriverState
{
public:
	MainMenuDriverState();

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;

	void draw(
		sf::RenderTarget &target,
		sf::RenderStates states) const override;
private:
	MainMenuBackdrop backdrop_;

	MainMenuTitleText titleText_;

	TextButton playButton_;
	TextButton quitButton_;

	InterfaceText watermark_;
};