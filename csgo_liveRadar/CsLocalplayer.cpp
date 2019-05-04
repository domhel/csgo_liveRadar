#include <SFML/Graphics.hpp>
#include "CsLocalplayer.hpp"
#ifdef CSGO
#include "MemoryManager.h"
#include "offsets.hpp"
#include "Manager.h"


dh::CsLocalplayer::CsLocalplayer() : dh::CsPlayer()
{
	face.setFillColor(sf::Color::White);
	face.setOutlineThickness(1.0f);
	face.setOutlineColor(sf::Color::Black);
	face.setSize(sf::Vector2f(body.getRadius() / 5.0f, body.getRadius() * 1.0f));
	face.setOrigin(face.getLocalBounds().width / 2.0f, face.getLocalBounds().height / 2.0f);

	address = mem.getLocalplayer();
	crosshairId = 0;
}
void dh::CsLocalplayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	target.draw(body, states);
	target.draw(direction, states);
	target.draw(face, states);
}
void dh::CsLocalplayer::updateAddress(void)
{
	this->address = mem.getLocalplayer();
}
void dh::CsLocalplayer::updateCrosshairId(void)
{
	this->crosshairId = mem.readMem<int>(this->address + hazedumper::netvars::m_iCrosshairId);
}
void dh::CsLocalplayer::updateFace(void)
{
	sf::Vector3f angles = this->getViewAngles();
	float phi = angles.y;
	angles.y = angles.y / 180.0f * 3.14159f;
	//       90
	// +-180     0
	//		-90
	this->face.setPosition(body.getPosition().x + body.getRadius() * std::cosf(angles.y), body.getPosition().y - body.getRadius() * std::sinf(angles.y));
	face.setRotation(-phi);
}
sf::Vector3f dh::CsLocalplayer::getViewAngles(void) const
{
	return mem.readMem<sf::Vector3f >(mem.getClientState() + hazedumper::signatures::dwClientState_ViewAngles);
}
#endif