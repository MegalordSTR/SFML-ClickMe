#include "PauseState.h"
#include "FontConsts.h"
#include "ResourseHolder.h"

PauseState::PauseState(StateStack& stack, Context ctx) :
    State(stack, ctx)
{
    pauseText.setFont(ctx.fonts->get(Game::Resources::Font::Main));
    pauseText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::StateInfo));
    sf::View view = getContext().window->getDefaultView();
    pauseText.setString("Press P to unpause");
    pauseText.setPosition((view.getSize().x - pauseText.getLocalBounds().width) / 2, (view.getSize().y - pauseText.getLocalBounds().height) / 2);
}

void PauseState::draw()
{
    getContext().window->draw(pauseText);
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
        requestStackPop();
    }
    return false;
}
