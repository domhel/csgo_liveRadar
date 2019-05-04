#pragma once

#include "Window.hpp"

namespace dh {
	class SimWindow :
		public dh::Window
	{
	public:
		SimWindow(dh::Map& map, unsigned int width, unsigned int height);

		void Run(void) override;
		void Update(float dt) override;
		void Render(void) override;
		void handleInput(void) override;
	};
}