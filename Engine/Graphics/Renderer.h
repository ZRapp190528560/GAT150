#pragma once
#include "Core/System.h"

namespace AZ {
	class renderer : public system {
	public:
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		bool createWindow(const std::string& name, int width, int height);

		void beginFrame();
		void endFrame();

		friend class texture;

	protected:
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}