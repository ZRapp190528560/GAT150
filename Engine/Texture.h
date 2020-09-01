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

		void draw(const Vector2& position, float angle = 0, const Vector2& scale = { 1,1 }, const Vector2& origin = { 0, 0 }, const bool flip = false);
		void draw(const SDL_Rect& source, const Vector2& position, float angle = 0, const Vector2& scale = {1, 1}, const Vector2& origin = { 0, 0 }, const bool flip = false);
		Vector2 getSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}