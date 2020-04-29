#pragma once

#include <SFML/Graphics.hpp>

namespace ce {
	struct Ctrlobj {
		int BufNum = -1;			// -1 if it does not lie in any buffer
		virtual void AKey (sf::Event event) = 0;	// Action on key user pressed
	};

	struct ControllerEngine {
		Ctrlobj **buf;
		int size;

		int sizeOn;
		int posOff;

		ControllerEngine ();
		ControllerEngine (int size);

		void init (int size);
		void add (Ctrlobj *ctrlobj);
		void del (int number);

		void ControllOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void ControllOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void getCommandUsers ();

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
}
