#include "MainMenuDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "AudioData.h"
#include "Config.h"

MainMenuDriverState::MainMenuDriverState() :
	DriverState(),
	backdrop_(),
	titleText_(
		sf::Vector2f(
			Config::Window::width * 0.5f,
			Config::Window::height * 0.25f)),
	playButton_(
		sf::Vector2f(
			Config::Window::width * 0.5f,
			Config::Window::height * 0.7f) / Config::Interface::scale,
		"Play",
		Config::Text::Size::large),
	quitButton_(
		sf::Vector2f(
			Config::Window::width * 0.5f,
			Config::Window::height * 0.7f + Config::Text::Size::large * 1.25f) / Config::Interface::scale,
		"Quit",
		Config::Text::Size::large),
	watermark_()
{
	watermark_.setString("Created by Lukas Vaiciunas");
	watermark_.setCharacterSize(Config::Text::Size::medium);
	watermark_.setFillColor(sf::Color(225, 225, 225));
	watermark_.setOutlineColor(sf::Color(0, 0, 0));
	watermark_.setInterfacePosition(
		sf::Vector2f(
			Config::Window::width * 0.5f / Config::Interface::scale,
			Config::Window::height / Config::Interface::scale - 2.0f));

	const sf::FloatRect watermarkLocalBounds = watermark_.getLocalBounds();

	watermark_.setOrigin(
		watermarkLocalBounds.left + watermarkLocalBounds.width * 0.5f,
		watermarkLocalBounds.top + watermarkLocalBounds.height);

	AudioData::getInstance().playMusic(1);
}

void MainMenuDriverState::update(float deltaTime)
{
	backdrop_.update(deltaTime);
	playButton_.update(deltaTime);
	quitButton_.update(deltaTime);
}

void MainMenuDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	const sf::Vector2f mousePosition(
		static_cast<float>(mouseX),
		static_cast<float>(mouseY));

	const sf::Vector2f mouseInterfacePosition(mousePosition / Config::Interface::scale);

	playButton_.updateOnMouseMove(mouseInterfacePosition);
	quitButton_.updateOnMouseMove(mouseInterfacePosition);
}

void MainMenuDriverState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	playButton_.updateOnMouseButtonPress(button);
	quitButton_.updateOnMouseButtonPress(button);
}

void MainMenuDriverState::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	playButton_.updateOnMouseButtonRelease(button);
	quitButton_.updateOnMouseButtonRelease(button);

	if (playButton_.isHovered())
	{
		EventQueue::getInstance().send(
			new EventChangeDriverState(
				DriverStateType::Play));
	}
	else if (quitButton_.isHovered())
	{
		EventQueue::getInstance().send(
			new EventQuit());
	}
}

void MainMenuDriverState::draw(
	sf::RenderTarget &target,
	sf::RenderStates states) const
{
	const sf::Vector2f interfaceScale(
		Config::Interface::scale,
		Config::Interface::scale); // TODO make this into a private member

	backdrop_.draw(target, states, interfaceScale);

	titleText_.draw(target, states, interfaceScale);

	playButton_.draw(target, states, interfaceScale);
	quitButton_.draw(target, states, interfaceScale);

	watermark_.draw(target, states, interfaceScale);
}