#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Engines.hpp"
#include "ClassCat.hpp"
#include <locale.h>

struct ActKey {

};

unsigned int width = 640;
unsigned int height = 640 * 9 / 16;

sf::RenderWindow window;
ve::VisualEngine VE;
pe::PhysicEngine PE;
ce::ControllerEngine CE;

int main () {
#define TEXTURE_FILE_CAT "sprites/cat.png"

	window.create (sf::VideoMode (width, height, 8 * 8), "TestActKey", sf::Style::Default &
																	  ~sf::Style::Resize); //sf::Style::Titlebar & sf::Style::Close);
	window.setPosition (sf::Vector2i (1920 / 2 + width / 2, 0));
	window.setVerticalSyncEnabled (true);
	window.setKeyRepeatEnabled (false);

	VE.init (20);
	CE.init (3);
	PE.init (20);

	sf::Texture texture_cat;
	if (!texture_cat.loadFromFile (TEXTURE_FILE_CAT))
		printf ("Failed to load texture");

	hero::cat cat ({ 150, 400 }, &texture_cat);

	VE.add ((ve::Visobj  *) &(cat.View));
	CE.add ((ce::Ctrlobj *) &(cat.Control));
	PE.add ((pe::Physobj *) &(cat.Model));

	bool state = true;

	while (window.isOpen ()) {

		CE.getCommandUsers ();
		PE.SetLocaleChanges ();
		VE.draw ();

	}

	return 0;

#undef TEXTURE_FILE_CAT
}
