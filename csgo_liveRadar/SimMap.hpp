#pragma once

#include "Map.hpp"

namespace dh {
	class SimMap :
		public Map
	{
	public:
		SimMap(std::string name);
		~SimMap() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updatePlayers(void) override;
		void deletePlayers(void) override;
		void addPlayer(void);
	};
}