#pragma once

#include "Window.hpp"

namespace dh {
	class CsWindow:
		public Window
	{
	public:
		CsWindow(Map& map, unsigned int width, unsigned int height);

		void Run(void) override;
		void Update(float dt) override;
		void Render(void) override;
		void handleInput(void) override;
	};
}