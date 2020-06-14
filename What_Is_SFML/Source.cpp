#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Engines.hpp"
#include "ClassCat.hpp"
#include "Levels.h"

unsigned int width = 1920;
unsigned int height = width * 9 / 16;

sf::RenderWindow window;

ve::VisualEngine VE[ve::prt::QUANTITY];
pe::PhysicEngine PE;
ue::UserControlEngine UE;

float delta_time;
int LVL = 0;

int main () {

	lvl::levels_t buf_levels (lvl::QUANTITY_LVL);

	lvl::openWindow (lvl::win::DEBUG);

	sf::Clock clock;
	__int64 __time_old = clock.getElapsedTime ().asMicroseconds () - 1000000;
	__int64 __curr_time = __time_old;

	while (LVL >= 0 && window.isOpen ()) {

		buf_levels.levels[LVL].Load ();

		int save_LVL = LVL;
		while (LVL == save_LVL && window.isOpen ()) {
			// | Get delta_time | -------------------------------------
			__curr_time = clock.getElapsedTime ().asMicroseconds ();
			delta_time = (float) (__curr_time - __time_old) / 1000000;		// In seconds
			__time_old = __curr_time;
			//---------------------------------------------------------
			
			UE.getCommandUsers ();
			PE.SetLocaleChanges ();
			PE.SetInteractionOutside ();

			window.clear (sf::Color::White);
			VE[ve::prt::BACKGROUND	].draw ();
			VE[ve::prt::OBJ_STATIC	].draw ();
			VE[ve::prt::OBJ_DYNAMIC	].draw ();
			VE[ve::prt::HERO		].draw ();
			window.display ();

		}

		buf_levels.levels[save_LVL].Clean ();

	}


	return 0;
}
/*
int main () {

	sf::Texture texture_cat;
	if (!texture_cat.loadFromFile (TEXTURE_FILE_CAT_TYPICAL))
		printf ("Failed to load texture");

	hero::cat cat ({ 150, 330 }, &texture_cat, pe::objtype::USER);

	VE[ve::prt::HERO].add ((ve::Visobj		 *) &(cat.View));
	UE.add ((ue::UserCtrlobj *) &(cat.Control));
	PE.add ((pe::Physobj	 *) &(cat.Model));

	return 0;

}
*/