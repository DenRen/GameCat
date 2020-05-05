#include "VisMove.hpp"
#include <assert.h>

extern float delta_time;

namespace objmove {

	namespace smooth {
		
		void ViewFrame::SetNextFrame (float speed, int direct, int state) {
			assert (speed >= 0);
			assert (eps_speed >= 0);

	#define _DA dataAnim.data[old_state]
			printf ("State: %d\nOld_state: %d\n", state, old_state);

			time_state += delta_time;
			if (state != old_state) {

				if (dataAnim.data[state].cycle) {
					if (old_num_state == _DA.size - 1)
						old_state = state;
				
				} else
					if (old_num_state == 0)
						old_state = state;
				
			} else
				if (old_num_state == 0) {
					old_state = state;
				}


			sf::Vector2i new_frame;

			//printf ("time_state: %g\n", time_state);

			if (_DA.cycle) {
				//printf ("Cycle: %s\n", "true");
				int _save = old_num_state;
				old_num_state = (int) (time_state / _DA.dur) % _DA.size;
				//printf ("time_state: %g\n", time_state);
				//printf ("(int) (time_state / _DA.dur): %d\n", (int) (time_state / _DA.dur) % _DA.size);

				dataAnim.SetFrame (state, old_num_state);

			} else {
				//printf ("Cycle: %s\n", "false");
				if (speed < walking_speed)
					old_num_state = (int) ((float) _DA.size * (1 - (walking_speed - speed) / (walking_speed)));
				else
					old_num_state = (int) ((float) _DA.size * (1 - (running_speed - speed) / (running_speed)));

				dataAnim.SetFrame (state, old_num_state);
			}
			//printf ("Speed: %g\nOld_num_state: %d\n\n\n", speed, old_num_state);
			
		}

		ViewFrame::ViewFrame (sf::Texture *texture) :
			sprite (*texture),
			dataAnim (5, &sprite)
		{}
	}

}