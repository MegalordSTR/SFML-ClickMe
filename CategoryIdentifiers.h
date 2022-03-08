#pragma once


namespace Game
{
	enum class CategoryType : unsigned int
	{
		None = 0,
		Bubble = 1 << 0,
		SoundEffect = 1 << 1,
		HealthBar = 1 << 2
	};
}