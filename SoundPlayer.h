#pragma once
#include "ResourseHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Audio.hpp>

#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
	SoundPlayer();

	void play(Game::Resources::SoundEffect id);

	void removeStoppedSounds();

private:
	SoundBufferHolder soundBuffers;

	std::list<sf::Sound> playingSounds;
};

