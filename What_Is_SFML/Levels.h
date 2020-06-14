#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


namespace lvl {

	enum {
		QUANTITY_LVL = 1
	};

	struct level_t
	{

		void (*Load)  () = nullptr;
		void (*Clean) () = nullptr;

	};

	struct levels_t {
		int quantity = 0;
		level_t *levels = nullptr;

		levels_t (int quantity);
		~levels_t ();
	};

	enum win {
		DEBUG,
		RELEASE
	};

	void openWindow (int type_window);

}