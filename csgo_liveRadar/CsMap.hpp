#pragma once

#include "DEFINITIONS.hpp"
#ifdef CSGO
#include "Map.hpp"

namespace dh {
	class CsMap :
		public Map
	{
	public:
		CsMap(std::string name);
		~CsMap() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updatePlayers(void) override;
		void deletePlayers(void) override;
	};
}
#endif