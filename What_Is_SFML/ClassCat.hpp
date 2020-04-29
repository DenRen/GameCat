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
			RIGHT,
			LEFT,
			FRONT
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
			unsigned direction : 2;
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
			int direct;

			Physic (sf::Vector2f init_pos, Model_2_View *ViewParam, int direct = direct::RIGHT);

			void ActCtrl ();
			void SetViewParam (Model_2_View *buf);
		 };

		class ActKey : public ce::Ctrlobj
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
		

		cat (sf::Vector2f init_pos);
		cat (sf::Vector2f init_pos, sf::Texture *texture_cat);
	};
}