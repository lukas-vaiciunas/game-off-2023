#include "AudioData.h"
#include "Config.h"
#include <fstream>
#include <sstream>

AudioData::AudioData() :
	soundBuffers_(),
	musicFilePaths_()
{
	this->loadSoundBuffers_("./data/audio/sounds.txt");
	this->loadMusicFilePaths_("./data/audio/music.txt");
}

AudioData &AudioData::getInstance()
{
	static AudioData instance;
	return instance;
}

void AudioData::playMusic(MusicId id)
{
	music_.stop();

	music_.openFromFile(musicFilePaths_.at(id));

	music_.setVolume(Config::Audio::musicVolume);
	music_.setLoop(true);

	music_.play();
}

const sf::SoundBuffer &AudioData::getSoundBuffer(SoundId id) const
{
	return soundBuffers_.at(id);
}

void AudioData::loadSoundBuffers_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in AudioData::loadSoundBuffers_\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	SoundId soundId;
	std::string soundFilePath;

	while (std::getline(in, line))
	{
		ss.clear();
		ss.str(line);

		ss >> soundId >> soundFilePath;

		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromFile(soundFilePath);

		soundBuffers_.emplace(soundId, std::move(soundBuffer));
	}

	in.close();
}

void AudioData::loadMusicFilePaths_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in AudioData::loadMusicFilePaths_\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	MusicId musicId;
	std::string musicFilePath;

	while (std::getline(in, line))
	{
		ss.clear();
		ss.str(line);

		ss >> musicId >> musicFilePath;

		musicFilePaths_.emplace(musicId, musicFilePath);
	}

	in.close();
}