#include "FadingTextPool.h"
#include "FadingIconText.h"
#include "FadingEmphasisText.h"
#include "Event.h"

FadingTextPool::FadingTextPool(Size capacity) :
	Pool(capacity),
	Listener(
		{
			EventType::SpawnFloatingText,
			EventType::SpawnFloatingIconText,
			EventType::SpawnFloatingEmphasisText
		}),
	WorldDrawable()
{}

void FadingTextPool::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::SpawnFloatingText:
		{
			if (this->isFull_())
			{
				return;
			}

			const EventSpawnFloatingText &castEv = static_cast<const EventSpawnFloatingText &>(ev);

			this->add_(
				new FadingText(
					castEv.getPosition(),
					castEv.getVelocity(),
					castEv.getString(),
					castEv.getFillColor(),
					castEv.getCharacterSize(),
					castEv.getDurationSecs()));
			break;
		}
		case EventType::SpawnFloatingIconText:
		{
			if (this->isFull_())
			{
				return;
			}

			const EventSpawnFloatingIconText &castEv = static_cast<const EventSpawnFloatingIconText &>(ev);

			this->add_(
				new FadingIconText(
					castEv.getPosition(),
					castEv.getVelocity(),
					castEv.getString(),
					castEv.getFillColor(),
					castEv.getCharacterSize(),
					castEv.getTextureId(),
					castEv.getDurationSecs()));
			break;
		}
		case EventType::SpawnFloatingEmphasisText:
		{
			if (this->isFull_())
			{
				return;
			}

			const EventSpawnFloatingEmphasisText &castEv = static_cast<const EventSpawnFloatingEmphasisText &>(ev);

			this->add_(
				new FadingEmphasisText(
					castEv.getPosition(),
					castEv.getVelocity(),
					castEv.getString(),
					castEv.getFillColor(),
					castEv.getCharacterSize(),
					castEv.getDurationSecs()));
			break;
		}
	}
}

void FadingTextPool::update(float deltaTime)
{
	for (Size i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime);

		if (!objects_[i]->isLive())
		{
			this->remove_(i);
		}
		else ++i;
	}
}

void FadingTextPool::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	for (Size i = 0; i < numLive_; ++i)
	{
		objects_[i]->draw(target, states, offset, scale);
	}
}