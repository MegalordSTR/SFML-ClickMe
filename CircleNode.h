#pragma once
#include "SceneNode.h"
#include "TextNode.h"
#include "ResourseHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

class CircleNode : public SceneNode
{
public:
	explicit CircleNode(
		float radius,
		Game::Resources::Texture bubbleTexture,
		const TextureHolder& textures,
		const sf::FloatRect& bounds,
		const FontHolder& fonts,
		float velocity = 100
	);

	~CircleNode();
public:
	void setBounds(const sf::FloatRect& bounds);
	bool intersects(const sf::Vector2f point) const;

	void destroy();
	bool isDestroyed();

	bool isTimeExeeded();

	void markToRemove();
	virtual bool isMarkedForRemoval() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

	void updateColor();

private:
	sf::CircleShape circleShape;

	sf::FloatRect bounds;
	sf::Vector2f routePoint;
	float velocity;

	sf::Time timeAlive;
	sf::Time maxTime;

	TextNode* timeAliveLabel;

	bool destroyed;
	bool soundPlayed;
	bool toRemove;
};

