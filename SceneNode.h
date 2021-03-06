#pragma once
#include "CommandQueue.h"
#include "CategoryIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	explicit SceneNode();

	void attachChild(std::unique_ptr<SceneNode> ptr);
	std::unique_ptr<SceneNode> detachChild(const SceneNode& ptr);

	void update(sf::Time dt, CommandQueue& commands);
	void onCommand(const Command& command, sf::Time dt);

	virtual bool isMarkedForRemoval() const;
	void removeMarked();

	void setNodeCategory(Game::CategoryType type);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; // To override
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt, CommandQueue& commands); // To override
	void updateChildren(sf::Time dt, CommandQueue& commands);

private:
	SceneNode* parent;
	std::vector<std::unique_ptr<SceneNode>> children;
	Game::CategoryType nodeType;
};