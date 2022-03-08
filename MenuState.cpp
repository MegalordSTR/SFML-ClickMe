#include "MenuState.h"
#include "FontConsts.h"
#include "ResourseHolder.h"

MenuState::MenuState(StateStack& stack, Context ctx) :
    State(stack, ctx)
{
    menuText.setFont(ctx.fonts->get(Game::Resources::Font::Main));
    menuText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::StateInfo));
    sf::View view = getContext().window->getDefaultView();
    menuText.setString("Press Enter to start");
    menuText.setPosition((view.getSize().x - menuText.getLocalBounds().width) / 2, (view.getSize().y - menuText.getLocalBounds().height) / 2);

    background.setTexture(ctx.textures->get(Game::Resources::Texture::Background));
}

void MenuState::draw()
{
    getContext().window->draw(background);
    getContext().window->draw(menuText);
}

bool MenuState::update(sf::Time dt)
{
    return false;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        requestStackPop();
        requestStackPush(States::ID::Game);
    }    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        getContext().window->close();
    }
    return false;
}
