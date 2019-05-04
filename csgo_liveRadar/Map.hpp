#pragma once

/*namespace sf {
	class Drawable;
	class Sprite;
	class Texture;
	class RenderTarget;
	class RenderStates;
	class FloatRect;
}*/
#include <SFML/Graphics.hpp>

namespace dh {
	class Player;
	class Map: public sf::Drawable
	{
	protected:
		sf::Sprite image;
		sf::Texture tex;
		std::vector<dh::Player*> players;
		std::string name;
		sf::IntRect bounds;

	public:
		Map(std::string name);
		virtual ~Map() {}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void updatePlayers(void) = 0;
		virtual void deletePlayers(void) = 0;
		std::vector<dh::Player*> getPlayers(void) {
			return players;
		}
		const sf::IntRect getBounds(void) const {
			return bounds;
		}
	};
}