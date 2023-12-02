#pragma once

#include "Pool.h"
#include "Listener.h"
#include <SFML/Audio/Sound.hpp>

class SoundPool :
	public Pool<sf::Sound>,
	public Listener
{
public:
	SoundPool();

	void onEvent(const Event &ev) override;

	void update();
};