#pragma once
#include "State.h"
#include "RecordManager.h"

class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context ctx);
	virtual ~GameOverState();

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	sf::Sprite background;

	sf::Text finishText;
	sf::Text recordsText;
};

