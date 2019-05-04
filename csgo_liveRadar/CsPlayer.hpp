#pragma once

#include "DEFINITIONS.hpp"
#ifdef CSGO
#include "Player.hpp"
#include <Windows.h>

/*namespace sf {
	class Vector3f;
}*/

namespace dh {
	enum weapon {
		WEAPON_AK47 = 7,
		WEAPON_M4A4 = 16,
		WEAPON_M4A1S = 60,
		WEAPON_P2000 = 32,
		WEAPON_FIVE7 = 3,
		WEAPON_DEAGLE = 1,
		WEAPON_USPS = 61,
		WEAPON_P250 = 36,
		WEAPON_DUALS = 2,
		WEAPON_GLOCK = 4,
		WEAPON_TEC9 = 30,
		WEAPON_SSG08 = 40,
		WEAPON_MP9 = 34,
		WEAPON_MP7 = 33,
		WEAPON_NOVA = 35,
		WEAPON_XM = 25,
		WEAPON_SAWEDOFF = 29,
		WEAPON_MAG7 = 27,
		WEAPON_GALIL = 13,
		WEAPON_NEGEV = 28,
		WEAPON_P90 = 19,
		WEAPON_MAC10 = 17,
		WEAPON_UMP = 24,
		WEAPON_AWP = 9,
		WEAPON_FAMAS = 10,
		WEAPON_CZ75 = 63,
		WEAPON_DECOY = 47,
		WEAPON_SMOKE = 45,
		WEAPON_HEGRENADE = 44,
		WEAPON_MOLOTOV = 46,
		WEAPON_INCENDARY = 48,
		WEAPON_FLASHBANG = 43
	};
	enum weaponType {
		IS_GRENADE = 1,
		IS_RIFLE = 2,
		IS_SNIPER = 3,
		IS_PISTOL = 4,
		IS_SHOTGUN = 6,
		IS_SMG = 5,
		IS_UNKNOWN = 7
	};
	class CsPlayer :
		public Player
	{
	public:
		DWORD address;

		CsPlayer();
		virtual ~CsPlayer();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updateCircleshape(int offset_x = 0, int offset_y = 0) override;
		void updateDirectionLine(void) override;
		void updateColor(void);
		void updateAddress(int index);
		bool isEnemy(void) const;
		bool isTeammate(void) const;
		bool isAlive(void) const;
		int getHealth(void) const;
		int getTeam(void) const;
		bool isDormant(void) const;
		float isFlashed(void) const;
		bool isDefusing(void) const;
		bool isSpotted(void) const;
		sf::Vector3f getPosition(void) const;
		sf::Vector3f getVelocity(void) const;
		sf::Vector3f getViewOffset(void) const; // origin
		sf::Vector3f getBonePosition(int bone) const;
		sf::Vector3f getAimPunch(void) const;
		int getWeaponInHand(void) const;
		DWORD getBoneBase(void) const;
	};
}
#endif