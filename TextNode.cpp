#include "TextNode.h"
#include "FontConsts.h"

TextNode::TextNode(const FontHolder& fonts) :
	SceneNode(),
	text()
{
	text.setCharacterSize(static_cast<unsigned int>(Game::FontSize::PlayerInfo));
	text.setFont(fonts.get(Game::Resources::Font::Main));
}

void TextNode::setText(const std::string& str)
{
	text.setString(str);

	auto localBounds = text.getLocalBounds();
	setOrigin(std::floorf(localBounds.left + localBounds.width / 2), std::floorf(localBounds.top + localBounds.height / 2));
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void TextNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Ничего
}
