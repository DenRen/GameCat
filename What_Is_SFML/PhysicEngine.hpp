#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

namespace pe {
	struct rect_t {
		float x0, y0, x1, y1;

		rect_t (float x0, float y0, float x1, float y1) :
			x0 (x0), y0 (y0), x1 (x1), y1 (y1)
		{}

		bool intersect (rect_t &other);
		rect_t calc_poligon (sf::Vector2f size, sf::Vector2f coord);
	};

	enum PHYSIC_TYPE {
		MAT_POINT,
		CTRL_MAT_POINT,
		CTRL_POLIGON,
		MOTIONLESS
	};

	enum objtype {
		USER,
		NPC,
		BUTTON,
		BECON,
		WALL,
		COUNTER
	};

	struct Physobj {
		int BufNum = -1;	// -1 if it does not lie in any buffer
		int type = -1;
		rect_t poligon = {0, 0, 0, 0};
		virtual void ActCtrl () = 0;	// Action on the controller
		virtual sf::Vector2f getLocate () = 0;
		virtual void ActInterOutside (Physobj &physobj) = 0;
	};

	struct PhysicEngine {
		Physobj **buf;
		int size;

		int sizeOn;
		int posOff;

		PhysicEngine ();
		PhysicEngine (int size);
		~PhysicEngine ();

		void init (int size);
		void add (Physobj *physobj);
		void del (int number);
		void clean ();					// Del all object in buff

		void visOn (int number);		// visualOn (),  visible (),   visibleOn (), activ ()
		void visOff (int number);		// visualOff (), invisible (), visibleOff (), diactiv ()

		void SetLocaleChanges ();		// Perform action on the controller
		void SetInteractionOutside ();

		inline void _swap (int first, int second);
		inline bool verifier ();

		void DUMP ();
	};
}
