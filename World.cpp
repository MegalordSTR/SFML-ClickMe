#include "World.h"
#include "Utility.h"
#include "FontConsts.h"
#include "SceneNode.h"
#include "CircleNode.h"
#include "SoundNode.h"
#include "HealthBar.h"

#include <sstream>

World::World(sf::RenderWindow& window, FontHolder& fonts, TextureHolder& textures, SoundPlayer& soundPlayer) :
	window(window),
	view(window.getDefaultView()),
	commands(),
    fonts(fonts),
    textures(textures),
    soundPlayer(soundPlayer),
	playerScore(0),
	scene()
{
    background.setTexture(textures.get(Game::Resources::Texture::Background));

	playerScoreText.setFont(fonts.get(Game::Resources::Font::Main));
	playerScoreText.setCharacterSize(static_cast<unsigned int>(Game::FontSize::PlayerInfo));
    scene.addLayer(Game::Layer::World);
    scene.addLayer(Game::Layer::Sound);

    SceneNode& soundLayer = scene.getLayer(Game::Layer::Sound);
    soundLayer.attachChild(std::move(std::make_unique<SoundNode>(this->soundPlayer)));

    auto hpBar = std::make_unique<HealthBar>(3, textures, sf::Vector2f(view.getSize().x - 30.f, 30.f));
    healthBar = hpBar.get();
    SceneNode& worldLayer = scene.getLayer(Game::Layer::World);
    worldLayer.attachChild(std::move(hpBar));

    spawnCircles(10);
}

void World::update(sf::Time dt)
{
    soundPlayer.removeStoppedSounds();

    SceneNode& worldLayer = scene.getLayer(Game::Layer::World);
    SceneNode& soundLayer = scene.getLayer(Game::Layer::Sound);

    processDestroyedCircles(commands);
    while (!commands.isEmpty())
    {
        auto command = commands.pop();
        worldLayer.onCommand(command, dt);
        soundLayer.onCommand(command, dt);
    }

    worldLayer.update(dt, commands);
    
    worldLayer.removeMarked();
    spawnCircles(static_cast<int32_t>(destroyedCircles.size()));


    updateScoreText();
}

void World::draw()
{
    window.draw(background); // вынести на слой
    SceneNode& worldLayer = scene.getLayer(Game::Layer::World);
    window.draw(worldLayer);

    window.draw(playerScoreText);
}

CommandQueue& World::getCommandQueue()
{
    return commands;
}

void World::updateScoreText()
{
    const sf::Vector2f& viewSize = view.getSize();

    std::stringstream ss;
    ss << "SCORE: " << playerScore;
    playerScoreText.setString(ss.str());
    sf::FloatRect bounds = playerScoreText.getLocalBounds();

    playerScoreText.setPosition((viewSize.x - bounds.width) / 2, 20);
}

void World::processDestroyedCircles(CommandQueue& commands)
{
    auto action = derrivedAction<CircleNode>([this](CircleNode& node, sf::Time dt) {
        if (node.isDestroyed())
        {
            destroyedCircles.push_back(&node);
            node.markToRemove();
            
            if (node.isTimeExeeded())
            {
                healthBar->damage(1);
            }
            else
            {
                playerScore++;
            }
        }
        }
    );
    commands.push(Command(action, Game::CategoryType::Bubble));
    destroyedCircles.clear();
}

void World::spawnCircles(int32_t qnt)
{
    SceneNode& worldLayer = scene.getLayer(Game::Layer::World);
    const sf::Vector2f& viewSize = view.getSize();

    for (int i = 0; i < qnt; i++)
    {
        sf::Color color(sf::Color(randIntN(256), randIntN(256), randIntN(256)));
        auto bubbleTexture = static_cast<Game::Resources::Texture>(static_cast<int>(Game::Resources::Texture::BubbleBlack) + randIntN(Game::Resources::BubbleTexturesCount));
        auto circle = std::make_unique<CircleNode>(20.f + randFloatN(20.f), bubbleTexture, textures, sf::FloatRect(0, 0, viewSize.x, viewSize.y), fonts);

        circle->setPosition(getRandomViewPosition());
        worldLayer.attachChild(std::move(circle));
    }
}

bool World::checkHP()
{
    return healthBar->getHP() > 0;
}

int32_t World::getScore()
{
    return playerScore;
}

void World::drawGUI()
{
}

sf::Vector2f World::getRandomViewPosition()
{
    const sf::Vector2f& viewSize = view.getSize();
    return sf::Vector2f(randFloatN(viewSize.x), randFloatN(viewSize.y));
}