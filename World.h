#pragma once
#include "CommandQueue.h"
#include "SceneManager.h"
#include "State.h"
#include "ResourseHolder.h"

#include <SFML/Graphics.hpp>

class CircleNode;
class HealthBar;


class World : sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window, FontHolder& fonts, TextureHolder& textures, SoundPlayer& soundPlayer);
	void update(sf::Time dt);
	void draw();

	bool checkHP();
	int32_t getScore();

	CommandQueue& getCommandQueue();

private:
	void updateScoreText();

	void processDestroyedCircles(CommandQueue& commands);
	void spawnCircles(int32_t qnt);

	void drawGUI();

	sf::Vector2f getRandomViewPosition();

private:
	sf::RenderWindow& window;
	sf::View view;

	CommandQueue commands;

	// Resource Holders
	FontHolder& fonts;
	TextureHolder& textures;

	sf::Sprite background;  // вынести на слой
	// Text
	sf::Text playerScoreText;
	int32_t playerScore;

	// SceneManager
	SceneManager scene;
	HealthBar* healthBar;
	std::vector<CircleNode*> destroyedCircles;

	// SoundPlayer
	SoundPlayer& soundPlayer;
};

