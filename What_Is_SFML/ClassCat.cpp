#include "Engines.hpp"
#include "ClassCat.hpp"

extern sf::RenderWindow window;

namespace hero {

	cat::cat (sf::Vector2f init_pos) :
		View (),
		Model (init_pos, &View.ViewParam),
		Control (&Model.ReqController)
	{
		printf ("%g %g\n", Model.coord.x, Model.coord.y);
	}

	cat::cat (sf::Vector2f init_pos, sf::Texture *texture_cat) :
		View (texture_cat),
		Model (init_pos, &View.ViewParam),
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

	cat::Physic::Physic (sf::Vector2f init_pos, Model_2_View *ViewParam, int direct) :
		coord (init_pos),
		direct (direct),
		ViewParam (ViewParam),
		ReqController ({ true, direct::FRONT, user_action::NONE })
	{}

	void cat::Physic::SetViewParam (cat::Model_2_View *buf) {
		buf->coord = coord;
		buf->direct = direct;
		buf->state = cat::state_move::SITTING;
	}

	void cat::Physic::ActCtrl () {
		
	}

	//| Keyboard action |------------------------------------------------------------

#define KEY		case sf::Keyboard::
#define ACT		ReqController->action = user_action::
#define DIR		ReqController->direction = direct::
#define SEND	ReqController->Processed_PE = false; break;

	void cat::ActKey::AKey (sf::Event event) {
		if (event.key.shift) {				// SHIFT

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
			}
		} else {							// SIMPLE

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
			}
		}
	}

#undef KEY
#undef ACT
#undef DIR
#undef SEND

	cat::ActKey::ActKey (hero::cat::Control_2_Model *ReqController) :
		ReqController (ReqController)
	{}
}