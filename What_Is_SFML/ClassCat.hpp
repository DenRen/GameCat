#pragma once

namespace hero {

	class cat {
	public:
		enum state_move {
			SITTING,
			D_WALK,		// Delta walk
			WALKING,
			D_RUN,		// Delta run
			RUNNING
		};
		enum direct {
			RIGHT = 1,
			LEFT  = -1,
			FRONT = 0
		};

		struct Model_2_View {	// Inteface between Model and View
			sf::Vector2f coord;
			int state;			// 
			int direct;			// Move direction
		};

		enum user_action {
			NONE,
			ACC_WALK,
			ACC_RUN,
			DOWN
		};

		struct Control_2_Model {
			bool Processed_PE;
			signed direction : 2;
			__int8 action;
		};

	//private:
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

		class Physic : public pe::Physobj
		{
		public:
			// Interface Model -> View
			Model_2_View *ViewParam;
			// Interface getting Controller Requests
			Control_2_Model ReqController;
			
			sf::Vector2f coord;
			float speed = 0;	// Always above or equal by zero
			int direct = 1;	// Right: 1; Left: -1
			
			// Constants for smooth walking
			struct _alpha {
				float wu;
				float wd;
				float ru;
				float wrd;
				float sd;
			};
			struct _speed_state_move {
				float walking;
				float running;
			};
			const _alpha alpha = {1, 1, 1, 1, 5};
			const _speed_state_move speed_state_move = {100, 300};

			Physic (sf::Vector2f init_pos, pe::objtype type, Model_2_View *ViewParam, int direct = direct::RIGHT);

			void ActCtrl ();
			sf::Vector2f getLocate ();

			const float eps_speed = 0.01;
			void SpeedChange (float dv, bool Accel);

			void ActInterOutside (pe::Physobj &physobj);
			void SetViewParam (Model_2_View *buf);
			int GetCurrentState ();
		 };

		class ActKey : public ue::UserCtrlobj
		{
		public:
			// Interface Controller -> Model
			Control_2_Model *ReqController;

			ActKey (Control_2_Model *ReqController);

			void AKey (sf::Event event);
		};

		Animation	View;
		Physic		Model;
		ActKey		Control;
		

		//cat (sf::Vector2f init_pos);
		cat (sf::Vector2f init_pos, sf::Texture *texture_cat, pe::objtype);
	};
}
