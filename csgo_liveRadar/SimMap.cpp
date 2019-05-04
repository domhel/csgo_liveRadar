#include <SFML/Graphics.hpp>
#include "SimPlayer.hpp"
#include "SimMap.hpp"

dh::SimMap::SimMap(std::string name) : dh::Map(name)
{
}
dh::SimMap::~SimMap()
{
	deletePlayers();
}

void dh::SimMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= image.getTransform();
	states.texture = image.getTexture();
	target.draw(image, states);
	for (size_t i = 0; i < players.size(); ++i) {
		target.draw(*((dh::SimPlayer*)players[i]), states);
	}
}
void dh::SimMap::updatePlayers(void)
{
	for (size_t i = 0; i < players.size(); ++i) {
		players[i]->updateCircleshape(0, getBounds().height + 2 * getBounds().top);
		players[i]->updateDirectionLine();
	}
}
void dh::SimMap::deletePlayers(void) {
	for (size_t i = 0; i < players.size(); ++i) {
		delete players[i];
	}
	players.clear();
}
void dh::SimMap::addPlayer(void)
{
	dh::SimPlayer* p = new SimPlayer;
	players.push_back(p);
}