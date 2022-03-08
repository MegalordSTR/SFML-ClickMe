#pragma once
#include "CommandQueue.h"

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();

	void handleInputEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
};

