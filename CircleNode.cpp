#include "Utility.h"
#include "FontConsts.h"
#include "CircleNode.h"
#include "SoundNode.h"

CircleNode::CircleNode(
	float radius,
	Game::Resources::Texture bubbleTexture,
	const TextureHolder& textures,
	const sf::FloatRect& bounds,
	const FontHolder& fonts,
	float velocity
) :
	circleShape(radius),
	velocity(velocity),
	bounds(bounds),
	destroyed(false),
	toRemove(false),
	soundPlayed(false),
	timeAlive(sf::Time::Zero),
	maxTime(sf::seconds(10)),
	timeAliveLabel(nullptr)
{
	circleShape.setTexture(&textures.get(bubbleTexture));
	routePoint.x = float(randIntN(int(bounds.width)));
	routePoint.y = float(randIntN(int(bounds.height)));
	auto localBounds = circleShape.getLocalBounds();
	setOrigin(std::floorf(localBounds.left + localBounds.width / 2), std::floorf(localBounds.top + localBounds.height / 2)); // вынести в SceneNode
	setNodeCategory(Game::CategoryType::Bubble);

	auto textNode = std::make_unique<TextNode>(fonts);
	timeAliveLabel = textNode.get(); // weak ptr?
	attachChild(std::move(textNode));

	timeAliveLabel->setPosition(radius, radius);
}

CircleNode::~CircleNode()
{
}

void CircleNode::setBounds(const sf::FloatRect& bounds)
{
	this->bounds = bounds;
}

bool CircleNode::intersects(const sf::Vector2f point) const
{
	return length(point - getPosition()) <= circleShape.getRadius();
}

void CircleNode::destroy()
{
	destroyed = true;
}

bool CircleNode::isDestroyed()
{
	return destroyed;
}

bool CircleNode::isTimeExeeded()
{
	return timeAlive > maxTime;
}

void CircleNode::markToRemove()
{
	toRemove = true;
}

bool CircleNode::isMarkedForRemoval() const
{
	return toRemove;
}

void CircleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!destroyed)
		target.draw(circleShape, states);
}

void CircleNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (destroyed)
	{
		if (!soundPlayed)
		{
			auto action = derrivedAction<SoundNode>([this](SoundNode& node, sf::Time dt) {
				node.playSound(static_cast<Game::Resources::SoundEffect>(randIntN(int(Game::Resources::SoundEffect::SoundCount))));
				});
			commands.push(Command(action, Game::CategoryType::SoundEffect));
		}
		return;
	}

	updateColor();
	if (routePoint == getPosition())
	{
		routePoint.x = float(randIntN(int(bounds.width)));
		routePoint.y = float(randIntN(int(bounds.height)));
	}

	sf::Vector2f targetVector = routePoint - getPosition();

	sf::Vector2f vector;
	vector = (targetVector.x == 0 && targetVector.y == 0) ? vector : unitVector(targetVector) * velocity * dt.asSeconds();
	vector = length(vector) < length(targetVector) ? vector : targetVector;

	move(vector);

	if (isTimeExeeded())
	{
		destroy();
	}

	timeAlive += dt;
	timeAliveLabel->setText(std::to_string(static_cast<int>(floorf(timeAlive.asSeconds()))));
}

void CircleNode::updateColor()
{
	float mt = maxTime.asSeconds();
	float ta = timeAlive.asSeconds();
	if (ta > mt / 2)
	{
		sf::Color warnColor = sf::Color();
		warnColor.r = static_cast<sf::Uint8>(255 * (ta / mt));
		warnColor.a = static_cast<sf::Uint8>(255 * (ta / mt));
		circleShape.setOutlineColor(warnColor);
		circleShape.setOutlineThickness(10*(ta / mt));
	}
	
}
