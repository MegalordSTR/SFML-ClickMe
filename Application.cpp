#include "Application.h"
#include "FontConsts.h"
#include "ResourseHolder.h"
#include "ResourceIdentifiers.h"

#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"



#include <sstream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application() :
	window(sf::VideoMode(800, 600), "ClickMe", sf::Style::Close),
	fonts(),
	textures(),
	soundPlayer(),
	recordManager("records.json"),
	states(State::Context(window, fonts, textures, soundPlayer, recordManager)),
	frameCounter(0)
{
	window.setKeyRepeatEnabled(false);
	fonts.load(Game::Resources::Font::Main, "Media/Sansation.ttf");
	textures.load(Game::Resources::Texture::Heart, "Media/heart_full_16x16.png");
	textures.load(Game::Resources::Texture::HeartDamaged, "Media/heart_empty_16x16.png");

	textures.load(Game::Resources::Texture::BubbleBlack, "Media/Bubbles/Bubble - Black.png");
	textures.load(Game::Resources::Texture::BubbleBlue, "Media/Bubbles/Bubble - Blue.png");
	textures.load(Game::Resources::Texture::BubbleGreen, "Media/Bubbles/Bubble - Green.png");
	textures.load(Game::Resources::Texture::BubbleOrange, "Media/Bubbles/Bubble - Orange.png");
	textures.load(Game::Resources::Texture::BubblePurple, "Media/Bubbles/Bubble - Purple.png");
	textures.load(Game::Resources::Texture::BubbleRed, "Media/Bubbles/Bubble - Red.png");
	textures.load(Game::Resources::Texture::BubbleWhite, "Media/Bubbles/Bubble - White.png");
	textures.load(Game::Resources::Texture::BubbleYellow, "Media/Bubbles/Bubble - Yellow.png");

	textures.load(Game::Resources::Texture::Background, "Media/corona_up.png");
	textures.get(Game::Resources::Texture::Background).setRepeated(true);

	debugText.setFont(fonts.get(Game::Resources::Font::Main));
	debugText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::DebugInfo));
	debugText.setPosition(10, 10);
	debugText.setString("DebugInfo");

	registerStates();

	states.pushState(States::ID::Menu);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		states.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Application::update(sf::Time dt)
{
	states.update(dt);
}

void Application::render()
{
	window.clear(sf::Color::Blue);

	// States
	states.draw();

	// Debug
	window.draw(debugText);

	window.display();
}

void Application::registerStates()
{
	states.registerState<MenuState>(States::ID::Menu);
	states.registerState<GameState>(States::ID::Game);
	states.registerState<PauseState>(States::ID::Pause);
	states.registerState<GameOverState>(States::ID::GameOver);
}

void Application::updateStatistics(sf::Time dt)
{
	// Debug info
	frameCounter++;
	debugUpdateTime += dt;

	if (debugUpdateTime > sf::seconds(1.f))
	{
		std::stringstream ss;

		ss << "FPS = " << frameCounter << std::endl;
		ss << "Time per update (us) = " << (debugUpdateTime.asMicroseconds() / frameCounter) << std::endl;
		ss << std::endl;

		debugText.setString(ss.str());

		debugUpdateTime -= sf::seconds(1.f);
		frameCounter = 0;
	}
}
