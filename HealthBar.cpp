#include "HealthBar.h"
#include "CategoryIdentifiers.h"

HealthBar::HealthBar(int32_t startHP, TextureHolder& textures, const sf::Vector2f upperLeftCorner) :
	SceneNode(),
	textures(textures),
	hearts(),
	hp(startHP),
	textureScaleFactor(1.f,1.f)
{
	setNodeCategory(Game::CategoryType::HealthBar);
	const sf::Texture& heartTexture = textures.get(Game::Resources::Texture::Heart);

	sf::Vector2u textureSize = heartTexture.getSize();
	textureScaleFactor = sf::Vector2f(30.f / static_cast<float>(textureSize.x), 30.f / static_cast<float>(textureSize.y));

	for (int i = 0; i < startHP; i++)
	{
		auto heart = std::make_unique<sf::Sprite>(heartTexture);
		heart->setScale(textureScaleFactor);
		heart->setPosition(upperLeftCorner.x, upperLeftCorner.y + 30.f * i);
		hearts.push_back(std::move(heart));
	}
}

void HealthBar::update(sf::Time dt, CommandQueue& commands)
{
}

void HealthBar::onCommand(const Command& command, sf::Time dt)
{
}

bool HealthBar::isMarkedForRemoval() const
{
	return false;
}

void HealthBar::damage(int32_t damage)
{
	if (hp > 0)
	{
		const sf::Texture& heartTexture = textures.get(Game::Resources::Texture::HeartDamaged);
		hearts[hp - 1]->setTexture(heartTexture);
		hp--;
	}
	
}

int32_t HealthBar::getHP()
{
	return static_cast<int32_t>(hp);
}

void HealthBar::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& h : hearts)
	{
		target.draw(*h, states);
	}
	
}

void HealthBar::updateCurrent(sf::Time dt, CommandQueue& commands)
{
}
