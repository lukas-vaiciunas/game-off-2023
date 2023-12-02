#include "PlayDriverState.h"
#include "TextureData.h"
#include "AudioData.h"
#include "Config.h"

PlayDriverState::PlayDriverState() :
	player_(
		sf::Vector2u(
			static_cast<uint32_t>(Constants::Map::width * 0.5f),
			static_cast<uint32_t>(Constants::Map::height * 0.5f)),
		32.0f,
		TextureData::getInstance().getTexture(1)),
	map_(),
	tileSelector_(map_),
	camera_(),
	hunterEnemySpawner_(),
	eyeball_(
		sf::Vector2f(
			4.0f,
			4.0f)),
	equipment_(),
	inventory_(equipment_),
	inventoryInterface_(
		sf::Vector2f(
			Config::Window::width * 0.8f,
			Config::Window::height * 0.5f) / Config::Interface::scale,
		inventory_,
		equipment_),
	crafting_(),
	craftingInterface_(
		sf::Vector2f(
			Config::Window::width * 0.2f,
			Config::Window::height * 0.5f) / Config::Interface::scale,
		crafting_,
		inventory_),
	healthInterface_(
		sf::Vector2f(
			4.0f,
			Config::Window::height / Config::Interface::scale - 6.5f)),
	fadingTextPool_(100),
	particlePool_(100)
{
	map_.updateVisibility(player_.getCoordinate());
	camera_.center(player_.getCenterPosition());

	AudioData::getInstance().playMusic(2);
}

void PlayDriverState::update(float deltaTime)
{
	map_.update(deltaTime, player_.getCoordinate());

	tileSelector_.update(deltaTime, camera_.getPosition());

	player_.update(deltaTime);

	camera_.center(player_.getCenterPosition());

	hunterEnemySpawner_.update(deltaTime);

	eyeball_.update(deltaTime);
	inventoryInterface_.update(deltaTime);
	craftingInterface_.update(deltaTime);

	fadingTextPool_.update(deltaTime);
	particlePool_.update(deltaTime);
}

void PlayDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	const sf::Vector2f mousePosition(
		static_cast<float>(mouseX),
		static_cast<float>(mouseY));

	const sf::Vector2f mouseInterfacePosition = mousePosition / Config::Interface::scale;

	tileSelector_.updateOnMouseMove(mousePosition / Config::World::scale);

	eyeball_.updateOnMouseMove(mouseInterfacePosition);
	inventoryInterface_.updateOnMouseMove(mouseInterfacePosition);
	craftingInterface_.updateOnMouseMove(mouseInterfacePosition);
}

void PlayDriverState::updateOnMouseWheelScroll(float delta)
{
	inventoryInterface_.updateOnMouseWheelScroll(delta);
	craftingInterface_.updateOnMouseWheelScroll(delta);
}

void PlayDriverState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (inventoryInterface_.isHovered())
	{
		inventoryInterface_.updateOnMouseButtonPress(button);
	}
	else if (craftingInterface_.isHovered())
	{
		craftingInterface_.updateOnMouseButtonPress(button);
	}
	else if (eyeball_.isHovered())
	{
		eyeball_.updateOnMouseButtonPress(button);
	}
	else
	{
		tileSelector_.updateOnMouseButtonPress(button);
	}
}

void PlayDriverState::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (inventoryInterface_.isHovered())
	{
		inventoryInterface_.updateOnMouseButtonRelease(button);
	}
	else if (craftingInterface_.isHovered())
	{
		craftingInterface_.updateOnMouseButtonRelease(button);
	}
	else if (eyeball_.isHovered())
	{
		eyeball_.updateOnMouseButtonRelease(button);
	}
}

void PlayDriverState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::I)
	{
		inventoryInterface_.toggle();
	}
	else if (key == sf::Keyboard::Key::C)
	{
		craftingInterface_.toggle();
	}
}

void PlayDriverState::draw(
	sf::RenderTarget &target,
	sf::RenderStates states) const
{
	const sf::Vector2f worldOffset = -camera_.getPosition();

	const sf::Vector2f worldScale(
		Config::World::scale,
		Config::World::scale);

	const sf::Vector2f interfaceScale(
		Config::Interface::scale,
		Config::Interface::scale);

	std::multimap<Coordinate, const WorldDrawable *> sortedWorldDrawables;

	const std::unordered_map<Coordinate, Tile *> &visibleTiles = map_.getVisibleTiles();
	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = map_.getVisibleResourceNodes();
	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = map_.getVisibleCamperEnemies();
	const HunterEnemyPool &hunterEnemyPool = map_.getHunterEnemyPool();

	sortedWorldDrawables.insert(visibleResourceNodes.begin(), visibleResourceNodes.end());
	sortedWorldDrawables.insert(visibleCamperEnemies.begin(), visibleCamperEnemies.end());

	for (auto it = hunterEnemyPool.begin(); it != hunterEnemyPool.end(); ++it)
	{
		sortedWorldDrawables.emplace((*it)->getCoordinate(), *it);
	}

	sortedWorldDrawables.emplace(player_.getCoordinate(), &player_);

	for (auto it = visibleTiles.begin(); it != visibleTiles.end(); ++it)
	{
		it->second->draw(target, states, worldOffset, worldScale);
	}

	particlePool_.draw(target, states, worldOffset, worldScale); // TODO maybe background sorted particle pool and foreground one
	
	for (auto it = sortedWorldDrawables.begin(); it != sortedWorldDrawables.end(); ++it)
	{
		it->second->draw(target, states, worldOffset, worldScale);
	}
	
	tileSelector_.draw(target, states, worldOffset, worldScale);
	fadingTextPool_.draw(target, states, worldOffset, worldScale);

	eyeball_.draw(target, states, interfaceScale);
	healthInterface_.draw(target, states, interfaceScale);
	inventoryInterface_.draw(target, states, interfaceScale);
	craftingInterface_.draw(target, states, interfaceScale);
}