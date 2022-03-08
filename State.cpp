#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, Context ctx) :
	stack(&stack),
	ctx(ctx)
{

}

State::~State(){}

void State::requestStackPush(States::ID stateID)
{
	stack->pushState(stateID);
}

void State::requestStackPop()
{
	stack->popState();
}

void State::requestStateClear()
{
	stack->clearStates();
}

State::Context State::getContext() const
{
	return ctx;
}

State::Context::Context(
	sf::RenderWindow& window,
	FontHolder& fonts,
	TextureHolder& textures,
	SoundPlayer& soundPlayer,
	RecordManager& recordManager
) :
	window(&window),
	fonts(&fonts),
	textures(&textures),
	soundPlayer(&soundPlayer),
	recordManager(&recordManager)
{
}
