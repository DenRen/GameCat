#include "Level_0.h"
#include "Engines.hpp"

extern ve::VisualEngine			VE[ve::prt::QUANTITY];
extern pe::PhysicEngine			PE;
extern ue::UserControlEngine	UE;

sf::Texture texture_background;
objs::background background (&texture_background);

#define TEXTURE_FILE_CAT_LIGHTING	"sprites/cat_Lightning.png"
#define TEXTURE_FILE_CAT_TYPICAL	"sprites/cat.png"	
#define TEXTURE_FILE_BGART			"media/WhiteBackGraund.png"

void lvl_0_Load () {

	UE.init (2);
	PE.init (3);

	VE[ve::prt::BACKGROUND	].init (2);
	VE[ve::prt::OBJ_STATIC	].init (2);
	VE[ve::prt::OBJ_DYNAMIC	].init (2);

    if (!texture_background.loadFromFile (TEXTURE_FILE_BGART)) {

        printf ("Failed to load texture\n");
        return;
    }
}

void lvl_0_Clean () {

	VE[ve::prt::BACKGROUND ].clean ();
	VE[ve::prt::OBJ_STATIC ].clean ();
	VE[ve::prt::OBJ_DYNAMIC].clean ();
}

#undef TEXTURE_FILE_CAT_LIGHTING
#undef TEXTURE_FILE_CAT_TYPICAL