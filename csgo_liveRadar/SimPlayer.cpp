#include <SFML/Graphics.hpp>
#include "SimPlayer.hpp"
#include <iostream>

dh::SimPlayer::SimPlayer(): dh::Player()
{
	body.setFillColor(sf::Color::Blue);
	//body.setRadius(50.0f);
	body.setRadius(30.0f);
	body.setPointCount(20);
	body.setOrigin(body.getRadius(), body.getRadius());
}

void dh::SimPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body, states);
	target.draw(direction, states);
}
void dh::SimPlayer::updateCircleshape(int offset_x, int offset_y)
{
	this->body.setPosition(this->position.x + offset_x, offset_y - this->position.y);
}
void dh::SimPlayer::updateDirectionLine(void)
{

}
void dh::SimPlayer::updateColor(void)
{

}

sf::Vector3f dh::SimPlayer::getPosition(void)
{
	return this->position;
}
sf::Vector3f dh::SimPlayer::getVelocity(void)
{
	return this->velocity;
}
void dh::SimPlayer::move(sf::Vector3f direction)
{
	this->position += direction;
	std::cout << "Player position: " << position.x << "/" << position.y << std::endl;
}