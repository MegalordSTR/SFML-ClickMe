#pragma once
#include "SceneNode.h"

#include <unordered_map>

#include <SFML/System/NonCopyable.hpp>

namespace Game
{
	enum class Layer : int
	{
		World = 0,
		Sound = 1
	};
}

class SceneManager : private sf::NonCopyable
{
public:
	explicit SceneManager();
	~SceneManager();

	void addLayer(Game::Layer layer);
	SceneNode& getLayer(Game::Layer layer);

private:
	std::unordered_map<Game::Layer, std::shared_ptr<SceneNode>> layers;
};

