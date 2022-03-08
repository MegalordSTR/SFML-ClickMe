#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() :
	soundBuffers(),
	playingSounds()
{
	soundBuffers.load(Game::Resources::SoundEffect::BubblePop0, "Media/pop.ogg");
	soundBuffers.load(Game::Resources::SoundEffect::BubblePop1, "Media/pop1.ogg");
	soundBuffers.load(Game::Resources::SoundEffect::BubblePop2, "Media/pop2.ogg");
	soundBuffers.load(Game::Resources::SoundEffect::BubblePop3, "Media/pop3.ogg");
}

void SoundPlayer::play(Game::Resources::SoundEffect id)
{
	const sf::SoundBuffer& buffer = soundBuffers.get(id);

	playingSounds.push_back(sf::Sound(buffer));
	sf::Sound& sound = playingSounds.back();
	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	playingSounds.remove_if([](const sf::Sound& sound) {
		return static_cast<int>(sound.getStatus()) == static_cast<int>(sf::Sound::Stopped);
	});
}
