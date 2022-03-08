#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Game
{
	namespace Resources
	{
		enum class Font
		{
			Main
		};

		const int BubbleTexturesCount = 8;

		enum class Texture
		{
			Heart,
			HeartDamaged,
			Background,
			BubbleBlack,
			BubbleBlue,
			BubbleGreen,
			BubbleOrange,
			BubblePurple,
			BubbleRed,
			BubbleWhite,
			BubbleYellow
		};

		enum class SoundEffect
		{
			BubblePop0,
			BubblePop1,
			BubblePop2,
			BubblePop3,
			SoundCount
		};
	}
}

template <typename Resource, typename Identifier>
class ResourseHolder;

typedef ResourseHolder<sf::Font, Game::Resources::Font> FontHolder;
typedef ResourseHolder<sf::Texture, Game::Resources::Texture> TextureHolder;
typedef ResourseHolder<sf::SoundBuffer, Game::Resources::SoundEffect> SoundBufferHolder;