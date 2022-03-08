#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "SoundPlayer.h"
#include "RecordManager.h"

#include <SFML/Graphics.hpp>

#include <memory>

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(
			sf::RenderWindow& window,
			FontHolder& fonts,
			TextureHolder& textures,
			SoundPlayer& soundPlayer,
			RecordManager& recordManager
		);

		sf::RenderWindow* window;

		FontHolder* fonts;
		TextureHolder* textures;
		SoundPlayer* soundPlayer;
		RecordManager* recordManager;
	};

public:

	State(StateStack& stack, Context ctx);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* stack;
	Context ctx;
};

