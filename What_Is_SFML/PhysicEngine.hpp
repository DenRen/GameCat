#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

namespace pe {
	enum PHYSIC_TYPE {
		MAT_POINT,
		CTRL_MAT_POINT,
		CTRL_POLIGON,
		MOTIONLESS
	};

	struct Physobj {
		int BufNum = -1;	// -1 if it does not lie in any buffer
		virtual void ActCtrl () = 0;	// Action on the controller
	};

	struct PhysicEngine {
		Physobj **buf;
		int size;

		int sizeOn;
		int posOff;

		PhysicEngine ();
		PhysicEngine (int size);

		void init (int size);
		void add (Physobj *physobj);
		void del (int number);

		void visOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void visOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void SetLocaleChanges ();		// Perform action on the controller

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
	
}
