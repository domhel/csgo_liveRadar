#include <SFML/Graphics.hpp>
#include "CsLocalplayer.hpp"
#include "CsMap.hpp"
#ifdef CSGO
#include "MemoryManager.h"
#include "Manager.h"

dh::CsMap::CsMap(std::string name): dh::Map(name)
{
}
dh::CsMap::~CsMap()
{
	deletePlayers();
}

void dh::CsMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= image.getTransform();
	states.texture = image.getTexture();
	target.draw(image, states);
	for (size_t i = 0; i < players.size(); ++i) {
		target.draw(*players[i], states);
	}
}
void dh::CsMap::updatePlayers(void)
{
	static DWORD myLastAddress = 0;
	static int count = 0;
	if (cm.me.address != myLastAddress || count >= 1000) {
		// Update All Players because addresses have changed
		count = 0;
		myLastAddress = cm.me.address;
		deletePlayers();
		players.push_back(&cm.me);
		cm.me.setColor(sf::Color::Yellow);
		std::vector<DWORD> enemies = mem.getAllEnemies();
		std::vector<DWORD> mates = mem.getAllTeammates();
		for (size_t i = 0U; i < enemies.size(); ++i) {
			dh::CsPlayer* p = new dh::CsPlayer;
			p->address = enemies[i];
			p->updateColor();
			this->players.push_back(p);
		}
		for (size_t i = 0U; i < mates.size(); ++i) {
			dh::CsPlayer* p = new dh::CsPlayer;
			p->address = mates[i];
			p->updateColor();
			this->players.push_back(p);
		}
	}
	for (size_t i = 0; i < players.size(); ++i) {
		players[i]->updateCircleshape(0, getBounds().height + 2 * getBounds().top);
		players[i]->updateDirectionLine();
	}
	++count;
}
void dh::CsMap::deletePlayers(void) {
	for (size_t i = 0; i < players.size(); ++i) {
		if (((CsPlayer*)players[i])->address == cm.me.address) continue;
		delete players[i];
	}
	players.clear();
}
#endif