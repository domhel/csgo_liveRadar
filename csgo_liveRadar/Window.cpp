#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Window.hpp"
#include "Map.hpp"

dh::Window::Window(dh::Map& map, unsigned int width, unsigned int height) 
	: map(map) 
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;
	this->window.create(sf::VideoMode(width, height),
		"CSGO Radar", sf::Style::Close, settings);
	this->window.setVerticalSyncEnabled(true);
	this->window.setPosition(sf::Vector2i(10, 10));

	view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)width, (float)height));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	viewZoom = map.getBounds().width / width;
	view.zoom(viewZoom);
	window.setView(view);
}