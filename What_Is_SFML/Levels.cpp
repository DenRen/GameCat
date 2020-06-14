#include "Levels.h"
#include "Level_0.h"
#include "Engines.hpp"

extern unsigned int width;
extern unsigned int height;

extern sf::RenderWindow window;

namespace lvl {
	
	levels_t::levels_t (int quantity) :
		quantity (quantity),
		levels ((level_t *) calloc (quantity, sizeof (level_t)))
	{
		if (levels == nullptr)
			std::runtime_error ("Zero levels! Failed to create levels!");

		levels[0].Load  = lvl_0_Load;
		levels[0].Clean = lvl_0_Clean;
	}

	levels_t::~levels_t () {
		free (levels);
	}

	void openWindow (int type_window) {
		switch (type_window) {
		case win::DEBUG:						//sf::Style::Titlebar & sf::Style::Close);
			window.create (sf::VideoMode (width, height, 8 * 8), "", sf::Style::Default &
				~sf::Style::Resize);
			window.setPosition (sf::Vector2i (width / 2, 0));

			break;
		case win::RELEASE:
			window.create (sf::VideoMode (width, height, 8 * 8), "", sf::Style::Fullscreen);
			window.setPosition (sf::Vector2i (0, 0));

			break;
		default:
			throw std::runtime_error ("Incorrect window type!");
		}
	}
}