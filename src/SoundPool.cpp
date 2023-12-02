#include "SoundPool.h"
#include "Event.h"
#include "AudioData.h"
#include "Config.h"

SoundPool::SoundPool() :
	Pool(256),
	Listener({ EventType::PlaySound })
{}

void SoundPool::onEvent(const Event &ev)
{
	if (this->isFull_())
	{
		return;
	}

	sf::Sound *sound = new sf::Sound(
		AudioData::getInstance().getSoundBuffer(
			static_cast<const EventPlaySound &>(ev).getSoundId()));

	sound->setVolume(Config::Audio::soundVolume);

	sound->play();

	this->add_(sound);
}

void SoundPool::update()
{
	for (Size i = 0; i < numLive_; )
	{
		if (objects_[i]->getStatus() == sf::SoundSource::Status::Stopped)
		{
			this->remove_(i);
		}
		else ++i;
	}
}