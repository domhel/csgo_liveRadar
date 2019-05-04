#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.hpp"
#include "MemoryManager.h"
#include "offsets.hpp"

dh::Player::Player()
{
	body.setRadius(30.0f);
	body.setPointCount(20);
	body.setOrigin(body.getRadius(), body.getRadius());
	direction.setFillColor(sf::Color::Black);
	direction.setSize(sf::Vector2f(3.0f, 50.0f));
	direction.setOrigin(direction.getLocalBounds().width / 2.0f, direction.getLocalBounds().height / 2.0f);
}

void dh::Player::setColor(sf::Color color)
{
	body.setFillColor(color);
}