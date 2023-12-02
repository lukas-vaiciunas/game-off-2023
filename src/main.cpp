#include "Driver.h"
#include "Config.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void detectConfig();

int main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	const sf::Color clearColor(0, 0, 0);

	detectConfig();

	sf::RenderWindow window(
		sf::VideoMode(
			Config::Window::width,
			Config::Window::height,
			Config::Window::bitsPerPixel),
		"Banished Prey",
		//sf::Style::Titlebar | sf::Style::Close
		sf::Style::Fullscreen);

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock frameClock;
	float deltaTime;

	Driver driver;

	while (window.isOpen() && !driver.isDone())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::EventType::MouseMoved:
					driver.updateOnMouseMove(ev.mouseMove.x, ev.mouseMove.y);
					break;
				case sf::Event::EventType::MouseWheelScrolled:
					driver.updateOnMouseWheelScroll(ev.mouseWheelScroll.delta);
					break;
				case sf::Event::EventType::MouseButtonPressed:
					driver.updateOnMouseButtonPress(ev.mouseButton.button);
					break;
				case sf::Event::EventType::MouseButtonReleased:
					driver.updateOnMouseButtonRelease(ev.mouseButton.button);
					break;
				case sf::Event::EventType::KeyPressed:
					driver.updateOnKeyPress(ev.key.code);
					break;
				case sf::Event::EventType::Closed:
					window.close();
					break;
			}
		}

		deltaTime = frameClock.restart().asSeconds();

		driver.update(deltaTime);

		window.clear(clearColor);
		window.draw(driver);
		window.display();
	}

	return 0;
}

void detectConfig()
{
	const sf::VideoMode desktopMode =  sf::VideoMode::getDesktopMode();

	Config::Window::width = desktopMode.width;
	Config::Window::height = desktopMode.height;
	Config::Window::bitsPerPixel = desktopMode.bitsPerPixel;

	const unsigned int windowSizeAdded = Config::Window::width + Config::Window::height;

	Config::Text::Size::small = static_cast<unsigned int>(windowSizeAdded * 0.006f);
	Config::Text::Size::medium = static_cast<unsigned int>(windowSizeAdded * 0.008f);
	Config::Text::Size::large = static_cast<unsigned int>(windowSizeAdded * 0.016f);
	Config::Text::Size::huge = static_cast<unsigned int>(windowSizeAdded * 0.024f);

	Config::World::scale = windowSizeAdded * 0.0025f;
	Config::Interface::scale = windowSizeAdded * 0.0025f;
}