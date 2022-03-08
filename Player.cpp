#include "Player.h"
#include "CircleNode.h"

struct CircleSelector
{
    typedef std::function<bool(CircleNode&)> Selector;
    CircleSelector(Selector selector) : selector(selector) {};

    bool operator() (CircleNode& circle) const
    {
        return selector(circle);
    }

    Selector selector;
};

Player::Player()
{
}

void Player::handleInputEvent(const sf::Event& event, CommandQueue& commands)
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::Vector2f point(float(event.mouseButton.x), float(event.mouseButton.y));

            CircleSelector selector(
                [point](CircleNode& circle) {
                    return circle.intersects(point);
                }
            );
            auto action = derrivedAction<CircleNode>([selector](CircleNode& node, sf::Time dt)
                {
                    if (selector(node))
                    {
                        node.destroy();
                    }
                }
            );
            commands.push(Command(action, Game::CategoryType::Bubble));
        }
        break;
        default:
            break;
    }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
}
