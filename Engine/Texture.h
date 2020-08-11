#pragma once
#include "Math/Vector2.h"
#include "Resource/resource.h"
#include <SDL.h>
#include <string>

namespace AZ {
	class texture : public resource {
	public:
		bool create(const std::string& name, void* data = nullptr) override;
		void destroy() override;

		void draw(const Vector2& position, const Vector2& scale, float angle);
		void draw(const SDL_Rect& source, const Vector2& position, const Vector2& scale, float angle);
		Vector2 getSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}