#pragma once
#include <SFML/Graphics.hpp>

namespace spran {

	enum {
		HORIZONTAL, VERTICAL,		// Arrangement direction locate of sprites
		UP, DOWN,					
	};

	struct DataAnim {
		unsigned arrang : 1;
		unsigned dir_spr : 1;
		unsigned Hight;
		unsigned Width;
		unsigned size = -1;
		sf::Vector2i locate;
	};

	class SpriteAnimation
	{
		DataAnim *data = nullptr;
		sf::Sprite *sprite = nullptr;

		SpriteAnimation (int size, sf::Sprite *sprite);
	};

}