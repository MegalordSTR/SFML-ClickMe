#include "GameState.h"

GameState::GameState(StateStack& stack, Context ctx) : 
	State(stack, ctx),
	world(*ctx.window, *ctx.fonts, *ctx.textures, *ctx.soundPlayer),
	player()
{

}

GameState::~GameState()
{
}

void GameState::draw()
{
	world.draw();
}

bool GameState::update(sf::Time dt)
{
	world.update(dt);

	if (!world.checkHP())
	{
		getContext().recordManager->addRecord(RecordManager::Record{ "Admin", world.getScore() });

		requestStateClear();
		requestStackPush(States::ID::GameOver);
	}

	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.getCommandQueue();
	player.handleInputEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		requestStackPush(States::ID::Pause);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStateClear();
		requestStackPush(States::ID::Menu);
	}
	return false;
}
