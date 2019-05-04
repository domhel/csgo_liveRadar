#pragma once

#include "DEFINITIONS.hpp"
#ifdef CSGO
#include "CsPlayer.hpp"

/*namespace sf {
	class RectangleShape;
	class RenderTarget;
	class RenderStates;
	class Vector3f;
}*/
#include <SFML/Graphics.hpp>

namespace dh {
	class CsLocalplayer : public CsPlayer {
	private:
		sf::RectangleShape face;

	public:
		int crosshairId;

		CsLocalplayer();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void updateAddress(void);
		void updateCrosshairId(void);
		sf::Vector3f getViewAngles(void) const;
		void updateFace(void);
	};
}
#endif