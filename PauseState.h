#pragma once
#include "State.h"

#include <SFML/Graphics.hpp>

class PauseState :
    public State
{
public :
    PauseState(StateStack& stack, Context ctx);

    // Inherited via State
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    sf::Text pauseText;
};

