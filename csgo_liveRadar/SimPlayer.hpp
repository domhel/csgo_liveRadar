#pragma once

#include "Player.hpp"

/*namespace sf {
	class Vector3f;
	class CircleShape;
	class RenderTarget;
	class RenderStates;
}*/

namespace dh {
	class SimPlayer :
		public Player
	{
	private:
		sf::Vector3f position;
		sf::Vector3f velocity;
		sf::CircleShape body;
	public:
		SimPlayer();
		
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updateCircleshape(int offset_x = 0, int offset_y = 0) override;
		void updateDirectionLine(void) override;
		void updateColor(void) override;

		sf::Vector3f getPosition(void);
		sf::Vector3f getVelocity(void);
		void move(sf::Vector3f direction);
	};
}