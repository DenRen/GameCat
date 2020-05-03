#include "SpriteAnimation.hpp"

namespace spran {
	SpriteAnimation::SpriteAnimation (int size, sf::Sprite *sprite) :
		sprite (sprite),
		data ((DataAnim *) calloc (size, sizeof (DataAnim)))
	{
		if (data == nullptr)
			throw "Failed to create data array for sprite animation";

	}
}
