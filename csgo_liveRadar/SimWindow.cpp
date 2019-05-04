#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Map.hpp"
#include "SimWindow.hpp"
#include "SimPlayer.hpp"
#include <iostream>

dh::SimWindow::SimWindow(dh::Map& map, unsigned int width, unsigned int height): 
	dh::Window(map, width, height)
{
}

void dh::SimWindow::Run(void)
{
	sf::Clock clock;
	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asSeconds();
		handleInput();
		Update(dt);
		Render();
	}
}
void dh::SimWindow::Update(float dt)
{
	map.updatePlayers();
}
void dh::SimWindow::Render(void)
{
	this->window.clear();
	window.setView(view);
	this->window.draw(map);
	this->window.display();
}
void dh::SimWindow::handleInput(void)
{
	static bool mousePressed = false;
	sf::Event event;
	static dh::SimPlayer& p = *((dh::SimPlayer*)map.getPlayers()[0]);
	// Keyboard Input and Collision Testing
	{
		constexpr float step = 5.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			p.getPosition().y < 875)
			p.move(sf::Vector3f(0.0f, step, 0.0f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			p.getPosition().y > -45)
			p.move(sf::Vector3f(0.0f, -step, 0.0f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			p.getPosition().x > -100)
			p.move(sf::Vector3f(-step, 0.0f, 0.0f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			p.getPosition().x < 825)
			p.move(sf::Vector3f(step, 0.0f, 0.0f));

	}

	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
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
		case sf::Event::MouseButtonPressed:
			sf::Vector2i mousepos = sf::Mouse::getPosition(window);
			sf::Vector2f pos = window.mapPixelToCoords(mousepos);
			std::cout << "Clicked position: " << pos.x << "/" << pos.y << std::endl;
			break;
		/*case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::W:
				((dh::SimPlayer*)map.getPlayers()[0])->move(sf::Vector3f(0.0f, step, 0.0f));
				break;
			case sf::Keyboard::S:
				((dh::SimPlayer*)map.getPlayers()[0])->move(sf::Vector3f(0.0f, -step, 0.0f));
				break;
			case sf::Keyboard::A:
				((dh::SimPlayer*)map.getPlayers()[0])->move(sf::Vector3f(-step, 0.0f, 0.0f));
				break;
			case sf::Keyboard::D:
				((dh::SimPlayer*)map.getPlayers()[0])->move(sf::Vector3f(step, 0.0f, 0.0f));
				break;
			}
			break;*/
		}
	}
}