#pragma once
#include "SceneNode.h"
#include "SoundPlayer.h"


class SoundNode : public SceneNode
{
public:
	explicit SoundNode(SoundPlayer& player);

	void playSound(Game::Resources::SoundEffect sound);

private:
	SoundPlayer& player;
};

