#include "GameOverState.h"
#include "FontConsts.h"

#include <SFML/Graphics.hpp>

#include <sstream>

GameOverState::GameOverState(StateStack& stack, Context ctx) :
	State(stack, ctx),
	finishText()
{
	background.setTexture(ctx.textures->get(Game::Resources::Texture::Background));

	finishText.setFont(getContext().fonts->get(Game::Resources::Font::Main));
	finishText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::StateInfo));
	finishText.setString("           Game Over\nPress Esc to Enter Menu");
	sf::View view = getContext().window->getDefaultView();
	finishText.setPosition((view.getSize().x - finishText.getLocalBounds().width) / 2, (view.getSize().y - finishText.getLocalBounds().height) / 5);

	std::vector<RecordManager::Record> records = getContext().recordManager->getRecords();

	recordsText.setFont(getContext().fonts->get(Game::Resources::Font::Main));
	recordsText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::PlayerInfo));

	std::stringstream recordsTextSS;
	recordsTextSS << "Best Score" << std::endl;
	for (int i = 0; i < 6 && i < records.size(); i++)
	{
		recordsTextSS << records[i].name << "  " << records[i].score << std::endl;
	}
	recordsText.setString(recordsTextSS.str());
	recordsText.setPosition((view.getSize().x - recordsText.getLocalBounds().width) / 2, (view.getSize().y - recordsText.getLocalBounds().height) / 2);

}

GameOverState::~GameOverState()
{
}

void GameOverState::draw()
{
	getContext().window->draw(background);
	getContext().window->draw(finishText);
	getContext().window->draw(recordsText);
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
		requestStackPush(States::ID::Menu);
	}
	return false;
}
