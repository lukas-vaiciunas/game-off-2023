#include "Player.h"
#include "IdlePlayerState.h"
#include "MovePlayerState.h"
#include "MoveAndHarvestPlayerState.h"
#include "HarvestPlayerState.h"
#include "MoveAndAttackPlayerState.h"
#include "AttackPlayerState.h"
#include "Map.h"
#include "Event.h"
#include "EventQueue.h"
#include "WeaponItem.h"
#include "HelmetItem.h"
#include "ChestplateItem.h"
#include "AxeItem.h"
#include "PickaxeItem.h"
#include "ItemData.h"
#include "PathFinder.h"
#include "Config.h"
#include "Constants.h"

Player::Player(
	const sf::Vector2u &coordinates,
	float speed,
	const sf::Texture &texture)
	:
	Character(coordinates, speed, texture),
	Listener(
		{
			EventType::HealPlayer,
			EventType::HurtPlayer,
			EventType::ChangePlayerWeapon,
			EventType::ChangePlayerHelmet,
			EventType::ChangePlayerChestplate,
			EventType::ChangePlayerAxe,
			EventType::ChangePlayerPickaxe,
			EventType::Harvest,
			EventType::MovePlayerAndHarvest,
			EventType::Attack,
			EventType::MovePlayerAndAttack,
			EventType::MovePlayer,
			EventType::StopPlayer,
			EventType::AddItem,
			EventType::SpawnPlayerFloatingText
		}),
	state_(new IdlePlayerState(*this)),
	weaponDamage_(1),
	helmetArmor_(0),
	chestplateArmor_(0),
	axePower_(1),
	pickaxePower_(1),
	maxHealth_(25),
	health_(25),
	attackClock_(1.0f),
	canAttack_(true)
{
	EventQueue::getInstance().send(
		new EventUpdateHealthInterface(
			health_ / static_cast<float>(maxHealth_)));
}

Player::~Player()
{
	delete state_;
}

void Player::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::HealPlayer:
			this->heal_(
				static_cast<const EventHealPlayer &>(ev).getHealth());
			break;
		case EventType::HurtPlayer:
			this->hurt_(
				static_cast<const EventHurtPlayer &>(ev).getDamage());
			break;
		case EventType::ChangePlayerWeapon:
			this->changeWeapon_(
				static_cast<const EventChangePlayerWeapon &>(ev).getItemId());
			break;
		case EventType::ChangePlayerHelmet:
			this->changeHelmet_(
				static_cast<const EventChangePlayerHelmet &>(ev).getItemId());
			break;
		case EventType::ChangePlayerChestplate:
			this->changeChestplate_(
				static_cast<const EventChangePlayerChestplate &>(ev).getItemId());
			break;
		case EventType::ChangePlayerAxe:
			this->changeAxe_(
				static_cast<const EventChangePlayerAxe &>(ev).getItemId());
			break;
		case EventType::ChangePlayerPickaxe:
			this->changePickaxe_(
				static_cast<const EventChangePlayerPickaxe &>(ev).getItemId());
			break;
		case EventType::Harvest:
		{
			delete state_;
			state_ = new HarvestPlayerState(
				*this,
				static_cast<const EventHarvest &>(ev).getResourceNode());
			break;
		}
		case EventType::MovePlayerAndHarvest:
		{
			const EventMovePlayerAndHarvest &eventMovePlayerAndHarvest = static_cast<const EventMovePlayerAndHarvest &>(ev);

			const sf::Vector2u &coordinates = eventMovePlayerAndHarvest.getCoordinates();
			const Map &map = eventMovePlayerAndHarvest.getMap();

			const std::vector<sf::Vector2u> navigableAdjacents = map.getNavigableAdjacents(coordinates);

			if (navigableAdjacents.empty())
			{
				break;
			}

			const sf::Vector2u &closestAdjacent = map.getClosestCoordinate(
				coordinate_,
				navigableAdjacents);

			const std::stack<sf::Vector2u> path = std::move(
				PathFinder::findPath(
					coordinate_,
					closestAdjacent,
					map));

			delete state_;
			state_ = new MoveAndHarvestPlayerState(
				*this,
				path,
				map.getVisibleResourceNodes().at(Coordinate(coordinates)));

			break;
		}
		case EventType::Attack:
			delete state_;
			state_ = new AttackPlayerState(
				*this,
				static_cast<const EventAttack &>(ev).getEnemy());
			break;
		case EventType::MovePlayerAndAttack:
		{
			const EventMovePlayerAndAttack &castEv = static_cast<const EventMovePlayerAndAttack &>(ev);

			delete state_;
			state_ = new MoveAndAttackPlayerState(
				*this,
				castEv.getEnemy(),
				castEv.getMap());

			break;
		}
		case EventType::MovePlayer:
		{
			const EventMovePlayer &eventMovePlayer = static_cast<const EventMovePlayer &>(ev);

			const std::stack<sf::Vector2u> path = std::move(
				PathFinder::findPath(
					coordinate_,
					eventMovePlayer.getCoordinates(),
					eventMovePlayer.getMap()));

			if (path.empty())
			{
				break;
			}

			delete state_;
			state_ = new MovePlayerState(*this, path);

			break;
		}
		case EventType::StopPlayer:
			delete state_;
			state_ = new IdlePlayerState(*this);
			break;
		case EventType::AddItem:
		{
			const EventAddItem &castEv = static_cast<const EventAddItem &>(ev);

			EventQueue::getInstance().send(
				new EventSpawnFloatingIconText(
					sf::Vector2f(
						coordinate_.x + 0.5f,
						coordinate_.y - 0.25f) * static_cast<float>(Constants::tileSize),
					sf::Vector2f(0.0f, -8.0f),
					"+" + std::to_string(castEv.getAmount()),
					sf::Color(225, 225, 225),
					Config::Text::Size::medium,
					castEv.getItemId(),
					1.25f));

			break;
		}
		case EventType::SpawnPlayerFloatingText:
		{
			const EventSpawnPlayerFloatingText &castEv = static_cast<const EventSpawnPlayerFloatingText &>(ev);

			EventQueue::getInstance().send(
				new EventSpawnFloatingText(
					sf::Vector2f(
						coordinate_.x + 0.5f,
						coordinate_.y - 0.25f) *static_cast<float>(Constants::tileSize),
					castEv.getVelocity(),
					castEv.getString(),
					castEv.getFillColor(),
					castEv.getCharacterSize(),
					castEv.getDurationSecs()));

			break;
		}
	}
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);

	state_->update(deltaTime);

	this->updateAttacking_(deltaTime);
}

void Player::updateFootstepSounds_()
{
	if (!animation_.wasUpdated())
	{
		return;
	}

	if (animation_.getCol() == 0)
	{
		EventQueue::getInstance().send(
			new EventPlaySound(
				201));
	}
	else if (animation_.getCol() == 2)
	{
		EventQueue::getInstance().send(
			new EventPlaySound(
				202));
	}
}

void Player::updateAttacking_(float deltaTime)
{
	if (canAttack_)
	{
		return;
	}

	attackClock_.update(deltaTime);

	if (attackClock_.isDone())
	{
		attackClock_.resetSoft();
		canAttack_ = true;
	}
}

void Player::attack_(Enemy &enemy)
{
	enemy.hurt(weaponDamage_);

	canAttack_ = false;
}

void Player::heal_(uint64_t health)
{
	const uint64_t maxRecovery = maxHealth_ - health_;
	const uint64_t recovery = std::min(maxRecovery, health);

	health_ += recovery;

	EventQueue &eventQueue = EventQueue::getInstance();

	eventQueue.send(
		new EventUpdateHealthInterface(
			health_ / static_cast<float>(maxHealth_)));

	eventQueue.send(
		new EventSpawnFloatingEmphasisText(
			sf::Vector2f(
				coordinate_.x + 0.5f,
				coordinate_.y - 0.25f) * static_cast<float>(Constants::tileSize),
			sf::Vector2f(0.0f, -8.0f),
			std::to_string(recovery),
			(recovery > 0
				? sf::Color(116, 180, 116)
				: sf::Color(104, 136, 204)),
			Config::Text::Size::medium,
			1.25f));
}

void Player::hurt_(uint64_t damage)
{
	EventQueue &eventQueue = EventQueue::getInstance();

	uint64_t totalArmor = helmetArmor_ + chestplateArmor_;

	if (totalArmor >= damage)
	{
		damage = 0;
	}
	else
	{
		damage -= totalArmor;
	}

	if (damage >= health_)
	{
		health_ = 0;

		eventQueue.send(
			new EventChangeDriverState(
				DriverStateType::MainMenu)); // TODO add another layer before this showing the player dying

		eventQueue.send(
			new EventPlaySound(
				101));
	}
	else
	{
		health_ -= damage;
	}

	eventQueue.send( // TODO send different sound if 0 damage
		new EventPlaySound(
			3));

	eventQueue.send(
		new EventUpdateHealthInterface(
			health_ / static_cast<float>(maxHealth_)));

	eventQueue.send(
		new EventSpawnFloatingEmphasisText(
			sf::Vector2f(
				coordinate_.x + 0.5f,
				coordinate_.y - 0.25f) * static_cast<float>(Constants::tileSize),
			sf::Vector2f(0.0f, -8.0f),
			std::to_string(damage),
			(damage > 0
				? sf::Color(208, 112, 112)
				: sf::Color(104, 136, 204)),
			Config::Text::Size::medium,
			1.25f));
}

void Player::changeWeapon_(ItemId itemId)
{
	weaponDamage_ = (itemId
		? static_cast<const WeaponItem *>(
			ItemData::getInstance().getItem(
				itemId))->getDamage()
		: 1);
}

void Player::changeHelmet_(ItemId itemId)
{
	this->setHelmetTexture_(itemId);

	helmetArmor_ = (itemId
		? static_cast<const HelmetItem *>(
			ItemData::getInstance().getItem(
				itemId))->getArmor()
		: 0);
}

void Player::changeChestplate_(ItemId itemId)
{
	this->setChestplateTexture_(itemId);

	chestplateArmor_ = (itemId
		? static_cast<const ChestplateItem *>(
			ItemData::getInstance().getItem(
				itemId))->getArmor()
		: 0);
}

void Player::changeAxe_(ItemId itemId)
{
	axePower_ = (itemId
		? static_cast<const AxeItem *>(
			ItemData::getInstance().getItem(
				itemId))->getPower()
		: 1);
}

void Player::changePickaxe_(ItemId itemId)
{
	pickaxePower_ = (itemId
		? static_cast<const PickaxeItem *>(
			ItemData::getInstance().getItem(
				itemId))->getPower()
		: 1);
}