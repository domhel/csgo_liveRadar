#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CsPlayer.hpp"
#ifdef CSGO
#include "MemoryManager.h"
#include "offsets.hpp"
#include "Manager.h"
#include <iostream>

dh::CsPlayer::CsPlayer(): dh::Player()
{
	address = 0UL;
}
dh::CsPlayer::~CsPlayer()
{
}

void dh::CsPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	target.draw(body, states);
	target.draw(direction, states);
}
void dh::CsPlayer::updateCircleshape(int offset_x, int offset_y)
{
	sf::Vector3f pos = this->getPosition();
	this->body.setPosition(pos.x + offset_x, offset_y - pos.y);
}

void dh::CsPlayer::updateDirectionLine(void)
{
	sf::Vector3f dir = this->getVelocity();
	float angleRad = atan2f(-dir.y, dir.x) - 3.14159f / 2.0f;
	float angle = angleRad * 180.0f / 3.14159f;
	this->direction.setPosition(body.getPosition().x + body.getRadius() * std::cosf(angleRad), body.getPosition().y - body.getRadius() * std::sinf(angleRad));
	// Angle
	direction.setRotation(angle);
}
void dh::CsPlayer::updateColor(void)
{
	int team = this->getTeam();
	if (this->isTeammate()) body.setFillColor(sf::Color::Blue);
	else body.setFillColor(sf::Color::Red);
}

void dh::CsPlayer::updateAddress(int index)
{
	this->address = mem.getEntityAddress(index);
}
bool dh::CsPlayer::isEnemy(void) const
{
	return (this->getTeam() != cm.me.getTeam() && this->getTeam() > 1);
}
bool dh::CsPlayer::isTeammate(void) const
{
	return (this->getTeam() == cm.me.getTeam());
}
bool dh::CsPlayer::isAlive(void) const
{
	int health = this->getHealth();
	return (health > 0 && health <= 100 && !this->isDormant());
}

int dh::CsPlayer::getHealth(void) const
{
	return mem.readMem<int>(this->address + hazedumper::netvars::m_iHealth);
}
int dh::CsPlayer::getTeam(void) const
{
	return mem.readMem<int>(this->address + hazedumper::netvars::m_iTeamNum);
}
bool dh::CsPlayer::isDormant(void) const
{
	return mem.readMem<bool>(this->address + hazedumper::signatures::m_bDormant);
}
float dh::CsPlayer::isFlashed(void) const
{
	return mem.readMem<float>(this->address + hazedumper::netvars::m_flFlashDuration);
}
bool dh::CsPlayer::isDefusing(void) const
{
	return mem.readMem<bool>(this->address + hazedumper::netvars::m_bIsDefusing);
}
bool dh::CsPlayer::isSpotted(void) const
{
	return mem.readMem<bool>(this->address + hazedumper::netvars::m_bSpotted);
}
sf::Vector3f dh::CsPlayer::getPosition(void) const
{
	return mem.readMem<sf::Vector3f >(this->address + hazedumper::netvars::m_vecOrigin);
}
sf::Vector3f dh::CsPlayer::getVelocity(void) const
{
	return mem.readMem<sf::Vector3f >(this->address + hazedumper::netvars::m_vecVelocity);
}
sf::Vector3f dh::CsPlayer::getViewOffset(void) const
{
	return mem.readMem<sf::Vector3f >(this->address + hazedumper::netvars::m_vecViewOffset);
}

sf::Vector3f dh::CsPlayer::getBonePosition(int bone) const
{
	DWORD bb = getBoneBase();
	return sf::Vector3f(
		mem.readMem<float>(bb + 0x30 * bone + 0x0C),
		mem.readMem<float>(bb + 0x30 * bone + 0x1C),
		mem.readMem<float>(bb + 0x30 * bone + 0x2C)
	);
}

DWORD dh::CsPlayer::getBoneBase(void) const
{
	return mem.readMem<DWORD>(this->address + hazedumper::netvars::m_dwBoneMatrix);
}
sf::Vector3f dh::CsPlayer::getAimPunch(void) const
{
	return mem.readMem<sf::Vector3f >(this->address + hazedumper::netvars::m_aimPunchAngle);
}
int dh::CsPlayer::getWeaponInHand(void) const
{
	int weaponId = mem.readMem<int>(this->address + hazedumper::netvars::m_hActiveWeapon);
	weaponId &= 0xFFF;
	DWORD weaponEntity = mem.readMem<DWORD>(mem.clientBase + hazedumper::signatures::dwEntityList + (weaponId - 1) * 16);
	int weaponIndex = mem.readMem<int>(weaponEntity + hazedumper::netvars::m_iItemDefinitionIndex);
	return weaponIndex;
}
#endif