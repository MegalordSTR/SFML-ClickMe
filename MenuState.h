#pragma once
#include "State.h"

#include <SFML/Graphics.hpp>

class MenuState :
    public State
{
public:
    MenuState(StateStack& stack, Context ctx);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    sf::Text menuText;
    sf::Sprite background;
};

