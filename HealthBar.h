#pragma once
#include "SceneNode.h"
#include "ResourseHolder.h"
#include "ResourceIdentifiers.h"

#include "SFML/Graphics.hpp"

#include <vector>
#include <memory>

class HealthBar : public SceneNode
{
public:
	HealthBar(int32_t startHP, TextureHolder& textures, const sf::Vector2f upperLeftCorner);

	void update(sf::Time dt, CommandQueue& commands);
	void onCommand(const Command& command, sf::Time dt);

	virtual bool isMarkedForRemoval() const;

	void damage(int32_t damage);
	int32_t getHP();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	TextureHolder& textures;

	std::vector<std::unique_ptr<sf::Sprite>> hearts;
	size_t hp;

	sf::Vector2f textureScaleFactor;
};

