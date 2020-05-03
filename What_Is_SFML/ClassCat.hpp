#pragma once
#include "ObjMoveTempl.hpp"

namespace hero {

	class cat {
	public:

		struct Model_2_View {	// Inteface between Model and View
			sf::Vector2f coord;
			int state;			// 
			int direct;			// Move direction
		};

		struct Control_2_Model {
			bool Processed_PE;
			signed direction : 2;
			__int8 action;
		};

		class Animation : public ve::Visobj
		{
		public:

			// Interface getting Model Requests 
			Model_2_View ViewParam;

			sf::Sprite sprite;

			Animation () {};
			Animation (sf::Texture *texture_cat);

			void draw ();
		};

		class Physic : 
			public pe::Physobj, public objmove::smooth::PhysSmoothMove
		{
		public:
			// Interface Model -> View
			Model_2_View *ViewParam;

			Physic (sf::Vector2f init_pos, pe::objtype type, Model_2_View *ViewParam, 
					int direct = objmove::smooth::direct_move::RIGHT);

			void ActCtrl ();
			void SetViewParam ();

			sf::Vector2f getLocate ();
			void ActInterOutside (pe::Physobj &physobj);
		 };

		class ActKey : 
			public ue::UserCtrlobj, public objmove::smooth::UserCtrl
		{
		public:
			
			ActKey (objmove::smooth::AManager *ReqUserCtrl);

			void AKey ();
			
		};

		Animation	View;
		Physic		Model;
		ActKey		Control;

		cat (sf::Vector2f init_pos, sf::Texture *texture_cat, pe::objtype);
	};
}
