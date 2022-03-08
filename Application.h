#pragma once
#include "StateStack.h"
#include "StateIdentifiers.h"
#include "ResourseHolder.h"
#include "SoundPlayer.h"
#include "RecordManager.h"

#include <SFML/Graphics.hpp>


class Application
{
public:
	explicit Application();
	void run();

private:
	void processInput();
	void update(sf::Time dt);
	void render();

	void registerStates();

	void updateStatistics(sf::Time dt);

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow window;
	StateStack states;

	FontHolder fonts;
	TextureHolder textures;
	SoundPlayer soundPlayer;
	RecordManager recordManager;

	sf::Text debugText;
	sf::Time debugUpdateTime;
	std::size_t frameCounter;
};

