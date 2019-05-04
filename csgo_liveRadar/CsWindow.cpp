#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CsWindow.hpp"
#include "Map.hpp"

dh::CsWindow::CsWindow(dh::Map& map, unsigned int width, unsigned int height) : 
	dh::Window(map, width, height)
{
}

void dh::CsWindow::Run(void)
{
	while (window.isOpen())
	{
		handleInput();
		Update(0.0f);
		Render();
	}
}
void dh::CsWindow::Update(float dt)
{
	this->map.updatePlayers();
	//sf::Vector3f p = map.getPlayers()[0]->getPosition();
	//view.setCenter(p.x, p.y);
}
void dh::CsWindow::Render(void)
{
	this->window.clear();
	window.setView(view);
	this->window.draw(map);
	this->window.display();
}
void dh::CsWindow::handleInput(void)
{
	static bool mousePressed = false;
	static sf::Vector2i lastMousePosition = sf::Mouse::getPosition(window);
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			mousePressed = false;
			break;
		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta > 0) {
				view.zoom(0.9f);
				viewZoom *= 0.9f;
			}
			else {
				view.zoom(1.1f);
				viewZoom *= 1.1f;
			}
			break;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			// drag and scroll the map
			if (mousePressed)
			{
				sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
				sf::Vector2f mousePositionChange = sf::Vector2f(
					(viewZoom * (lastMousePosition.x - currentMousePosition.x)),
					(viewZoom * (lastMousePosition.y - currentMousePosition.y))
				);
				lastMousePosition = currentMousePosition;
				view.move(mousePositionChange);
			}
			else {
				lastMousePosition = sf::Mouse::getPosition(window);
				mousePressed = true;
			}
		}
	}

}