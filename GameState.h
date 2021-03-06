#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"

class GameState :
    public State
{
public:
	GameState(StateStack& stack, Context ctx);
	virtual ~GameState();

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	World world;
	Player player;
};

