#pragma once

/*namespace sf {
	class RenderWindow;
	class View;
}*/
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace dh {
	class Map;
	class Window
	{
	protected:
		dh::Map& map;
		sf::RenderWindow window;
		sf::View view;
		float viewZoom;

	public:
		Window(dh::Map& map, unsigned int width, unsigned int height);

		virtual void Run(void) = 0;
		virtual void Update(float dt) = 0;
		virtual void Render(void) = 0;
		virtual void handleInput(void) = 0;
	};
}