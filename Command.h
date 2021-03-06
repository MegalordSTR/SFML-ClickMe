#pragma once
#include "CategoryIdentifiers.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
	typedef std::function<void(SceneNode&, sf::Time)> Action;

	Command(Action fn, Game::CategoryType category);
	Action action;
	Game::CategoryType category;
};

template<typename GameObject, typename Function>
Command::Action derrivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}