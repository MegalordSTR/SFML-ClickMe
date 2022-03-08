#pragma once
#include "SceneNode.h"
#include "ResourseHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <string>

class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fonts);

	void setText(const std::string& str);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::Text text;
};

