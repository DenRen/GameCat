#include "Engines.hpp"
#include "ClassCat.hpp"

extern sf::RenderWindow window;
extern float delta_time;

namespace hero {

	/*cat::cat (sf::Vector2f init_pos) :
		View (),
		Model (init_pos, &View.ViewParam),
		Control (&Model.ReqController)
	{
		printf ("%g %g\n", Model.coord.x, Model.coord.y);
	}*/

	cat::cat (sf::Vector2f init_pos, sf::Texture *texture_cat, pe::objtype type) :
		View (texture_cat),
		Model (init_pos, type, &View.ViewParam),
		Control (&Model.ReqController)
	{}
	
	//| Animation |------------------------------------------------------------------

	cat::Animation::Animation (sf::Texture *texture_cat) :
		sprite (*texture_cat)
	{}

	void cat::Animation::draw () {
		sprite.setTextureRect (sf::IntRect (400, 5 * 200, 400, 200));
		sprite.setPosition (ViewParam.coord);
		window.draw (sprite);
	}

	//|	Physics |--------------------------------------------------------------------

	cat::Physic::Physic (sf::Vector2f init_pos, pe::objtype type, Model_2_View *ViewParam, int direct) :
		coord (init_pos),
		direct (direct),
		ViewParam (ViewParam),
		ReqController ({ true, direct::FRONT, user_action::NONE })
	{
		this->type = type;
	}

	void cat::Physic::ActInterOutside (pe::Physobj &physobj)
	{
	}

	void cat::Physic::SetViewParam (cat::Model_2_View *buf) {
		buf->coord = coord;
		buf->direct = direct;
		buf->state = cat::state_move::SITTING;
	}

	void cat::Physic::ActCtrl () {	// Action on monipulats user

		/*if (ReqController.Processed_PE)		// Невозможно)
			return;*/

		// This code have elements of optimization, because maybe therefore, 
		// it may seem that it is not structured. In fact, all is well.
		
	#define _WU accel = alpha.wu * (speed_state_move.walking - speed)
	#define _RU accel = alpha.ru * (speed_state_move.running - speed)

	#define _SD accel = -alpha.sd * (speed_state_move.running + speed)
	#define _WRD accel = -alpha.wrd * (speed_state_move.running + speed)
	#define _WD accel = -alpha.wd * (speed_state_move.walking + speed)

	#define _RC ReqController
	#define CUR_STATE cur_state == state_move
	#define CUR_STATE_NE cur_state != state_move

		int cur_state = GetCurrentState ();
		bool Accel = true;
		if (speed)
			Accel = _RC.direction == direct; // true - Accel, false - Braking
		else
			direct = _RC.direction;

		float accel = 0.0;
		
		if (Accel == false && CUR_STATE_NE::SITTING && _RC.action != user_action::NONE)
			_SD;
		else 
			switch (_RC.action) {

				case user_action::NONE:

					if (CUR_STATE_NE::SITTING)
						if (CUR_STATE::D_WALK || CUR_STATE::WALKING)
							_WD;
						else
							_WRD;
					break;

				case user_action::ACC_WALK:
				
					if (CUR_STATE::SITTING || CUR_STATE::D_WALK)
						_WU;
					else if (CUR_STATE::D_RUN)
							_WRD;
					else if (CUR_STATE::RUNNING)
							_SD;
					break;

				case user_action::ACC_RUN:

					if (CUR_STATE_NE::RUNNING)
						_RU;

					break;

				case user_action::DOWN:

					if (Accel && CUR_STATE_NE::SITTING)
						_SD;

					break;
			}
		
		SpeedChange (accel * delta_time, Accel);

		coord.x += direct * speed * delta_time;
		ViewParam->coord = coord;

		_RC.Processed_PE = true;
		
		printf ("\nAccel: %d\naccel: %4g\nspeed: %4g\npos: %4g\ndircet: %d\nd_speed: %g\n", 
				   Accel,	  accel,      speed,      coord.x,  direct,     direct * speed * delta_time);

#undef CUR_STATE_NE
#undef CUR_STATE
#undef _RC

#undef _WU
#undef _RU

#undef _WD
#undef _WRD
#undef _SD

	}

	inline void cat::Physic:: SpeedChange (float dv, bool Accel) {
		assert (eps_speed >= 0);
		
		speed += dv;
		if (speed < eps_speed) speed = 0;

	}

	int cat::Physic::GetCurrentState () {
		if (speed == 0)
			return state_move::SITTING;

		else if (speed <= speed_state_move.walking)

			if (speed + eps_speed >= speed_state_move.walking)
				return state_move::WALKING;
			else
				return state_move::D_WALK;
		else
			if (speed + eps_speed >= speed_state_move.running)
				return state_move::RUNNING;
			else
				return state_move::D_RUN;
	}

	inline sf::Vector2f cat::Physic::getLocate ()
	{
		return coord;
	}

	//| Keyboard action |------------------------------------------------------------
#define _RC			ReqController
//#define KEY		case sf::Keyboard::
#define KEY(key)	sf::Keyboard::isKeyPressed (sf::Keyboard:: key)
#define ACT			_RC->action = user_action::
#define DIR			_RC->direction = direct::
//#define SEND		_RC->Processed_PE = false; break;
#define SEND		_RC->Processed_PE = false;
	void cat::ActKey::AKey (sf::Event event) {
		
		if (_RC->Processed_PE == false)
			return;

		if (KEY (LShift)) {					// SHIFT	
			
			if (KEY (Right)) {

				ACT ACC_RUN;
				DIR RIGHT;

			} else if (KEY (Left)) {

				ACT ACC_RUN;
				DIR LEFT;

			} else if (KEY (Down))
				ACT DOWN;
			else
				ACT NONE;
				
		} else {							// SIMPLE	

			if (KEY (Right)) {

				ACT ACC_WALK;
				DIR RIGHT;

			} else if (KEY (Left)) {

				ACT ACC_WALK;
				DIR LEFT;

			} else if (KEY (Down))
				ACT DOWN;
			else
				ACT NONE;
		}															
		
		SEND
		
	}
/*
	void cat::ActKey::AKey (sf::Event event) {
		
		if (_RC->Processed_PE == false)
			return;

		if (event.key.shift)					// SHIFT	
			switch (event.key.code) {
				KEY Right :
					ACT ACC_RUN;
					DIR RIGHT;
				SEND

				KEY Left :
					ACT ACC_RUN;
					DIR LEFT;
				SEND

				KEY Down :
					ACT DOWN;
				SEND

				default:
					ACT NONE;
				SEND
			}
		 else									// SIMPLE							
			switch (event.key.code) {
				KEY Right :
					ACT ACC_WALK;
					DIR RIGHT;
				SEND

				KEY Left :
					ACT ACC_WALK;
					DIR LEFT;
				SEND

				KEY Down :
					ACT DOWN;
				SEND

				default:
					ACT NONE;
				SEND
			}
	}
	*/
#undef KEY
#undef ACT
#undef DIR
#undef SEND
#undef _RC
	cat::ActKey::ActKey (hero::cat::Control_2_Model *ReqController) :
		ReqController (ReqController)
	{}
}