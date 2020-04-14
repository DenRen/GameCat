#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/System/String.hpp>
#include <thread>
#include <Windows.h>

void key_handler (const sf::Event& event, sf::Window& window, bool press);

void game ();

int main () {
	game ();
	//std::thread main_thread (game);
	//main_thread.join ();
	//system ("pause");
	return 0;
}

void game () {
	sf::RenderWindow window;
	window.create (sf::VideoMode (1920 / 2, 1080 / 2), ""); //(sf::VideoMode::getDesktopMode (), "", sf::Style::Fullscreen);
	window.setPosition (sf::Vector2i (0 * 1920 / 2, 0));
	window.setVerticalSyncEnabled (true);
	window.setKeyRepeatEnabled (false);

	//window.setFramerateLimit (25);
	sf::Cursor cursor;
	if (cursor.loadFromSystem (sf::Cursor::Arrow))
		window.setMouseCursor (cursor);

	sf::Event event;
	sf::Clock clock;
	int frame_rate = 25;
	int frame_dur = 1000 / frame_rate;

	while (window.isOpen ()) {
		//if (clock.getElapsedTime ().asMilliseconds () >= frame_dur) {
			while (window.pollEvent (event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close ();
					break;
				case sf::Event::KeyPressed:
					key_handler (event, window, true);
					break;
				case sf::Event::KeyReleased:
					key_handler (event, window, false);
					break;
				case sf::Event::MouseMoved:
					printf ("x: %3d, y: %3d\n", event.mouseMove.x, event.mouseMove.y);
					break;
				case sf::Event::MouseButtonPressed:
					printf ("Mouse pressed\n");
					break;
				case sf::Event::MouseButtonReleased:
					printf ("Mouse released\n");
					break;
				}
			}

		//}
	}
}

void parallel () {
	for (int i = 0; i < 10; i++) {
		printf ("___________________________________ I'm right!\n");
		sf::sleep (sf::milliseconds (200));

	}
}

void key_handler (const sf::Event& event, sf::Window& window, bool press) {
	static bool close_win = false;

	switch (event.key.code) {
		case sf::Keyboard::Escape:
			printf ("Escape: %d\n", press);
			if (!close_win && press) {
				close_win = true;
				printf ("If you release the Escape, I immediatly closed)\n");
			}
			else if (close_win && !press)
				//printf ("\"close ()\"\n");
				window.close ();

			break;

		case sf::Keyboard::Space:
			if (press) {
				printf ("Space pressed\n");
				std::thread print (parallel);
				print.detach ();
			}

			break;
	}
}