#pragma once

/*namespace sf {
	class RenderTarget;
	class RenderStates;
	class Drawable;
	class CircleShape;
	class RectangleShape;
	class Color;
}*/
#include <SFML/Graphics.hpp>

namespace dh {
	class Player: public sf::Drawable {
	protected:
		sf::CircleShape body;
		sf::RectangleShape direction;
	public:
		Player();
		virtual ~Player() {}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void updateCircleshape(int offset_x = 0, int offset_y = 0) = 0;
		virtual void updateDirectionLine(void) = 0;
		virtual void updateColor(void) = 0;
		void setColor(sf::Color color);
	};
}