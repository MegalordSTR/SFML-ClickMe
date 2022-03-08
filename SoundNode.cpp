#include "SoundNode.h"

SoundNode::SoundNode(SoundPlayer& player) :
	player(player)
{
	setNodeCategory(Game::CategoryType::SoundEffect);
}

void SoundNode::playSound(Game::Resources::SoundEffect sound)
{
	player.play(sound);
}
