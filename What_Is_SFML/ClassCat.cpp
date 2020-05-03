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
		Control (&Model.manager)
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

	cat::Physic::Physic (sf::Vector2f init_pos, pe::objtype type, 
						 Model_2_View *ViewParam, int direct) :
		ViewParam (ViewParam)		
	{
		this->type = type;
		
		alpha.wu  = 1;
		alpha.wd  = 1;
		alpha.ru  = 1;
		alpha.wrd = 1;
		alpha.sd  = 5;

		speed_state_move.walking = 100;
		speed_state_move.running = 300;

		coord = init_pos;
		speed = 0;
		this->direct = direct;

		UpdateCurrentState ();

		manager.Processed_PE = true;
		manager.direction = objmove::smooth::direct_move::RIGHT;
		manager.action = objmove::smooth::action_manager::NONE;

		eps_speed = 0.1;
	}

	void cat::Physic::ActInterOutside (pe::Physobj &physobj)
	{
	}

	inline void cat::Physic::SetViewParam () {
		ViewParam->coord = coord;
		ViewParam->direct = direct;
		ViewParam->state = objmove::smooth::state_move::SITTING;
	}

	void cat::Physic::ActCtrl () {	// Action on monipulats user

		update_speed ();
		SetViewParam ();

	}

	inline sf::Vector2f cat::Physic::getLocate ()
	{
		return coord;
	}
	
	// | Keyboard |------------------------------------------------------------------
	
	void cat::ActKey::AKey () {
		this->get ();
	}

	cat::ActKey::ActKey (objmove::smooth::AManager *ReqUserCtrl)
	{
		ReqUserController = ReqUserCtrl;
	}
}